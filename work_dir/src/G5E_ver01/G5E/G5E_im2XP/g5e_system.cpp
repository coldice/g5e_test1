#include "g5e_system.h"
G5ESystem::G5ESystem()
{
	s_width=800;
	s_height=600;
	runstate=false;

}

G5ESystem::~G5ESystem(){}

	//func
int G5ESystem::init()//G5EDraw *INgdraw) // übergabe des Draw-Pointers rauskommentiert
{
	//this->gdraw=INgdraw;          // DrawPointer
	init_sdlwindow();
	runstate = true;
	//gtimer = new G5ETimer();
	gtime = new G5ETime();
	keystates = SDL_GetKeyState(NULL);
	//GL INIT - TO BE MOVED
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	glClearColor(0, 0, 0, 1);

	glViewport(0, 0, 800, 600);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);        
	   
	glDepthFunc(GL_LEQUAL); 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);



	//END GL INIT
	return 0;
}
	// func: init_sdlwindow() >SDL Init window
int G5ESystem::init_sdlwindow()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_WM_SetCaption("engine test 5", 0);
	this->surface = SDL_SetVideoMode(s_width, s_height, 32, SDL_OPENGL);

	return 0;
}
int G5ESystem::free()        //  Das kann eig. auch in den Destruktor oder nich?
{
	delete gtime;
	//delete gtimer;
	return 0;
}


int G5ESystem::run()
{
	if(SDL_PollEvent(&event))
    {
		switch(event.type)
		{
		case SDL_QUIT:
			runstate = false;
		break;

		case SDL_KEYDOWN:
			keystates = SDL_GetKeyState(NULL);
		break;
		case SDL_KEYUP:
			keystates = SDL_GetKeyState(NULL);
		break;
			switch(event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				runstate = false;
			break;

			case SDLK_UP:

			break;

			}
			break;
		}
			
				/*if(event.type == SDL_QUIT) runstate = false;

            else if(event.type == SDL_KEYDOWN)
                if(event.key.keysym.sym == SDLK_ESCAPE)runstate = false;*/
    }
	gtime->run();
	if(keystates[SDLK_ESCAPE]) runstate = false;

	return 0;
}
