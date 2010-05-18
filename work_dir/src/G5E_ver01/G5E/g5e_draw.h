#ifndef HIC_DRAW
#define HIC_DRAW

#include "g5e_std.h"
#include "g5e_world.h"
#include "g5e_system.h"
#include "g5e_camera.h"
#include "g5e_time.h"
class G5EDrawObjects
{
public:
	G5EWorldMeshObject **gworldmeshobject;
	G5ETerrainObject **gterrainobject;
	int nworldmeshobject;
	int nterrainobject;
	Uint8 *meshdisplists;
	Uint8 *terraindisplists;
	G5EDrawObjects();
	~G5EDrawObjects();
	//void LoadTransform(int id);
	void LoadTransform(G5EWorldObject *wo);
	int addwmo(G5EWorldMeshObject *INgworldmeshobject);
	void removewmo(int id);
	int addto(G5ETerrainObject *INgterrainobject);
	void draw_meshslist();
	void draw_terrainslist();
	void draw_meshsdirect();
};
class G5EDraw
{

private:

public:
	G5ESystem *gsystem;
	G5EDrawObjects *gdrawobjects;
	G5ETimer *fpstimer;
	G5ECamera *gcamera;
	double fps;

	G5EDraw();
	~G5EDraw();
	int init(G5ESystem *INgsystem);
	int run();
	int run_end();
	int free();
};
#endif