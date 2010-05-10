#ifndef HIC_SYSTEM
#define HIC_SYSTEM

#include "g5e_std.h"
class G5ESystem
{
private:
	int s_width, s_height;
	bool s_window;
	SDL_Event event;
    
public:
	G5ETime *gtime;
	//G5ETimer *gtimer;
	//G5EDraw *gdraw;              Pointer auf das maindrawobject, aber bin mir nicht allzu sicher ob das zu realisieren ist, glaube aber, dass es gelegentlich nötig ist, darauf zuzugreifen
	Uint8 *keystates;
	bool runstate;
	SDL_Surface* surface;
	SDL_Surface* ifsurface;
	/*	G5ESystem(int width, int height, bool window) {    
		s_width = width;
		s_height = height;
		s_window = window;
	}*/
	G5ESystem();
	~G5ESystem();

	int init();//G5EDraw *INgdraw) // übergabe des Draw-Pointers rauskommentiert
	int init_sdlwindow();
	int free();        //  Das kann eig. auch in den Destruktor oder nich?
	int run();
};
#endif