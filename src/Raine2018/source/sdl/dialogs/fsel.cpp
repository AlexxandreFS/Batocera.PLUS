#ifdef RAINE_WIN32
#include <windows.h> // GetLogicalDrives
#endif
#include "raine.h"
#include "../gui/menu.h"
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#ifdef RAINE_WIN32
#include "fnmatch/fnmatch.h"
#else
#include <fnmatch.h>
#endif
#include "fsel.h"

class TFileSel : public TMenu
{
  protected:
    int nb_files;
    char **ext;
    int options;
    char *title2;
  public:
    char path[FILENAME_MAX];
    char *res_file;
    TFileSel(char *my_title, char *mypath, char **myext, char *res_str,int opts = 0, char* mytitle2 = NULL);
    virtual char* get_emuname();
    virtual ~TFileSel();
    virtual void compute_nb_items();
    virtual int get_fgcolor(int n);
    int can_be_selected(int n) {
      return can_be_displayed(n);
    }
    virtual void set_dir(char *mypath);
    virtual int mychdir(int n);
    virtual int myexec_file(int sel);
};

static int selected_path;
static TFileSel *dlg;

static int sel_path(int sel) {
  selected_path = sel;
  return 1;
}

class path_sel {
  private:
    menu_item_t *menu;
    int nb,max;
  public:
    path_sel() {
      menu = NULL;
      nb = max = 0;
    }
    ~path_sel() {
      if (menu) {
	for(nb--; nb>= 0; nb--)
	  free((void*)menu[nb].label);
	free(menu);
      }
    }
    void add_item(char *path) {
      if (!path)
	return;
      if (nb == max) {
	max += 10;
	menu = (menu_item_t*)realloc(menu,(max+1)*sizeof(menu_item_t));
	memset(&menu[nb],0,(11)*sizeof(menu_item_t));
      }
      menu[nb].label = strdup(path);
      menu[nb].menu_func = sel_path;
      nb++;
    }
    menu_item_t *get_menu() {
      return menu;
    }
};

static int exec_dir(int sel) {
  // just a wrapper to call mychdir
  return dlg->mychdir(sel);
}

static int exec_file(int sel) {
  return dlg->myexec_file(sel);
}

class TPathDlg : public TMenu
{
  public:
  TPathDlg(char *my_title, menu_item_t *menu) :
    TMenu(my_title,menu, NULL,-1, -1,-1,-1, /* to_translate */ 0)
  {}
  char *get_emuname() {
    return dlg->get_emuname();
  }
};

static int do_paths(int sel) {
  path_sel *paths = new path_sel();
  paths->add_item(getenv("HOME"));
#ifdef RAINE_UNIX
  int pipe_opened = 0;
  FILE *f = fopen("/etc/mtab","r");
  if (!f) {
      // Darwin doesn't seem to have a file for that, so let's use popen...
      f = popen("mount","r");
      pipe_opened = 1;
  }
  if (f) {
    char buff[2048];
    while (!feof(f)) {
      fgets(buff,2048,f);
      if (strncmp(buff,"/dev/",5) && !pipe_opened) // keep only the /dev entries
	continue;
      char *s1 = strchr(buff,' ');
      if (!s1) continue;
      char *s2 = strchr(s1+1,' ');
      if (!s2) continue;
      *s2 = 0;
      if (pipe_opened && strcmp(s1+1,"on")) {
	  // Super darwin puts spaces everywhere in its mounts making it hard
	  // to parse, we'll jump directly to "on" then...
	  // Plus strnstr seems unreliable !
	  s1 = s2+1;
	  while (*s1 && (s1[0] != 'o' || s1[1] != 'n'))
	      s1++;
	  if (!*s1) {
	      s1 = s2;
	  } else {
	      s1[2] = 0;
	      s2 = s1+2;
	      s1--;
	  }
      }
      if (!strcmp(s1+1,"on")) {
	  // darwin speciality, just ignore it
	  s1 = s2;
	  s2 = strchr(s1+1,'(');
	  if (!s2) continue;
	  s2[-1] = 0;
      }
      if (strcmp(s1+1,"/dev")) {
	  paths->add_item(s1+1);
      }
    }
    if (pipe_opened)
	pclose(f);
    else
	fclose(f);
  }
#else
  // windows
  paths->add_item(getenv("PROGRAMFILES"));
  paths->add_item(getenv("USERPROFILE"));
  int drives = GetLogicalDrives();
  int n;
  char path[3];
  strcpy(path,"x:");
  for (n=0; n<32; n++) {
    if (drives & (1<<n)) {
      path[0]=65+n;
      paths->add_item(path);
    }
  }
#endif
  selected_path = -1;
  TMenu *menu = new TPathDlg((char*)_("Path selection"),paths->get_menu());
  menu->execute();
  if (selected_path >= 0)
    dlg->set_dir((char*)paths->get_menu()[selected_path].label);
  delete menu;
  delete paths;
  return 0;
}

static int sort_menu(const void *a, const void *b) {
  return stricmp(((menu_item_t *)a)->label, ((menu_item_t *)b)->label);
}

// the only used option for now !
#define ONLY_DIRS 1
#define SAVE 2

TFileSel::TFileSel(char *my_title, char *mypath, char **myext, char *res_str, int opts,char *mytitle2) :
  TMenu(my_title,NULL,NULL,-1, -1,-1,-1, /* to_translate */ 0)
{
  char *s;
  title2 = mytitle2;
  options = opts;
  strcpy(path,mypath);
  int l = strlen(path);
  if (path[l-1] == SLASH[0])
    path[l-1] = 0;

  if ( !strchr(path,SLASH[0])
#ifdef RAINE_WIN32
    && path[1] != ':'
#endif
    ) {
    strcpy(path,dir_cfg.exe_path);
    path[strlen(path)-1] = 0;
  }
  ext = myext;

  // First check if the path exists, and if not take the 1st one which does
  struct stat buf;
  int res;
  do {
    res = stat(path,&buf);
    if (res < 0) { // does not exist
      s = strrchr(path,SLASH[0]);
      if (s)
	*s = 0;
      else {
	strcat(path,SLASH);
	res = 0;
      }
    }
  } while (res < 0);
  title = path;
  res_file = res_str;
}

char* TFileSel::get_emuname() {
  if (title2 && *title2)
    return title2;
  else
    return TMenu::get_emuname();
}

static char res_file[FILENAME_MAX+1];
static int ihead;

static int validate_file(int res) {
    snprintf(dlg->res_file,FILENAME_MAX,"%s%s%s",dlg->path,SLASH,res_file);
    return 1;
}

static menu_item_t myheader_save[] = {
    { _("New file"), &validate_file, &ihead, ITEM_EDIT, { FILENAME_MAX, 0, 200 }, { res_file } },
    { _("-- Path... "), &do_paths },
    { NULL }
};

static menu_item_t myheader[] = {
    { _("-- Path... "), &do_paths },
    { NULL }
};

void TFileSel::compute_nb_items() {
  DIR *dir = opendir(path);
  int nb_menu = 10;
  char cwd[1024];
  char tmp_path[1024];
  int found_cue = 0, found_iso = 0;
  char *oldsel = strrchr(res_file,SLASH[0]);
  if (oldsel) oldsel++;
  if (menu)
    free(menu);
  menu = (menu_item_t *)malloc(sizeof(menu_item_t)*(nb_menu+1));
  memset(menu,0,sizeof(menu_item_t)*(nb_menu+1));

  menu[0].label = "..";
  menu[0].menu_func = &exec_dir;
  if (!dir) {
    perror(path);
  } else {
    getcwd(cwd,1024);
    nb_files = 1;
    struct dirent *dent;
    while ((dent = readdir(dir))) {
      if (!strcmp(dent->d_name,".") || !strcmp(dent->d_name,".."))
	continue;
      menu[nb_files].label = strdup(dent->d_name);
      snprintf(tmp_path,1024,"%s%s%s",path,SLASH,dent->d_name);
      /* The big stupidity of readdir is that it doesn't set d_type (posix
       * compliant !!!).  */
      struct stat buf;
      if (!stat(tmp_path,&buf) && S_ISDIR(buf.st_mode)) {
	menu[nb_files].menu_func = &exec_dir;
	nb_files++;
      } else if (!(options & ONLY_DIRS)) {
	menu[nb_files].menu_func = &exec_file;
	int found = 0,idx;
	char *s = dent->d_name;
	if (strlen(s) > 3) {
	    if (!stricmp(&s[strlen(s)-3],"iso") ||
		    (strlen(s) > 6 && !stricmp(&s[strlen(s)-6],"iso.gz")))
		found_iso++;
	    else if (!stricmp(&s[strlen(s)-3],"cue"))
		found_cue++;
	}
	if (ext) {
	    for (s=ext[0], idx=1; s; s=ext[idx++]) {
		int l = strlen(s);
		if (strchr(s,'*') || strchr(s,'?')) { // pattern search
		    if (!fnmatch(s,dent->d_name,FNM_CASEFOLD)) {
			found = 1;
			break;
		    }
		} else if (!stricmp(&dent->d_name[strlen(dent->d_name)-(l)],s)) {
		    // extension only
		    found = 1;
		    break;
		}
	    }
	} else
	    found = 1;
	if (!found) {
	  // doesn't match the extension given
	  free((void*)menu[nb_files].label);
	} else
	  nb_files++;
      }

      if (nb_files == nb_menu) {
	nb_menu += 10;
	menu = (menu_item_t *)realloc(menu,sizeof(menu_item_t)*(nb_menu+1));
	memset(&menu[nb_files],0,sizeof(menu_item_t)*11);
	if (!menu) {
	  fprintf(stderr,"failed to realloc files buffer (%d entries)\n",nb_menu);
	  exit(1);
	}
      }
    }
    menu[nb_files].label = NULL;
    closedir(dir);
    qsort(&menu[1],nb_files-1,sizeof(menu_item_t),&sort_menu);
    if (oldsel)
	for (int n=1; n<nb_files; n++)
	    if (!strcmp(menu[n].label,oldsel))
		sel = n;
    chdir(cwd);
  }
  strcpy(res_file,path);
  if (path[strlen(path)-1] != SLASH[0])
    strcat(res_file,SLASH);
  if (options & SAVE)
      set_header(myheader_save);
  else
      set_header(myheader);
  int tmpsel = sel;
  if (found_iso && !found_cue && strcmp(ext[0],".iso")) {
      char *myexts[] = { ".iso", "iso.gz", "zip", "7z", NULL };
      char **old = ext;
      ext = myexts;
      compute_nb_items();
      ext = old;
  } else
      TMenu::compute_nb_items();
  if (tmpsel > -1)
      sel = tmpsel; // blocks find_new_sel from compute_nb_items
}

TFileSel::~TFileSel() {
  int nb;
  for (nb=2; nb<nb_files; nb++)
    free((void*)menu[nb].label);
  if (menu)
    free(menu);
}

int TFileSel::get_fgcolor(int n) {
  if (menu[n].menu_func == &exec_dir)
    return mymakecol(160,160,255);
  return fg;
}

void TFileSel::set_dir(char *mypath) {
  if (mypath != path)
    strcpy(path,mypath);
  if (!strstr(path,SLASH)) {
    chdir(path);
    getcwd(path,1024);
  }
  if (font) {
    delete font;
    font = NULL;
  }
  set_title(path);
  draw();
  strcpy(res_file,path);
  if (path[strlen(path)-1] != SLASH[0])
    strcat(res_file,SLASH); // To show it's a path more easily
}

int TFileSel::mychdir(int n) {
    char *old = NULL;
  if (n == 0) { // ..
    char *s = strrchr(path,SLASH[0]);
    if (s) {
      *s = 0;
      old = strdup(s+1);
#ifdef RAINE_WIN32
      if (s[-1] == SLASH[0]) { s[-1] = 0; // double \ in windows
	printf("double replace for %s\n",path);
      }
#endif
    }
#ifdef RAINE_WIN32
    if (strlen(path)==2) // only the drive letter is left
      strcat(path,SLASH);
#else
    if (!*path)
      strcpy(path,SLASH);
#endif
  } else
    sprintf(&path[strlen(path)],"%s%s",SLASH,menu[n].label);
  set_dir(path);
  if (old) {
      for (n=0; n<nb_items; n++)
	  if (!strcmp(menu[n].label,old)) {
	      sel = n;
	      break;
	  }
      free(old);
  }
  top = 0;
  if (top + rows - 1 < sel) top = sel-rows+1;

  return 0;
}

int TFileSel::myexec_file(int sel) {
  sprintf(res_file,"%s%s%s",path,SLASH,menu[sel].label);
  return 1;
}

void fsel(char *mypath, char **ext, char *res_str, char *title) {
  dlg = new TFileSel(mypath,mypath,ext,res_str,0,title);
  dlg->execute();
  delete dlg;
}

void fsel_save(char *mypath, char **ext, char *res_str, char *title) {
  dlg = new TFileSel(mypath,mypath,ext,res_str,SAVE,title);
  dlg->execute();
  delete dlg;
}

void dsel(char *mypath, char **ext, char *res_str,char *title) {
  dlg = new TFileSel(mypath,mypath,ext,res_str,ONLY_DIRS,title);
  dlg->execute();
  delete dlg;
}


