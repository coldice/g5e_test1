#ifndef HIC_WORLD
#define HIC_WORLD

#include "g5e_std.h"
class G5EWorld
{
public:
//	G5EMeshObject mesh_arr[] = new G5EMeshObject[];           crap?
};
class G5ETriangle
{
public:
	G5EPoint p[3];
	G5ETriangle();
};
class G5EMeshObject// : public G5EWorldObject
{
public:
	int ntriangles, npoints;
	G5EPoint *points;
	int *indices;
	G5EMeshObject();
	int add(G5EPoint *point);
};
class G5EWorldObject
{
public:
	G5EPoint rotate;
	G5EPoint translation;
	G5EPoint scale;
	G5EWorldObject();
	void rotatef(float INrotX, float INrotY, float INrotZ);
	void translatef(float INtransX, float INtransY, float INtransZ);
	void scalef(float INscaleX, float INscaleY, float INscaleZ);
};
class G5EWorldMeshObject : public G5EWorldObject
{
public:
	G5EMeshObject *gmeshobject;
	G5EWorldMeshObject();
	G5EWorldMeshObject(G5EMeshObject *INgmeshobject);
};
class  G5ETerrainObject : public G5EWorldObject
{
private:
	int dimX,dimZ;
	float maxheight,minheight;
public:
	float *heightmap;
	G5ETerrainObject();
	G5ETerrainObject(float INmaxheight, float INminheight);
	int gettxtdata(char *file, int INsizex, int INsizez, int step);
	int getdimX();
	int getdimZ();
	float getmax();
	float getmin();
	float getHeight(int x, int z);
	int setHeight(float height, int x, int z);
};
#endif