#include "g5e_text.h"
G5EText::G5EText()
{
	font = NULL;
}
int G5EText::init()
{
	TTF_Init();
	this->font=TTF_OpenFont("arial.ttf", 16);
	if(this->font == NULL) return 0;
	TTF_SetFontStyle(this->font, TTF_STYLE_NORMAL);
	return 1;
}
int G5EText::free()
{
	TTF_CloseFont(this->font);
	TTF_Quit();
	return 1;
}
int G5EText::print(int r, int g, int b, float X, float Y, float height, const char *fmt, ...)				
{
	char		text[256];				
	va_list		ap;					


	if (fmt == NULL)				
		return 0;						

	va_start(ap, fmt);					
		vsprintf_s(text,sizeof(text), fmt, ap);			
	va_end(ap);	

	SDL_Color color={r,g,b};
	SDL_Surface *surface = TTF_RenderText_Blended(this->font, text, color);

	unsigned int Texture = 0;
 
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
		
	float v = (float)(surface->w)/(float)(surface->h);
	X=X-0.555f;
	Y=Y+0.415f;
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
		glLoadIdentity();
		gluPerspective(45.0f, 4.0f/3.0f, 0.1f, 10.f);
		glBegin(GL_QUADS);
			glTexCoord2d(0, 0);  
			glVertex3d(X, Y, -1.0);
			glTexCoord2d(1, 0);
			glVertex3d(X+v*height, Y, -1.0);
			glTexCoord2d(1, 1); 
			glVertex3d(X+v*height, Y-height, -1.0);
			glTexCoord2d(0, 1);
			glVertex3d(X, Y-height, -1.0);	
		glEnd();
	glPopMatrix();

	glDeleteTextures(1, &Texture);
	SDL_FreeSurface(surface);
	return 1;
}
