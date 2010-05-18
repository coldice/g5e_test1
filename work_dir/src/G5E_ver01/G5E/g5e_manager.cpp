#include "g5e_manager.h"


G5EManagerMOList::G5EManagerMOList()
{
	this->mmo = new G5EManagerMO;
}
G5EManagerMOList::~G5EManagerMOList()
{
	delete mmo;
}
G5EStaticMeshManager::G5EStaticMeshManager()
{
	this->first = NULL;
	this->last = NULL;
}
G5EStaticMeshManager::~G5EStaticMeshManager()
{

}
int G5EStaticMeshManager::createMesh(G5EPoint *points, char name[32])
{
	if(this->first == NULL)
	{
		this->first = new G5EManagerMOList;
		this->first->prev = NULL;
		this->first->next = NULL;
		this->first->mmo->id = 1;
		strcpy_s(this->first->mmo->name,32, name);
		this->first->mmo->mesh.add(points);
		this->last = this->first;
		LOG_MESH("Created", this->first->mmo->name, this->first->mmo->id);
		return 1;
	}
	else
	{
		G5EManagerMOList *temp = first;
		while(temp->next!=NULL)	temp = temp->next;

		temp->next = new G5EManagerMOList;
		temp->next->prev = temp;
		temp = temp->next;
		temp->next = NULL;
		temp->mmo->id = last->mmo->id+1;
		strcpy_s(temp->mmo->name,32, name);
		temp->mmo->mesh.add(points);
		LOG_MESH("Created", temp->mmo->name, temp->mmo->id);
		return temp->mmo->id;
	}
}
void G5EStaticMeshManager::deleteMesh(int id)
{
	G5EManagerMOList *temp = this->first;
	while(temp->mmo->id!=id && temp->next!=NULL)	temp = temp->next;
	if(temp->mmo->id!=id && temp->next!=NULL) return;
	
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	LOG_MESH("Deleted", temp->mmo->name, temp->mmo->id) 
	delete temp;
}
void G5EStaticMeshManager::deleteMesh(char name[32])
{
	G5EManagerMOList *temp = this->first;
	while(strcmp(temp->mmo->name,name) && temp->next!=NULL)	temp = temp->next;
	if(strcmp(temp->mmo->name,name) && temp->next!=NULL) return;
	
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	LOG_MESH("Deleted", temp->mmo->name, temp->mmo->id)
	delete temp;
}
int G5EStaticMeshManager::getId(char name[32])
{
	G5EManagerMOList *temp = this->first;
	while(strcmp(temp->mmo->name,name) && temp->next!=NULL)	temp = temp->next;
	if(strcmp(temp->mmo->name,name) && temp->next!=NULL) return 0;
	else return temp->mmo->id;
}
void G5EStaticMeshManager::getMesh(G5EMeshObject **mesh, int id)
{
	G5EManagerMOList *temp = this->first;
	while(temp->mmo->id!=id && temp->next!=NULL)	temp = temp->next;
	if(temp->mmo->id!=id && temp->next!=NULL) *mesh = NULL;
	else *mesh = &(temp->mmo->mesh);
}
void G5EStaticMeshManager::getMesh(G5EMeshObject **mesh, char name[32])
{
	G5EManagerMOList *temp = this->first;
	while(strcmp(temp->mmo->name,name) && temp->next!=NULL)	temp = temp->next;
	if(strcmp(temp->mmo->name,name) && temp->next!=NULL) *mesh = NULL;
	else *mesh = &(temp->mmo->mesh);
}
void G5EStaticMeshManager::init_primitives()
{
	this->createPyramid4();
}
int G5EStaticMeshManager::createPyramid4()
{
	G5EPoint points[18] =	{	
							G5EPoint(0.0f,0.5f,0.0f), G5EPoint(-0.5f,-0.5f,0.5f), G5EPoint(0.5f,-0.5f,0.5f),
							G5EPoint(0.0f,0.5f,0.0f), G5EPoint(0.5f,-0.5f,-0.5f), G5EPoint(0.5f,-0.5f,0.5f),
							G5EPoint(0.0f,0.5f,0.0f), G5EPoint(-0.5f,-0.5f,-0.5f), G5EPoint(0.5f,-0.5f,-0.5f),
							G5EPoint(0.0f,0.5f,0.0f), G5EPoint(-0.5f,-0.5f,0.5f), G5EPoint(-0.5f,-0.5f,-0.5f),
							G5EPoint(-0.5f,-0.5f,0.5f), G5EPoint(-0.5f,-0.5f,-0.5f), G5EPoint(0.5f,-0.5f,-0.5f),
							G5EPoint(-0.5f,-0.5f,0.5f), G5EPoint(0.5f,-0.5f,-0.5f), G5EPoint(0.5f,-0.5f,0.5f)
							};
	return this->createMesh(points, "pyramid4");
}
G5EManagerWMOList::G5EManagerWMOList()
{
	this->mwmo = new G5EManagerWMO;
}
G5EManagerWMOList::~G5EManagerWMOList()
{
	delete this->mwmo;
}
G5EStaticWorldManager::G5EStaticWorldManager(G5EStaticMeshManager *INsmm)
{
	this->first = NULL;
	this->last = NULL;
	this->smm = INsmm;
	for(int n=0;n<MAXWORLDOBJECTS;n++) this->mwmo[n] = NULL;
}
G5EStaticWorldManager::~G5EStaticWorldManager()
{
	last = first;
	while(first->next != NULL)
	{
		delete first;
		last = last->next;
		first = last;
	}
	delete first;
}

int G5EStaticWorldManager::createWorldMesh(int meshid, char name[32])
{
	G5EMeshObject *mesh = NULL;
	this->smm->getMesh(&mesh, meshid);
	int id = 0;
	while(this->mwmo[id] != NULL) id++;
	if(this->first == NULL)
	{
		this->first = new G5EManagerWMOList();
		first->mwmo->wmo = new G5EWorldMeshObject(mesh);
		first->mwmo->id = id;
		strcpy_s(first->mwmo->name,32, name);
		first->next = NULL;
		first->prev = NULL;
		last = first;
		this->mwmo[id] = first;
	}
	else
	{
		last->next = new G5EManagerWMOList();
		last->next->prev = last;
		last = last->next;
		last->mwmo->wmo = new G5EWorldMeshObject(mesh);
		last->mwmo->id = id;
		strcpy_s(last->mwmo->name,32, name);
		last->next = NULL;
		if(first->next == NULL) first->next = last;
		this->mwmo[id] = last;
	}
	g5e_log_msg("00FF00", "WorldMesh", "Created: %d, %s", id, name);
	return id;
}
void G5EStaticWorldManager::deleteWorldMesh(int id)
{
	G5EManagerWMOList *temp = this->mwmo[id];
	if(temp == last)
	{
		last = temp->prev;
		last->prev->next = last;
	}
	else if(temp == first)
	{
		first = temp->next;
		first->next->prev = first;
	}
	else
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	this->mwmo[id] = NULL;
	g5e_log_msg("00FF00", "WorldMesh", "Deleted: %d, %s", temp->mwmo->id, temp->mwmo->name);
	delete temp;
	
}
void G5EStaticWorldManager::deleteWorldMesh(char name[32])
{
	G5EManagerWMOList *temp = this->first;
	while(strcmp(temp->mwmo->name,name) && temp->next!=NULL)	temp = temp->next;
	if(strcmp(temp->mwmo->name,name) && temp->next!=NULL) return;
	this->mwmo[temp->mwmo->id] = NULL;
	if(temp == last)
	{
		last = temp->prev;
		last->prev->next = last;
	}
	else if(temp == first)
	{
		first = temp->next;
		first->next->prev = first;
	}
	else
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	g5e_log_msg("00FF00", "WorldMesh", "Deleted: %d, %s", temp->mwmo->id, temp->mwmo->name);
	delete temp;
}
int G5EStaticWorldManager::getId(char name[32])
{
	G5EManagerWMOList *temp = this->first;
	while(strcmp(temp->mwmo->name,name) && temp->next!=NULL)	temp = temp->next;
	if(strcmp(temp->mwmo->name,name) && temp->next!=NULL) return 0;
	else return temp->mwmo->id;
}

void G5EStaticWorldManager::getWorldMesh(G5EWorldMeshObject **worldmesh, int id)
{
	*worldmesh = (this->mwmo[id]->mwmo->wmo);
}
void G5EStaticWorldManager::getWorldMesh(G5EWorldMeshObject **worldmesh, char name[32])
{
	G5EManagerWMOList *temp = this->first;
	while(strcmp(temp->mwmo->name,name) && temp->next!=NULL)	temp = temp->next;
	if(strcmp(temp->mwmo->name,name) && temp->next!=NULL) return;
	else *worldmesh = (temp->mwmo->wmo);
}