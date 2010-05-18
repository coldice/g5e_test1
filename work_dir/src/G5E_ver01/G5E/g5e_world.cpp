#include "g5e_world.h"

G5ETriangle::G5ETriangle()
{
	p[0]=G5EPoint();
	p[1]=G5EPoint();
	p[2]=G5EPoint();
}

G5EMeshObject::G5EMeshObject()
{
	ntriangles = 0;
	npoints = 0;
	points = (G5EPoint*) malloc(sizeof(G5EPoint));
	*points = G5EPoint(0,0,0); 
	indices = (int*) malloc(sizeof(int));
	*indices = 0;
}
int G5EMeshObject::add(G5EPoint *point)
{
	indices = (int*) realloc(indices, sizeof(int)*(ntriangles+1)*3);
	int n=0, newIndex=-1;
	while(n<npoints && newIndex == -1)
	{
		if(points[n] == point[0]) newIndex = n;
		n++;
	}
	if(newIndex == -1)
	{
		npoints++;
		points = (G5EPoint*) realloc(points, sizeof(G5EPoint)*(npoints));
		points[npoints-1] = point[0];
		indices[ntriangles*3] = npoints-1;
	}
	else indices[ntriangles*3] = newIndex;
	newIndex = -1;
	n = 0;
	while(n<npoints && newIndex == -1)
	{
		if(points[n] == point[1]) newIndex = n;
		n++;
	}
	if(newIndex == -1)
	{
		npoints++;
		points = (G5EPoint*) realloc(points, sizeof(G5EPoint)*(npoints));
		points[npoints-1] = point[1];
		indices[ntriangles*3+1] = npoints-1;
	}
	else indices[ntriangles*3+1] = newIndex;
	newIndex = -1;
	n = 0;
	while(n<npoints && newIndex == -1)
	{
		if(points[n] == point[2]) newIndex = n;
		n++;
	}
	if(newIndex == -1)
	{
		npoints++;
		points = (G5EPoint*) realloc(points, sizeof(G5EPoint)*(npoints));
		points[npoints-1] = point[2];
		indices[ntriangles*3+2] = npoints-1;
	}
	else indices[ntriangles*3+2] = newIndex;

	ntriangles++;
	return 0;
}

G5EWorldObject::G5EWorldObject()
{
	scale.x = 1;
	scale.y = 1;
	scale.z = 1;
}
void G5EWorldObject::rotatef(float INrotX, float INrotY, float INrotZ)
{
	rotate.x +=INrotX;
	rotate.y +=INrotY;
	rotate.z +=INrotZ;
	if(rotate.x>360) rotate.x-=360;
	else if(rotate.x<0) rotate.x+=360;
	if(rotate.y>360) rotate.y-=360;
	else if(rotate.y<0) rotate.y+=360;
	if(rotate.z>360) rotate.z-=360;
	else if(rotate.z<0) rotate.z+=360;
}
void G5EWorldObject::translatef(float INtransX, float INtransY, float INtransZ)
{
	translation.x +=INtransX;
	translation.y +=INtransY;
	translation.z +=INtransZ;
}
void G5EWorldObject::scalef(float INscaleX, float INscaleY, float INscaleZ)
{
	scale.x = INscaleX;
	scale.y = INscaleY;
	scale.z = INscaleZ;
}

G5EWorldMeshObject::G5EWorldMeshObject(){}
G5EWorldMeshObject::G5EWorldMeshObject(G5EMeshObject *INgmeshobject)
{
	gmeshobject = INgmeshobject;
}
G5ETerrainObject::G5ETerrainObject()
{
	this->maxheight = 255;
	this->minheight = 0;
}
G5ETerrainObject::G5ETerrainObject(float INmaxheight, float INminheight)
{
	this->maxheight = INmaxheight;
	this->minheight = INminheight;
}
int G5ETerrainObject::gettxtdata(char *file, int INsizex, int INsizez, int step = 1)
{
	this->dimX = (INsizex/step);
	this->dimZ = (INsizez/step);
	heightmap = (float*) malloc(sizeof(float)*this->dimX*this->dimZ);
	FILE *data;
	fopen_s(&data,file,"r");
	if(data == NULL) return 0;
	for(int n1=0;n1<this->dimX;n1++)
	{
		for(int n2=0;n2<this->dimZ;n2++)
		{
			heightmap[n1+this->dimX*n2] = this->minheight+((this->maxheight-this->minheight)/255.0f)*fgetc(data);
			for(int n3=0;n3<step-1;n3++)
			{
				fgetc(data);
			}
	
		}
		for(int n3=0;n3<(step-1)*INsizex;n3++)
		{
			fgetc(data);
		}
		
		
	}
	fclose(data);
	return 1;
}
int G5ETerrainObject::getdimX()
{
	return this->dimX;
}
int G5ETerrainObject::getdimZ()
{
	return this->dimZ;
}
float G5ETerrainObject::getmax()
{
	return this->maxheight;
}
float G5ETerrainObject::getmin()
{
	return this->minheight;
}
float G5ETerrainObject::getHeight(int x, int z)
{
	if(x < -(this->dimX/2) || x > this->dimX/2-1 || z < -(this->dimZ/2) || z > this->dimZ/2-1) return G5E_INVALID_VALUE;
	return this->heightmap[x+(this->dimX/2) + dimX * (z+(this->dimZ/2))];
}
int G5ETerrainObject::setHeight(float height, int x, int z)
{
	if(x < -(this->dimX/2) || x > this->dimX/2-1 || z < -(this->dimZ/2) || z > this->dimZ/2-1) return G5E_INVALID_VALUE;
	this->heightmap[x+(this->dimX/2) + dimX * (z+(this->dimZ/2))]=height;
}
