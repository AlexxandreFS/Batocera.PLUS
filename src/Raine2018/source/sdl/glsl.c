#include <SDL.h>
#ifndef RAINE_WIN32
// Go figure : this support is totally broken in windows !!!
#define GL_GLEXT_PROTOTYPES
#endif
#include <SDL_opengl.h>
#ifdef MessageBox
#undef MessageBox
#endif
#include "files.h"
#include "debug.h"
#include "sdl/compat.h"
#include "blit.h"
#include "sdl/blit_sdl.h"
#include "sdl/display_sdl.h"
#include "sdl/opengl.h"
#include "sdl/dialogs/messagebox.h"
#include "math/matrix.h"
#include "translate.h"

// glsl shaders

struct gl_ortho
{
   GLfloat left;
   GLfloat right;
   GLfloat bottom;
   GLfloat top;
   GLfloat znear;
   GLfloat zfar;
};
static math_matrix mvp;
static int modern;
static GLuint vertexshader; // only one
#ifdef RAINE_WIN32
#define glGetProcAddress(name) wglGetProcAddress(name)
static int no_shader_support = 0;
static PFNGLCREATEPROGRAMPROC glCreateProgram = 0;
static PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = 0;
static PFNGLGETATTRIBLOCATIONARBPROC glGetAttribLocation = 0;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = 0;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = 0;
static PFNGLACTIVETEXTUREPROC glActiveTexture = 0;

static PFNGLVALIDATEPROGRAMPROC glValidateProgram = 0;
static PFNGLDELETEPROGRAMPROC glDeleteProgram = 0;
static PFNGLUSEPROGRAMPROC glUseProgram = 0;
static PFNGLCREATESHADERPROC glCreateShader = 0;
static PFNGLDELETESHADERPROC glDeleteShader = 0;
static PFNGLSHADERSOURCEPROC glShaderSource = 0;
static PFNGLCOMPILESHADERPROC glCompileShader = 0;
static PFNGLGETSHADERIVPROC glGetShaderiv = 0;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = 0;
static PFNGLATTACHSHADERPROC glAttachShader = 0;
static PFNGLDETACHSHADERPROC glDetachShader = 0;
static PFNGLLINKPROGRAMPROC glLinkProgram = 0;
static PFNGLGETPROGRAMIVPROC glGetProgramiv = 0;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = 0;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = 0;
static PFNGLUNIFORM1IPROC glUniform1i = 0;
static PFNGLUNIFORM2FVPROC glUniform2fv = 0;
static PFNGLUNIFORM4FVPROC glUniform4fv = 0;
#endif

static int nb_pass; // number of passes for the shader
#define MAX_PASS 10
typedef struct {
    GLuint glprogram, fragmentshader;
    int sizex,sizey,filter;
    float outscalex,outscaley;
    int vertex;
    // locations
    GLint input_size,output_size,texture_size,mvp,texture;
    GLint orig_texture_size,orig_input_size,frame_count,tex_coord;

} tpass;

static tpass pass[MAX_PASS];

// Vertexes of the quad to draw the texture on...
// Used for the last pass when rendering to the back buffer.
const GLfloat vertexes_flipped[] = {
   0, 1,
   1, 1,
   0, 0,
   1, 0
};

// Used when rendering to an FBO.
// Texture coords have to be aligned with vertex coordinates.
static GLfloat vertexes[] = {
   0, 0,
   1, 0,
   0, 1,
   1, 1
};

static const GLfloat tex_coords[] = {
   0, 0,
   1, 0,
   0, 1,
   1, 1
};

static char* getstr(char *s, char *what) {
    char *p = strstr(s,what);
    if (p) p += strlen(what);
    return p;
}

static char *arg, *value;

static char* getarg(char *p) {
    arg = value = NULL;
    while (*p < 33) p++;
    if (*p < 'a' || *p > 'z') return p;
    char *e = strchr(p,'=');
    if (!e) return p;
    arg = p;
    *e = 0;
    p = e+1;
    if (*p == '"') { // quote
	p++;
	e = strchr(p,'"');
	if (!e) return p;
	*e = 0;
	value = p;
	p = e+1;
    } else { // don't even know if something can go without quotes in xml...
	e = p;
	while (*p != ' ' && *p)
	    p++;
	if (*p) {
	    *p = 0;
	    p++;
	}
	value = e;
    }
    return p;
}

static char *my_load_file(char *shader) {
    int size = size_file(shader);
    if (!size) {
	printf("shader: couldn't find file %s\n",shader);
	return NULL;
    }
    char *buf = malloc(size+1);
    if (!buf) {
	printf("shader: couldn't allocate %d bytes\n",size);
	return NULL;
    }
    if (!load_file(shader,(unsigned char*)buf,size)) {
	printf("shader: couldn't load %s\n",shader);
	free(buf);
	return NULL;
    }
    buf[size] = 0;
    return buf;
}

static char *process_cdata(char *p) {
    while (*p < 32) p++;
    value = p;
    p = getstr(p,"]]>");
    p[-3] = 0;
    return p;
}

static int mystrcmp(char **s, char *cmp) {
    int len = strlen(cmp);
    int ret = strncmp(*s,cmp,len);
    if (!ret) *s += len;
    return ret;
}

static int attach(GLuint shader) {
    int gl_error;
    if (!pass[nb_pass].glprogram) {
	pass[nb_pass].glprogram = glCreateProgram();
	print_debug("pass %d glprogram created %d\n",nb_pass,pass[nb_pass].glprogram);
    }
    if (vertexshader && vertexshader != shader &&
	    vertexshader != pass[nb_pass].vertex) {
	print_debug("attaching vertex shader %d to program %d\n",vertexshader,pass[nb_pass].glprogram);
	gl_error = glGetError( );
	glAttachShader(pass[nb_pass].glprogram, vertexshader);
	gl_error = glGetError( );
	if( gl_error != GL_NO_ERROR ) {
	    strcpy(ogl.shader,"None");
	    MessageBox(gettext("OpenGL error"),gettext("error while attaching vertex shader"),gettext("ok"));
	    return 0;
	}
    }
    print_debug("attaching shader %d to program %d\n",shader,pass[nb_pass].glprogram);
    gl_error = glGetError( );
    glAttachShader(pass[nb_pass].glprogram, shader);
    gl_error = glGetError( );
    if( gl_error != GL_NO_ERROR ) {
	strcpy(ogl.shader,"None");
	MessageBox(gettext("OpenGL error"),gettext("error while attaching fragment shader"),gettext("ok"));
	return 0;
    } else if (vertexshader == shader)
	pass[nb_pass].vertex = shader;
    check_error("attach");
    return 1;
}

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static int set_fragment_shader(const char *program) {
    int ret = 1;
    char *define = "#define FRAGMENT\n";
    GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *source[] = { define, program };
    glShaderSource(fragmentshader, ARRAY_SIZE(source), source, NULL);
    glCompileShader(fragmentshader);

    GLint tmp;
    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &tmp);
    if (!tmp) {
	glGetShaderiv(fragmentshader, GL_INFO_LOG_LENGTH, &tmp);
	GLchar *buf = malloc(tmp);
	glGetShaderInfoLog(fragmentshader, tmp, NULL, buf);
	strcpy(ogl.shader,"None");
	MessageBox(gettext("Errors compiling fragment shader"),buf,gettext("ok"));
	free(buf);
	ret = 0;
    } else
	ret = attach(fragmentshader);
    pass[nb_pass].fragmentshader = fragmentshader;
    check_error("set_fragment");
    return ret;
}

static int set_vertex_shader(const char *program) {
    int ret = 1;
    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    char *define = "#define VERTEX\n";

    const char *source[] = { define, program };
    glShaderSource(vertexshader, ARRAY_SIZE(source), source, NULL);
    print_debug("compiling vertex shader %d\n",vertexshader);
    glCompileShader(vertexshader);

    GLint tmp;
    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &tmp);
    if (!tmp) {
	glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &tmp);
	GLchar *buf = malloc(tmp);
	glGetShaderInfoLog(vertexshader, tmp, NULL, buf);
	printf("Errors compiling vertex shader: %s\n", buf);
	print_debug("errors compiling vertex shader : %s\n",buf);
	free(buf);
	ret = 0;
    } else {
	/* After seeing an example of a v1.2 xml shader, it seems the vertex
	 * shader can be totally at the end of the file, so I guess that it
	 * needs to be attached to all created programs in this case ! */
	print_debug("compilation vertex shader ok\n");
	int nb = nb_pass;
	for (nb_pass=0; nb_pass <= nb; nb_pass++)
	    ret &= attach(vertexshader);
	nb_pass = nb;
    }
    check_error("set_vertex");
    return ret;
}

void delete_shaders() {
    modern = 0;
    int n;
    for (n=0; n<=nb_pass; n++) {
	if (pass[n].glprogram) {
	    if (pass[n].fragmentshader) {
		glDetachShader(pass[n].glprogram, pass[n].fragmentshader);
		glDeleteShader(pass[n].fragmentshader);
	    }
	    if (vertexshader) glDetachShader(pass[n].glprogram,vertexshader);
	    glDeleteProgram(pass[n].glprogram);
	    print_debug("delete program %d\n",pass[n].glprogram);
	    pass[n].fragmentshader = pass[n].glprogram = 0;
	}
	pass[n].sizex = pass[n].sizey = pass[n].filter = pass[n].vertex = 0;
	pass[n].outscalex = pass[n].outscaley = 0.0;
    }
    if (vertexshader) {
	glDeleteShader(vertexshader);
	vertexshader = 0;
    }
    nb_pass = 0;
}

static char *prefix[] = {
    "ruby", NULL };

static GLint get_uniform_loc(GLuint prog, const char *name)
{
    GLint loc = glGetUniformLocation(prog,name);
    if (loc >= 0) return loc;
    char buf[64];
    char **pref = &prefix[0];
    while (*pref) {
	sprintf(buf,"%s%s",*pref,name);
	loc = glGetUniformLocation(prog,buf);
	if (loc >= 0) return loc;
	pref++;
    }
    return -1;
}

// Exactly the same function, but with glGetAttributeLocation... so unefficient
static GLint get_attrib_loc(GLuint prog, const char *name)
{
    GLint loc = glGetAttribLocation(prog,name);
    if (loc > 0) return loc;
    char buf[64];
    char **pref = &prefix[0];
    while (*pref) {
	sprintf(buf,"%s%s",*pref,name);
	loc = glGetAttribLocation(prog,buf);
	if (loc > 0) return loc;
	pref++;
    }
    return -1;
}

void read_shader(char *shader) {
    /* The idea is to try to make the code as readable as possible (it's
     * about string manipulation in C, so there won't be any miracle !), but
     * I'll have a separate block of code for each tag, and since there are
     * only shader, vertex and fragment here, it should do...
     *
     * Also I saw somewhere on the web that sometimes they use src instead of
     * cdata even though it's not part of 1.1 specification, but I added
     * support for it anyway... */

    char *vertex_src = NULL, *frag_src = NULL;
    char *buf = my_load_file(shader);
    int vertex_used_src = 0, frag_used_src = 0;
#ifdef RAINE_WIN32
    if (no_shader_support) return;
    if (!glCreateProgram) {
	//bind shader functions
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)glGetProcAddress("glCreateProgram");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glGetProcAddress("glUniformMatrix4fv");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONARBPROC)glGetProcAddress("glGetAttribLocation");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glGetProcAddress("glEnableVertexAttribArray");
	glActiveTexture = (PFNGLACTIVETEXTUREPROC)glGetProcAddress("glActiveTexture");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glGetProcAddress("glVertexAttribPointer");
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)glGetProcAddress("glValidateProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glGetProcAddress("glDeleteProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC)glGetProcAddress("glUseProgram");
	glCreateShader = (PFNGLCREATESHADERPROC)glGetProcAddress("glCreateShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)glGetProcAddress("glDeleteShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)glGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)glGetProcAddress("glCompileShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)glGetProcAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glGetProcAddress("glGetShaderInfoLog");
	glAttachShader = (PFNGLATTACHSHADERPROC)glGetProcAddress("glAttachShader");
	glDetachShader = (PFNGLDETACHSHADERPROC)glGetProcAddress("glDetachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)glGetProcAddress("glLinkProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glGetProcAddress("glGetProgramiv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glGetProcAddress("glGetProgramInfoLog");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glGetProcAddress("glGetUniformLocation");
	glUniform1i = (PFNGLUNIFORM1IPROC)glGetProcAddress("glUniform1i");
	glUniform2fv = (PFNGLUNIFORM2FVPROC)glGetProcAddress("glUniform2fv");
	glUniform4fv = (PFNGLUNIFORM4FVPROC)glGetProcAddress("glUniform4fv");

	no_shader_support = glCreateProgram && glUseProgram && glCreateShader
	    && glDeleteShader && glShaderSource && glCompileShader && glGetShaderiv
	    && glGetShaderInfoLog && glAttachShader && glDetachShader && glLinkProgram
	    && glGetProgramiv && glGetProgramInfoLog && glGetUniformLocation
	    && glUniform1i && glUniform2fv && glUniform4fv;
	no_shader_support = !no_shader_support;
    }
    if (no_shader_support) {
	MessageBox(gettext("Warning"),gettext("No shader support on your hardware"),gettext("ok"));
	return;
    }
#endif

    delete_shaders();

    if (!buf)
	return;
    if (!stricmp(shader+strlen(shader)-5,".glsl")) {
	vertex_src = buf;
	if (!set_vertex_shader(vertex_src)) {
	    delete_shaders();
	    goto flee;
	}
	frag_src = buf;
	if (!set_fragment_shader(frag_src)) {
	    delete_shaders();
	    goto flee;
	}
	goto shader_end;
    }

    char *p = buf;
start_shader:
    p = getstr(p,"<shader");
    if (!p) {
	printf("no shader in file %s\n",shader);
	goto flee;
    }
    while (*p == ' ') {
	p = getarg(p);
	if (!strcmp(arg,"language")) {
	    if (strcmp(value,"GLSL")) {
		p++;
		goto start_shader; // Maybe 2 shaders in file
	    }
	} else if (!strcmp(arg,"style"))
	    modern = !strcmp(value,"GLES2");
	else
	    printf("unknown shader argument : %s=%s\n",arg,value);
    }
    while ((p = getstr(p,"<"))) {
	if (!mystrcmp(&p,"!--")) // comment
	    p = getstr(p,"-->");


	else if (!mystrcmp(&p,"vertex")) {
	    if (vertex_src) {
		printf("shader: 2 vertex codes found in this shader, aborting\n");
		goto flee;
	    }
	    while (*p == ' ') {
		/* No argument expected for vertex shader, but I'll process
		 * src anyway */
		p = getarg(p);
		if (!strcmp(arg,"src")) {
		    vertex_src = my_load_file(value);
		    if (!vertex_src) {
			printf("shader: couldn't load vertex shader from src %s\n",value);
			goto flee;
		    }
		    vertex_used_src = 1;
		} else
		    printf("shader: unknown vertex argument : %s=%s\n",arg,value);
	    }
	    p = getstr(p,"<");
	    if (!mystrcmp(&p,"![CDATA[")) {
		if (vertex_src) {
		    printf("shader: 2 vertex declarations\n");
		    goto flee;
		}
		p = process_cdata(p);
		vertex_src = value;
	    } else if (mystrcmp(&p,"/vertex")) {
		printf("unexpected tag in vertex : %s\n",p);
	    }
	    if (!vertex_src) {
		printf("shader: parsing of vertex tag failed\n");
		goto flee;
	    }
	    if (!set_vertex_shader(vertex_src)) {
		delete_shaders();
		goto flee;
	    }
	    p = getstr(p,"/vertex>");


	} else if (!mystrcmp(&p,"fragment")) {
	    if (pass[nb_pass].fragmentshader)
		printf("shader: pass %d\n",++nb_pass);
	    while (*p == ' ') {
		if (frag_used_src) {
		    free(frag_src);
		    frag_used_src = 0;
		}
		p = getarg(p);
		if (!strcmp(arg,"src")) {
		    frag_src = my_load_file(value);
		    if (!frag_src) {
			printf("shader: couldn't load fragment shader from src %s\n",value);
			goto flee;
		    }
		    frag_used_src = 1;
		} else if (!strcmp(arg,"filter")) {
		    if (!strcmp(value,"linear"))
			pass[nb_pass].filter = 1;
		    else if (!strcmp(value,"nearest"))
			pass[nb_pass].filter = 2;
		    else {
			printf("filter value unknown : %s\n",value);
			pass[nb_pass].filter = 0;
		    }
		} else if (!strcmp(arg,"size")) {
		    pass[nb_pass].sizex = pass[nb_pass].sizey = atoi(value);
		} else if (!strcmp(arg,"size_x"))
		    pass[nb_pass].sizex = atoi(value);
		else if (!strcmp(arg,"size_y"))
		    pass[nb_pass].sizey = atoi(value);
		else if (!strcmp(arg,"scale")) {
		    pass[nb_pass].sizex = GameScreen.xview*atof(value);
		    pass[nb_pass].sizey = GameScreen.yview*atof(value);
		} else if (!strcmp(arg,"scale_x"))
		    pass[nb_pass].sizex = GameScreen.xview*atof(value);
		else if (!strcmp(arg,"scale_y"))
		    pass[nb_pass].sizey = GameScreen.yview*atof(value);
		else if (!strcmp(arg,"outscale")) {
		    pass[nb_pass].outscalex = atof(value);
		    pass[nb_pass].outscaley = atof(value);
		} else if (!strcmp(arg,"outscale_x"))
		    pass[nb_pass].outscalex = atof(value);
		else if (!strcmp(arg,"outscale_y"))
		    pass[nb_pass].outscaley = atof(value);
		else
		    printf("shader: unknown fragment argument : %s=%s\n",arg,value);
	    }
	    p = getstr(p,"<");
	    if (!mystrcmp(&p,"![CDATA[")) {
		if (frag_src && frag_used_src) {
		    free(frag_src);
		    frag_used_src = 0;
		}
		p = process_cdata(p);
		frag_src = value;
	    } else if (mystrcmp(&p,"/fragment")) {
		printf("unexpected tag in vertex : %s\n",p);
	    }
	    if (!frag_src) {
		printf("shader: parsing of fragment tag failed\n");
		goto flee;
	    }
	    if (!set_fragment_shader(frag_src)) {
		delete_shaders();
		goto flee;
	    }
	    p = getstr(p,"/fragment>");
	} else if (!mystrcmp(&p,"/shader>")) {
	    int n;
shader_end:
	    print_debug("end of shader\n");

	    for (n=0; n<=nb_pass; n++) {
		glLinkProgram(pass[n].glprogram);
		print_debug("linking program %d pass %d\n",pass[n].glprogram,n);

		GLint tmp;
		glGetProgramiv(pass[n].glprogram, GL_LINK_STATUS, &tmp);
		if (!tmp) {
		    glGetProgramiv(pass[n].glprogram, GL_INFO_LOG_LENGTH, &tmp);
		    GLchar *buf = malloc(tmp);
		    glGetProgramInfoLog(pass[n].glprogram, tmp, NULL, buf);
		    delete_shaders();
		    strcpy(ogl.shader,"None");
		    MessageBox(gettext("Error linking shader"),buf,gettext("OK"));
		    print_debug("link error : %s\n",buf);
		    free(buf);
		    break;
		} else {
		    print_debug("link ok\n");
		}
		glValidateProgram(pass[n].glprogram);
		glGetProgramiv(pass[n].glprogram, GL_INFO_LOG_LENGTH, &tmp);
		if (tmp && tmp > 1) {
		    // nvidia drivers <= 355 returned a 1 byte buffer here !
		    GLchar *buf = calloc(tmp, 1);
		    GLsizei len;
		    glGetProgramInfoLog(pass[n].glprogram, tmp, &len, buf);
		    printf("Errors validating shader program %d: (len %d max %d) %s\n", n,len,tmp,buf);
		    free(buf);
		    break;
		}
		print_debug("validation glprogram %d pass %d ok\n",pass[n].glprogram,n);
		GLuint glprogram = pass[n].glprogram;
		pass[n].input_size = get_uniform_loc(glprogram, "InputSize");
		pass[n].output_size = get_uniform_loc(glprogram, "OutputSize");
		pass[n].texture_size = get_uniform_loc(glprogram, "TextureSize");
		pass[n].orig_texture_size = get_uniform_loc(glprogram, "OrigTextureSize");
		pass[n].orig_input_size = get_uniform_loc(glprogram, "OrigInputSize");
		pass[n].frame_count = get_uniform_loc(glprogram, "FrameCount");
		pass[n].texture = get_uniform_loc(glprogram, "Texture");
		GLint loc = get_attrib_loc(glprogram, "VertexCoord");
		if (loc > -1) {
		    printf("VertexCoord... %d,%d\n",area_overlay.w,area_overlay.h);
		    vertexes[0] = area_overlay.x; vertexes[1] = area_overlay.y+area_overlay.h-1;
		    vertexes[2] = area_overlay.x+area_overlay.w-1;
		    vertexes[3] = area_overlay.y+area_overlay.h-1;
		    vertexes[4] = area_overlay.x; vertexes[5] = area_overlay.y;
		    vertexes[6] = area_overlay.x+area_overlay.w-1;
		    vertexes[7] = area_overlay.y;

		    glEnableVertexAttribArray(loc);
		    glVertexAttribPointer(loc,2,GL_FLOAT,GL_FALSE,0,vertexes);
		}
		loc = pass[n].mvp = get_uniform_loc(glprogram, "MVPMatrix");
		if (loc > -1) {
		    printf("init mvp\n");
		    struct gl_ortho ortho = {0, 1, 0, 1, -1, 1};
#if 1
		    matrix_ortho(&mvp,ortho.left,ortho.right,
			    ortho.bottom,ortho.top,ortho.znear,ortho.zfar);
#else
		    matrix_ortho(&mvp,area_overlay.x,
			    area_overlay.x+area_overlay.w-1,
			    area_overlay.y,
			    area_overlay.y+area_overlay.h-1,
			    -1,1);
#endif
		} else
		    printf("no MVPMatrix: %d\n",loc);
		loc = pass[n].tex_coord = get_attrib_loc(glprogram, "TexCoord");
	    }

	    goto flee;
	} else {
	    char *e = p;
	    p = getstr(p,">");
	    p[-1] = 0;
	    printf("shader: unknown tag %s\n",e);
	}
    }

    printf("shader: something went wrong, missing end shader declaration ?\n");
flee:
    if (frag_used_src) free(frag_src);
    if (vertex_used_src) free(vertex_src);
    free(buf);
    check_error("read_shader");
}

void draw_shader(int linear)
{
    check_error("start draw_shader");
    if (pass[0].glprogram) {

	int n;
	glActiveTexture(GL_TEXTURE0 + 1); // Used as texture shader parameter !
	for (n=0; n<=nb_pass; n++) {

	    GLuint glprogram = pass[n].glprogram;
	    glUseProgram(glprogram);

	    if (pass[n].tex_coord > -1) {
		glEnableVertexAttribArray(pass[n].tex_coord);
		glVertexAttribPointer(pass[n].tex_coord,2,GL_FLOAT,GL_FALSE,0,tex_coords);
		check_error("texcoord");
	    }
	    if (pass[n].mvp > -1) {
		glUniformMatrix4fv(pass[n].mvp, 1, GL_FALSE, mvp.data);
		check_error("mvp init");
	    }
	    if (pass[n].input_size > -1) {
		float inputSize[2];
/*		if (n > 0) {
		    inputSize[0] = (float)area_overlay.w;
		    inputSize[1] = (float)area_overlay.h;
		} else { */
		    inputSize[0] = (float)GameScreen.xview;
		    inputSize[1] = (float)GameScreen.yview;
		// }
		glUniform2fv(pass[n].input_size, 1, inputSize);
	    }
#if 1
	    if (pass[n].texture > -1) {
		// Contrary to what I thought what is passed here is not
		// the texture number used by glBindTexture but rather the
		// number of the active texture unit, used in a call to
		// glActiveTexture
		// This works, but not as it's supposed to do, apparently
		// for multi-pass shaders I am supposed to switch from 1 texture
		// unit to another, which is not the case for now, so avoid
		// these shaders for now !

		// extern GLuint texture; // opengl.c
		glUniform1i(pass[n].texture, 1);
	    }
#endif
	    if (pass[n].orig_input_size > -1) {
		float inputSize[2] = { (float)GameScreen.xview, (float)GameScreen.yview };
		glUniform2fv(pass[n].orig_input_size, 1, inputSize);
	    }
	    if (pass[n].output_size > -1) {

		float outputSize[2] = { (float)area_overlay.w, (float)area_overlay.h };
		glUniform2fv(pass[n].output_size, 1, outputSize);
	    }

	    if (pass[n].texture_size > -1) {
		// This one is supposed to be >= GameScreen.[xy]view
		// I guess it's in case you decide to use hq2/3x on GameScreen
		// to generate the texture, but I don't think I'll want to do
		// that (loss of cycles everywhere !)
		float textureSize[2] = { (float)GameScreen.xview, (float)GameScreen.yview };
#if 0
		if (n > 0) {
		    textureSize[0] = (float)area_overlay.w;
		    textureSize[1] = (float)area_overlay.h;
		}
#endif
		glUniform2fv(pass[n].texture_size, 1, textureSize);
	    }
	    if (pass[n].orig_texture_size > -1) {
		// Not sure how this one evolves for now
		float textureSize[2] = { (float)GameScreen.xview, (float)GameScreen.yview };
		glUniform2fv(pass[n].orig_texture_size, 1, textureSize);
	    }

	    if (pass[n].frame_count > -1) {

		extern UINT32 cpu_frame_count; // profile.c
		glUniform1i(pass[n].frame_count, cpu_frame_count);
	    }
	    if (pass[n].filter == 2) // explicit nearest
		linear = GL_NEAREST;
	    else
		linear = ogl.filter;
	    /* Notice : for now all the size/scale/outscale parameters are
	     * simply ignored, it's because I didn't find any shader using
	     * them until now */
	    render_texture(linear);
	}
	glUseProgram(0); // all shaders off now
	glActiveTexture(GL_TEXTURE0); // return to default textures for texts
	check_error("ret draw_shader");
	return;
    }
    render_texture(linear);
    check_error("end draw_shader");
}

