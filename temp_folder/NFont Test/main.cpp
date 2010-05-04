#include "stdafx.h"

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <time.h>

#include "SDL.h"

#ifndef PI
#define PI 3.14159265
#endif

#define DESIREDFPS 40
#define WAITTIME int(1000.0 / DESIREDFPS)

SDL_Surface* screen;

#include "NFont.h"

NFont RS20Font;
NFont RB14Font;
NFont* newNFont;
NFont* newNFontAnim;


void swirly(int& x, int& y, NFont::AnimData& data)
{
    int t = SDL_GetTicks();
    x += int(data.wordNum*5*cos(t/500.0));
    y += int(data.wordNum*20*sin(t/500.0));
}


void bouncy(int& x, int& y, NFont::AnimData& data)
{
    int t = SDL_GetTicks();
    y -= int(20*fabs(sin(t/250.0 + data.index/4.0)));
}


void wavy(int& x, int& y, NFont::AnimData& data)
{
    int t = SDL_GetTicks();
    y += int(20*sin(t/250.0 + data.index/4.0));
}


void circly(int& x, int& y, NFont::AnimData& data)
{
    int t = SDL_GetTicks();
    
    // Negate auto-placement
    x = data.startX;
    y = data.startY;
    
    float place = float(data.index + 1) / strlen(data.text);
    x += int(80*cos(place * 2*PI - t/1000.0));
    y += int(80*sin(place * 2*PI - t/1000.0));
}


void spirally(int& x, int& y, NFont::AnimData& data)
{
    int t = SDL_GetTicks();
    
    // Negate auto-placement
    x = data.startX;
    y = data.startY;
    
    float place = float(data.index + 1) / strlen(data.text);
    x += int(80*(place + .7)*cos(place * 2*PI - t/1000.0));
    y += int(40*(place + .7)*sin(place * 2*PI - t/1000.0));
}

void stretchy(int& x, int& y, NFont::AnimData& data)
{
    int t = SDL_GetTicks();
    
    float place = float(data.index) / strlen(data.text);
    x += int(80*(place - 0.5)*cos(t/500.0));
}


void rolly(int& x, int& y, NFont::AnimData& data)
{
    int t = SDL_GetTicks();
    
    float place = float(data.index) / strlen(data.text);
    x += int(80*cos((place - 0.5) * 2*PI - t/1000.0));
}


void shakeNjump(int& x, int& y, NFont::AnimData& data)
{
    int t = SDL_GetTicks();
    
    int num = t%1000;
    
    if(data.userVar != NULL && data.wordNum > *((int*)(data.userVar)))
    {
        if(num > 500)
            x += 20;
    }
    else
        x += int(3*sin(t/50.0));
}









bool initSDL(int w, int h, bool fullscreen)
{
	//printf("init SDL\n");
	if( SDL_Init(SDL_INIT_VIDEO ) < 0 ) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    atexit(SDL_Quit);
    
    if(fullscreen)
		screen = SDL_SetVideoMode(w, h, 0, SDL_SWSURFACE | SDL_FULLSCREEN);
	else
		screen = SDL_SetVideoMode(w, h, 0, SDL_SWSURFACE);

    if ( screen == NULL ) {
        printf("Couldn't set video mode %dx%d: %s\n", w, h, SDL_GetError());
		return false;
    }
    //printf(" running @ %dx%d %dbpp (done)\n", w,h,screen->format->BitsPerPixel);
	return true;
} //end bool initSDL(int w, int h, bool fullscreen)

void drawRect(SDL_Surface* surf, const SDL_Rect& rect, Uint32 color)
{
    SDL_Rect r;
    r.x = rect.x;
    r.y = rect.y;
    r.w = rect.w;
    r.h = 1;
    SDL_FillRect(surf, &r, color);
    r.y = rect.y + rect.h;
    SDL_FillRect(surf, &r, color);
    
    r.y = rect.y;
    r.w = 1;
    r.h = rect.h;
    SDL_FillRect(surf, &r, color);
    r.x = rect.x + rect.w;
    SDL_FillRect(surf, &r, color);
}





void start()
{
    bool drawDirty = false;
    
    // Main loop
    SDL_Event event;
    int frameStartTime;
    int frameTime;
    float fps = 0;
    bool done = 0;
    while (!done)
    {
        frameStartTime = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = true;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    done = true;
                }
                else if (event.key.keysym.sym == SDLK_d)
                {
                    drawDirty = !drawDirty;
                }
            }
        }



        SDL_FillRect(screen, NULL, 0);
        SDL_Rect r;
        r = RS20Font.draw(25, 25, "It's lame just sitting here.\nBy the way, the FPS = %.2f\n Press 'd' to show dirty rects.", fps);
        if(drawDirty)
            drawRect(screen, r, SDL_MapRGB(screen->format, 0, 255, 0));
        
        r = RS20Font.drawPos(300, 70, swirly, "Ha ha ha!");
        if(drawDirty)
            drawRect(screen, r, SDL_MapRGB(screen->format, 0, 255, 0));
        r = RS20Font.drawPos(70, 150, bouncy, "Let's bounce!");
        if(drawDirty)
            drawRect(screen, r, SDL_MapRGB(screen->format, 0, 255, 0));
        r = RS20Font.drawPos(150, 240, wavy, "Wheeeeeeeeeeeee!");
        if(drawDirty)
            drawRect(screen, r, SDL_MapRGB(screen->format, 0, 255, 0));
        r = RS20Font.drawPos(500, 250, circly, "Circle up, everybody!");
        if(drawDirty)
            drawRect(screen, r, SDL_MapRGB(screen->format, 0, 255, 0));
        r = RS20Font.drawPos(600, 450, spirally, "I'm going down the drain...");
        if(drawDirty)
            drawRect(screen, r, SDL_MapRGB(screen->format, 0, 255, 0));
        r = newNFontAnim->drawPos(200, 520, stretchy, "This is another newly colored NFont");
        if(drawDirty)
            drawRect(screen, r, SDL_MapRGB(screen->format, 0, 255, 0));
        r = RS20Font.drawPos(470, 100, rolly, "Roll it up and stretch it out.");
        if(drawDirty)
            drawRect(screen, r, SDL_MapRGB(screen->format, 0, 255, 0));
        
        int var = 3;
        NFont::setAnimData(&var);
        r = RS20Font.drawPos(90, 400, shakeNjump, "Here I am, over here.");
        if(drawDirty)
            drawRect(screen, r, SDL_MapRGB(screen->format, 0, 255, 0));
        
        NFont* plain = &RS20Font;
        r = plain->draw(30, 450, "This is\n just an NFont.");
        if(drawDirty)
            drawRect(screen, r, SDL_MapRGB(screen->format, 0, 255, 0));
        r = newNFont->draw(80, 560, "This is a newly colored NFont.");
        if(drawDirty)
            drawRect(screen, r, SDL_MapRGB(screen->format, 0, 255, 0));
        
        
        SDL_Flip(screen);  // Send to the monitor



        // Frame control
        frameTime = SDL_GetTicks()-frameStartTime;
        
        if (frameTime < WAITTIME)
            SDL_Delay(WAITTIME - frameTime);  // Keep framerate constant
        frameTime = SDL_GetTicks()-frameStartTime;
        if (frameTime != 0)
            fps = 1000.0f / frameTime;		//this is the framerate with vsync and the framebreak (should be equal to 1000/WAITTIME)
        else
            fps = 1111.11f;
        // End Frame Control

    }  // END main loop

    return;
} // END void start()



int _tmain(int argc, _TCHAR* argv[])
{
    SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center"));
    initSDL(800, 600, 0);

    srand(time(NULL));
    
    SDL_Surface* temp = SDL_LoadBMP("RedSystem20.bmp");
    if(temp == NULL)
    {
        printf("Error loading font.\n");
        return 0;
    }
    
    RS20Font.load(screen, temp);
    
    temp = SDL_LoadBMP("Bodoni18.bmp");
    if(temp == NULL)
    {
        printf("Error loading font.\n");
        return 0;
    }
    RB14Font.load(screen, temp);
    
    newNFont = new NFont;
    newNFontAnim = new NFont;
    
    SDL_Surface* surf = NFont::copySurface(RS20Font.getSurface());
    NFont::verticalGradient(surf, 0xFF0000, 0x0000FF, 11);
    newNFont->load(screen, surf);
    
    surf = NFont::copySurface(RB14Font.getSurface());
    NFont::verticalGradient(surf, 0x00FF00, 0x0000FF, 8);
    newNFontAnim->load(screen, surf);
    
    start();
}
