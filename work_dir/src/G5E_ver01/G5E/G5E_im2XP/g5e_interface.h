#ifndef HIC_INTERFACE
#define HIC_INTERFACE
#include <SDL.h>

class G5EIStaticText
{
public:
	G5EIStaticText();
	~G5EIStaticText();

	char *str_text;
	int str_len;
	int font_size;
	int posx, posy;
};


class G5EIPanel
{
public:
	G5EIPanel();
	~G5EIPanel();

	int add_text(G5EIStaticText new_text);

private:
	G5EIStaticText *sta_text_arr;
};

//simple interface class
class G5EInterface
{
public:
	G5EInterface();
	~G5EInterface();

	SDL_Surface *if_surface;
};

#endif