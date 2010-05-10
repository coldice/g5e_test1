#include "g5e_draw.h"

G5EDrawObjects::G5EDrawObjects()
{
	nworldmeshobject = 0;
	gworldmeshobject = (G5EWorldMeshObject**) malloc(sizeof(G5EWorldMeshObject*));
	meshdisplists = (Uint8*) malloc(sizeof(Uint8));
	*meshdisplists = 0;

	nterrainobject = 0;
	gterrainobject = (G5ETerrainObject**) malloc(sizeof(G5ETerrainObject*));
	terraindisplists = (Uint8*) malloc(sizeof(Uint8));
	*terraindisplists = 0;
}
/*void G5EDrawObjects::LoadTransform(int id)
{
	glScalef(this->gworldmeshobject[id]->scale.x+1,this->gworldmeshobject[id]->scale.y+1,this->gworldmeshobject[id]->scale.z+1);
	glTranslatef(this->gworldmeshobject[id]->translation.x,this->gworldmeshobject[id]->translation.y,this->gworldmeshobject[id]->translation.z);
	glRotatef(this->gworldmeshobject[id]->rotate.x,1.0f, 0.0f, 0.0f);
	glRotatef(this->gworldmeshobject[id]->rotate.y,0.0f, 1.0f, 0.0f);
	glRotatef(this->gworldmeshobject[id]->rotate.z,0.0f, 0.0f, 1.0f);
}*/
void G5EDrawObjects::LoadTransform(G5EWorldObject *wo)
{
	glScalef(wo->scale.x+1,wo->scale.y+1,wo->scale.z+1);
	glTranslatef(wo->translation.x,wo->translation.y,wo->translation.z);
	glRotatef(wo->rotate.x,1.0f, 0.0f, 0.0f);
	glRotatef(wo->rotate.y,0.0f, 1.0f, 0.0f);
	glRotatef(wo->rotate.z,0.0f, 0.0f, 1.0f);
}
int G5EDrawObjects::addwmo(G5EWorldMeshObject *INgworldmeshobject)
{
	this->nworldmeshobject++;
	this->gworldmeshobject = (G5EWorldMeshObject**) realloc(this->gworldmeshobject, sizeof(G5EWorldMeshObject*)*this->nworldmeshobject);
	this->gworldmeshobject[this->nworldmeshobject-1] = INgworldmeshobject;
	this->meshdisplists = (Uint8*) realloc(this->meshdisplists, sizeof(Uint8)*this->nworldmeshobject);
	this->meshdisplists[this->nworldmeshobject-1] = glGenLists(1);

	glNewList(this->meshdisplists[this->nworldmeshobject-1],GL_COMPILE);
		glBegin(GL_TRIANGLES);
			glColor3d(1, 0, 0);
			for(int n=0;n<INgworldmeshobject->gmeshobject->ntriangles*3;n++)
			{
				glVertex3d(INgworldmeshobject->gmeshobject->points[INgworldmeshobject->gmeshobject->indices[n]].x,INgworldmeshobject->gmeshobject->points[INgworldmeshobject->gmeshobject->indices[n]].y, INgworldmeshobject->gmeshobject->points[INgworldmeshobject->gmeshobject->indices[n]].z);
			}
		glEnd();
	glEndList();


	return nworldmeshobject-1;
}
int G5EDrawObjects::addto(G5ETerrainObject *INgterrainobject)
{
	this->nterrainobject++;
	this->gterrainobject = (G5ETerrainObject**) realloc(this->gterrainobject, sizeof(G5ETerrainObject*)*this->nterrainobject);
	this->gterrainobject[this->nterrainobject-1] = INgterrainobject;
	this->terraindisplists = (Uint8*) realloc(this->terraindisplists, sizeof(Uint8)*this->nterrainobject);
	this->terraindisplists[this->nterrainobject-1] = glGenLists(1);

	glNewList(this->terraindisplists[this->nterrainobject-1],GL_COMPILE);
		glBegin(GL_TRIANGLES);  // Eventuell noch für Trianglestrip definieren
			int dX = INgterrainobject->getdimX();
			int dZ = INgterrainobject->getdimZ();
			float cfactor = (1/(INgterrainobject->getmax()-INgterrainobject->getmin()));   // Vorübergehend
			float min = INgterrainobject->getmin();
			for(int n1 = 0;n1<dX-1;n1++)
			{
				for(int n2 = 0;n2<dZ-1;n2++)
				{
					glColor3d(0,0.05+cfactor*(INgterrainobject->heightmap[n1+dX*n2]-min),0); // Vorübergehend
					glVertex3d(-(dX/2)+n1,INgterrainobject->heightmap[n1+dX*n2],-(dZ/2)+n2);
					glColor3d(0,0.05+cfactor*(INgterrainobject->heightmap[n1+1+dX*n2]-min),0); // Vorübergehend
					glVertex3d(-(dX/2)+n1+1,INgterrainobject->heightmap[n1+1+dX*n2],-(dZ/2)+n2);
					glColor3d(0,0.05+cfactor*(INgterrainobject->heightmap[n1+dX*(n2+1)]-min),0); // Vorübergehend
					glVertex3d(-(dX/2)+n1,INgterrainobject->heightmap[n1+dX*(n2+1)],-(dZ/2)+n2+1);

					glColor3d(0,0.05+cfactor*(INgterrainobject->heightmap[n1+1+dX*n2]-min),0); // Vorübergehend
					glVertex3d(-(dX/2)+n1+1,INgterrainobject->heightmap[n1+1+dX*n2],-(dZ/2)+n2);
					glColor3d(0,0.05+cfactor*(INgterrainobject->heightmap[n1+1+dX*n2+1]-min),0); // Vorübergehend
					glVertex3d(-(dX/2)+n1+1,INgterrainobject->heightmap[n1+1+dX*(n2+1)],-(dZ/2)+n2+1);
					glColor3d(0,0.05+cfactor*(INgterrainobject->heightmap[n1+dX*n2+1]-min),0); // Vorübergehend
					glVertex3d(-(dX/2)+n1,INgterrainobject->heightmap[n1+dX*(n2+1)],-(dZ/2)+n2+1);

				}
			}
		glEnd();
	glEndList();


	return nterrainobject-1;
}
void G5EDrawObjects::removewmo(int id)
{
		
}
void G5EDrawObjects::draw_meshslist()
{
	for(int i=0;i<nworldmeshobject;i++)
	{
		glPushMatrix();
			this->LoadTransform(gworldmeshobject[i]);
			glCallList(this->meshdisplists[i]);
		glPopMatrix();
	}
}
void G5EDrawObjects::draw_terrainslist()
{
	for(int i=0;i<nterrainobject;i++)
	{
		glPushMatrix();
			this->LoadTransform(gterrainobject[i]);
			glCallList(this->terraindisplists[i]);
		glPopMatrix();
	}
}
void G5EDrawObjects::draw_meshsdirect()
{
	for(int i=0;i<nworldmeshobject;i++)
	{
		glPushMatrix();
			this->LoadTransform(gworldmeshobject[i]);
			glBegin(GL_TRIANGLES);
				glColor3d(1, 0, 0);
				for(int n=0;n<gworldmeshobject[i]->gmeshobject->ntriangles*3;n++)
				{
					glVertex3d(gworldmeshobject[i]->gmeshobject->points[gworldmeshobject[i]->gmeshobject->indices[n]].x,gworldmeshobject[i]->gmeshobject->points[gworldmeshobject[i]->gmeshobject->indices[n]].y, gworldmeshobject[i]->gmeshobject->points[gworldmeshobject[i]->gmeshobject->indices[n]].z);
				}
			glEnd();
		glPopMatrix();
	}	
}
G5EDrawObjects::~G5EDrawObjects()
{
	free(*gworldmeshobject);
	free(*gterrainobject);
	free(meshdisplists);
	free(terraindisplists);
}

G5EDraw::G5EDraw()
{
	gdrawobjects = new(G5EDrawObjects);
	gcamera = new G5ECamera();
}

G5EDraw::~G5EDraw(){}

int G5EDraw::init(G5ESystem *INgsystem)
{
	this->gsystem = INgsystem;
	this->fpstimer = new G5ETimer();
	this->fps = 0;
	this->gtext.init();	
	return TRUE;
}
	// draw run
	// called by main loop
int G5EDraw::run() //                  
{
	/* Zurücksetzen der Einstellungen, der Pipelines und des Bildpuffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	/* Laden der Kameraeinstellungen */
	gcamera->LoadPerspective(); 
	gcamera->LoadTransformation();

	
	/* Zeichnen des Meshobjects über die drawlist */
	gdrawobjects->draw_terrainslist();	
	gdrawobjects->draw_meshslist();
	glTranslatef(0.0f,0.0f,-5.0f);
	gdrawobjects->draw_meshsdirect();


	/* Momentane FPS Darstellung */
	if(this->fpstimer->check(0.1,1))
	{                          
		fps = this->gsystem->gtime->getffps();
	}
	gtext.print(100,100, 100, 0, 0, 0.1f, "%.1f", fps);		

	/* Diesdas*/
	gdrawobjects->gworldmeshobject[0]->translatef(0.01f,0,0);	

	//swap sdl buffer
	//SDL_GL_SwapBuffers(); -> moved to run_end


	/* Momentane Tastarturabfrage */
	if(gsystem->keystates[SDLK_UP]) gcamera->rotateUp(0.5f);//gcam->rotateX(-0.1f);
	if(gsystem->keystates[SDLK_DOWN]) gcamera->rotateDown(0.5f);//gcam->rotateX(0.1f);
	if(gsystem->keystates[SDLK_LEFT]) gcamera->rotateLeft(0.5f);//gcam->rotateY(-0.1f);
	if(gsystem->keystates[SDLK_RIGHT]) gcamera->rotateRight(0.5f);//gcam->rotateY(0.1f);
	if(gsystem->keystates[SDLK_q]) gcamera->rollLeft(0.5f);//gcam->rotateZ(-0.1f);
	if(gsystem->keystates[SDLK_e]) gcamera->rollRight(0.5f);//gcam->rotateZ(0.1f);
	if(gsystem->keystates[SDLK_w]) gcamera->moveFor(0.1f);//gcam->moveForwards(0.1f);
	if(gsystem->keystates[SDLK_s]) gcamera->moveBack(0.1f);//gcam->moveBackwards(0.1f);
	if(gsystem->keystates[SDLK_a]) gcamera->moveLeft(0.1f);//gcam->moveLeft(0.01f);
	if(gsystem->keystates[SDLK_d]) gcamera->moveRight(0.1f);//gcam->moveRight(0.01f);
	if(gsystem->keystates[SDLK_PAGEUP]) gcamera->zoom(0.05f);
	if(gsystem->keystates[SDLK_PAGEDOWN]) gcamera->zoom(-0.05f);
	if(gsystem->keystates[SDLK_r]) gcamera->free();
	if(gsystem->keystates[SDLK_t]) gcamera->center(this->gdrawobjects->gworldmeshobject[0]);
	return 0;
}

int G5EDraw::run_end() {
	SDL_GL_SwapBuffers();

	return 0;
}
int G5EDraw::free()
{
	this->gtext.free();
	delete this->fpstimer;
	delete this->gcamera;
	delete this->gdrawobjects;
	return 1;
}
