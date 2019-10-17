#ifndef TFONT_CPP
#define TFONT_CPP

#include <SDL_ttf.h>

extern int min_font_size;
void save_font_config();
void read_font_config();

class TFont {
  protected:
    char *loaded_font;
    int charWidth,charHeight;
    TFont(char *font);
    void select_ideal_font(int width, int height);
    int is_utf;
  public:
    TFont(int size,char *myfont);
    TFont(int ideal_width, int ideal_height);
    virtual ~TFont();
    virtual int get_font_width() { return (charWidth ? charWidth : 8); }
    virtual int get_font_height() { return (charHeight ? charHeight : 8); }
    virtual void dimensions(const char *s,int *w, int *h);
    virtual void put_string(int x, int y, const char *s, int color);
    virtual void put_string(int x, int y, const char *s, int color, int bgcolor);
    virtual void surf_string_tr(SDL_Surface *surf,int x, int y, const char *s, int color, int w = 0);
    virtual void surf_string(SDL_Surface *surf,int x, int y, const char *s, int color, int bgcolor, int w = 0);
    virtual void load_font(char *myfont);
    virtual void set_style(int style) {};
    virtual void set_utf(int utf) {
	is_utf = utf;
    }
};

class TFont_ttf :
  public TFont
{
  protected:
    TTF_Font *ttf;
  public:
    TFont_ttf(int size=12,char *font="Vera.ttf");
    virtual ~TFont_ttf();
    virtual void dimensions(const char *s, int *w, int *h);
    virtual void put_string(int x, int y, const char *s, int color);
    virtual void put_string(int x, int y, const char *s, int color, int bgcolor);
    virtual void surf_string_tr(SDL_Surface *surf,int x, int y, const char *s, int color, int w = 0);
    virtual void surf_string(SDL_Surface *surf,int x, int y, const char *s, int color, int bgcolor, int w = 0);
    virtual void load_font(char *myfont);
    virtual void set_style(int style)
    {
	TTF_SetFontStyle(ttf,style);
    }
};

#endif

