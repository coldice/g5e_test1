#ifndef HIC_INTERFACE
#define HIC_INTERFACE
#include <SDL.h>
#include <SDL_opengl.h>
#include "NFont.h"

class G5EIStaticText
{
public:
	G5EIStaticText();
	G5EIStaticText(int posx, int posy, char* str_text, int str_len, int fontsize);
	~G5EIStaticText();

	char *str_text;
	int str_len;
	int font_size;
	int posx, posy;
};

class G5EIDynamicText
{
public:
	G5EIDynamicText();
	G5EIDynamicText(int posx, int posy, void* ptr_text, int fontsize);
	~G5EIDynamicText();

	void *ptr_text;
	int font_size;
	int posx, posy;
	int ptr_type; //0=invalid/NULL, 1=int, 2=float, 3=double

	void assign_textptr(int *int_ptr);
	void assign_textptr(float *double_ptr);
	void assign_textptr(double *double_ptr);
	void get_textstr(char *char_ptr);
};


class G5EIPanel
{
public:
	G5EIPanel();
	G5EIPanel(int pwidth, int pheight, int pleft, int pbottom, bool pusebg, Uint32 pbgcolor);
	~G5EIPanel();

	int add_text(G5EIStaticText *new_text);
	int add_dyntext(G5EIDynamicText *new_text);
	int p_width;
	int p_height;
	int p_left;
	int p_top;
	
	bool use_bg;
	Uint32 bgcolor;

	G5EIStaticText *static_texts;
	G5EIDynamicText *dynamic_texts;
	int text_count;
	int dyntext_count;
	

private:
};

//simple interface class
class G5EInterface
{
public:
	G5EInterface();
	~G5EInterface();
	
	

	int init_interface(SDL_Surface* msurface);
	int draw_interface();
	
	int add_panel(G5EIPanel *new_panel);

	SDL_Surface *if_surface;
	G5EIPanel *if_panels;
	int panel_count;

	bool isactive;

	// font used vars
	GLuint texture;
	SDL_Surface *surface;
	GLenum texture_format;
	GLint  nOfColors;

	void drawRect(SDL_Surface* surf, const SDL_Rect& rect, Uint32 color); //change

};

#endif