#ifndef HIC_TEXT
#define HIC_TEXT

#include "g5e_std.h"
#include <SDL_ttf.h>
#pragma comment(lib, "SDL_ttf.lib")

class G5EText
{
private:
	TTF_Font *font;
public:
	G5EText();
	int init();
	int free();
	int print(int r, int g, int b, float X, float Y, float height, const char *fmt, ...);				
};
#endif