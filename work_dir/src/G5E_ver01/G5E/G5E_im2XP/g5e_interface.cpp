#include "g5e_interface.h"

NFont nfont_system;
NFont* newNFont;
SDL_Surface* temp;

#pragma region interface_text_objects

G5EIStaticText::G5EIStaticText()
{
	G5EIStaticText(0,0,"",0,0);
}

G5EIStaticText::G5EIStaticText(int posx, int posy, char* str_text, int str_len, int fontsize)
{
	this->posx = posx;
	this->posy = posy;
	this->str_text = str_text;
	this->str_len = str_len;
	this->font_size = font_size;
}

G5EIStaticText::~G5EIStaticText()
{

}


G5EIDynamicText::G5EIDynamicText()
{
	G5EIDynamicText(0,0,NULL,0);
}

G5EIDynamicText::G5EIDynamicText(int posx, int posy, void* ptr_text, int fontsize)
{
	this->posx = posx;
	this->posy = posy;
	this->font_size = font_size;
	this->ptr_text = (void*) ptr_text;
}

G5EIDynamicText::~G5EIDynamicText()
{

}


void G5EIDynamicText::assign_textptr(int *int_ptr)
{
	this->ptr_text = (void*) int_ptr;
	this->ptr_type = 1;
}
void G5EIDynamicText::assign_textptr(float *float_ptr)
{
	this->ptr_text = (void*) float_ptr;
	this->ptr_type = 2;
}
void G5EIDynamicText::assign_textptr(double *double_ptr)
{
	this->ptr_text = (void*) double_ptr;
	this->ptr_type = 3;
}

void G5EIDynamicText::get_textstr(char *char_ptr)
{
	if(this->ptr_type == 1) /* int */
	{
		int int_buffer = 0;
		int_buffer = *((int*)(this->ptr_text));
		sprintf(char_ptr,"%d", int_buffer);
	}
	else if(this->ptr_type == 2) /* float */
	{
		float float_buffer = 0;
		float_buffer = *((float*)(this->ptr_text));
		sprintf(char_ptr,"%f", float_buffer);
	}
	else if(this->ptr_type == 3) /* double */
	{
		double double_buffer = 0;
		double_buffer = *((double*)(this->ptr_text));
		sprintf(char_ptr,"%f", double_buffer);
	}
}

#pragma endregion

// G5EIPanel *** G5E Interface Panel ***
#pragma region interface_panel_objects
G5EIPanel::G5EIPanel()
{
	G5EIPanel(0,0,0,0,true,0xffffffff);
}

G5EIPanel::G5EIPanel(int pwidth, int pheight, int pleft, int pbottom, bool pusebg, Uint32 pbgcolor)
{
	this->p_width = pwidth;
	this->p_height = pheight;
	this->p_left = pleft;
	this->p_top = pbottom;
	this->use_bg = pusebg;
	this->bgcolor = pbgcolor;

	this->static_texts = (G5EIStaticText*) malloc(sizeof(G5EIStaticText));
	this->dynamic_texts = (G5EIDynamicText*) malloc(sizeof(G5EIDynamicText));
	this->text_count = 0;
	this->dyntext_count = 0;

}
G5EIPanel::~G5EIPanel()
{
	free(this->static_texts);
	free(this->dynamic_texts);
}

int G5EIPanel::add_text(G5EIStaticText *new_text)
{
	this->static_texts = (G5EIStaticText*) realloc(this->static_texts, sizeof(G5EIPanel)*(this->text_count+1));
	this->static_texts[this->text_count] = *new_text;
	this->text_count++;

	return 0;
}

int G5EIPanel::add_dyntext(G5EIDynamicText *new_text)
{
	this->dynamic_texts = (G5EIDynamicText*) realloc(this->dynamic_texts, sizeof(G5EIPanel)*(this->dyntext_count+1));
	this->dynamic_texts[this->dyntext_count] = *new_text;
	this->dyntext_count++;

	return 0;
}

#pragma endregion

#pragma region interface_objects

G5EInterface::G5EInterface() {
	//this->if_panels = new G5EIPanel[1];
	this->if_panels = (G5EIPanel*) malloc(sizeof(G5EIPanel));
	this->panel_count = 0;
}

int G5EInterface::init_interface(SDL_Surface* msurface)
{
	this->if_surface = msurface;
	temp = SDL_LoadBMP("RedSystem20.bmp");
	//temp = SDL_LoadBMP("LtBlueTwCen18Border.bmp");
	//temp = SDL_LoadBMP("BlueAgency20.bmp");
	//temp = SDL_LoadBMP("BlackLucida20.bmp");

	if(temp == NULL)
    {
		//ERROR loading font
		return EXIT_FAILURE;
    }
    
    nfont_system.load(this->if_surface, temp);

	newNFont = new NFont;
        
    SDL_Surface* surf = NFont::copySurface(nfont_system.getSurface());
    NFont::verticalGradient(surf, 0xFF0000, 0x0000FF, 11);
    newNFont->load(this->if_surface, surf);
	

	return 0;
}

int G5EInterface::add_panel(G5EIPanel *new_panel)
{
	this->if_panels = (G5EIPanel*) realloc(this->if_panels, sizeof(G5EIPanel)*(this->panel_count+1));
	this->if_panels[this->panel_count] = *new_panel;
	this->panel_count++;

	return 0;
}

void G5EInterface::drawRect(SDL_Surface* surf, const SDL_Rect& rect, Uint32 color)
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

// *********** INTERFACE DRAW FUNCTION ***********
int G5EInterface::draw_interface() {
	SDL_FillRect(this->if_surface, NULL, 0x00ffffff);
	//SDL_Rect r;
	int i, n, tpx, tpy, int_buffer;
	char str_buffer[20];
    //r = nfont_system.draw(25, 25, "hello world");
	//drawRect(this->if_surface, r, SDL_MapRGB(this->if_surface->format, 0, 255, 0));

	//draw panels
	SDL_Rect panel_rect;
	for(i=0; i<this->panel_count; i++)
	{
		panel_rect.x = this->if_panels[i].p_left;
		panel_rect.y = this->if_panels[i].p_top;
		panel_rect.w = this->if_panels[i].p_width;
		panel_rect.h = this->if_panels[i].p_height;
		SDL_FillRect(this->if_surface, &panel_rect, this->if_panels[i].bgcolor);

		//draw panel text
		for(n=0; n<this->if_panels[i].text_count; n++)
		{
			tpx = this->if_panels[i].static_texts[n].posx + this->if_panels[i].p_left;
			tpy = this->if_panels[i].static_texts[n].posy + this->if_panels[i].p_top;
			nfont_system.draw(tpx, tpy, this->if_panels[i].static_texts[n].str_text);
		}

		for(n=0; n<this->if_panels[i].dyntext_count; n++)
		{
			tpx = this->if_panels[i].dynamic_texts[n].posx + this->if_panels[i].p_left;
			tpy = this->if_panels[i].dynamic_texts[n].posy + this->if_panels[i].p_top;

			this->if_panels[i].dynamic_texts[n].get_textstr(str_buffer);
			nfont_system.draw(tpx, tpy, str_buffer);
		}
	}

	//to be moved & optimized
/*	GLuint texture;			// This is a handle to our texture object
	SDL_Surface *surface;	// This surface will tell us the details of the image
	GLenum texture_format;
	GLint  nOfColors;
*/

	/* atm unused
	// get the number of channels in the SDL surface
    nOfColors = this->if_surface->format->BytesPerPixel;
    if (nOfColors == 4)     // contains an alpha channel
    {
            if (this->if_surface->format->Rmask == 0x000000ff)
                    texture_format = GL_RGBA;
            else
                    texture_format = GL_BGRA;
    } else if (nOfColors == 3)     // no alpha channel
    {
            if (this->if_surface->format->Rmask == 0x000000ff)
                    texture_format = GL_RGB;
            else
                    texture_format = GL_BGR;
    } else {
            //not truecolor
            // this error should not go unhandled
		int err_debug_catch = 1;
    }
    */

	glColor3ub(255, 255, 255); // important !
	glEnable( GL_TEXTURE_2D );
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	 
	glTexImage2D(GL_TEXTURE_2D, 0, 4, this->if_surface->w, this->if_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->if_surface->pixels);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->if_surface->w, this->if_surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, this->if_surface->pixels);
	
	

	//glColor3d(0, 1.0, 0);
	
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
		glLoadIdentity();
		//gluPerspective(45.0f, 4.0f/3.0f, 0.1f, 10.f);
		//gluOrtho2D (0, 20, 0, 20);
		
		glBegin(GL_QUADS);
			glTexCoord2d(0, 1);  
			glVertex3d(-1, -1, 0);
			glTexCoord2d(0, 0);
			glVertex3d(-1, 1, 0);
			glTexCoord2d(1, 0); 
			glVertex3d(1, 1, 0);
			glTexCoord2d(1, 1);
			glVertex3d(1, -1, 0);	
		glEnd();
		

		/*gluOrtho2D (0, 1000, 0, 1000);
		glBegin(GL_QUADS);
			glTexCoord2d(0, 1);  
			glVertex3d(0, 0, 0);
			glTexCoord2d(0, 0);
			glVertex3d(0, 10, 0);
			glTexCoord2d(1, 0); 
			glVertex3d(10, 10, 0);
			glTexCoord2d(1, 1);
			glVertex3d(10, 0, 0);	
		glEnd();*/

	glPopMatrix(); //nimm das hier mal raus xD


	glDeleteTextures(1, &texture);
//	SDL_FreeSurface(this->if_surface);

	return 0;
}

#pragma endregion