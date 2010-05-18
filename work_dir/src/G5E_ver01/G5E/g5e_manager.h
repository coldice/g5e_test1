#ifndef HIC_MANAGER
#define HIC_MANAGER

#include "g5e_std.h"
#include "g5e_world.h"
#define MAXWORLDOBJECTS 1024

class G5EManagerMO
{
public:
	int id;
	char name[32];
	G5EMeshObject mesh;
};
class G5EManagerMOList
{
public:
	G5EManagerMOList();
	~G5EManagerMOList();
	G5EManagerMO *mmo;
	G5EManagerMOList *prev;
	G5EManagerMOList *next;
};
/*struct G5EMeshList
{
	int id;
	char name[32];
	G5EMeshObject mesh;
	G5EMeshList *prev;
	G5EMeshList *next;
};*/
class G5EStaticMeshManager
{
private:
	//G5EMeshList *first;
	//G5EMeshList *last;
	G5EManagerMOList *first;
	G5EManagerMOList *last;
public:
	G5EStaticMeshManager();
	~G5EStaticMeshManager();
	int loadModel();  // Platzhalter
	int createMesh(G5EPoint *points, char name[32]);
	int createMesh(G5EPoint *points, int ntriangles, char name[32]);  // Platzhalter für beschleunigte Mesherzeugung
	void deleteMesh(int id);
	void deleteMesh(char name[32]);
	int getId(char name[32]);
	void getMesh(G5EMeshObject **mesh, int id);
	void getMesh(G5EMeshObject **mesh, char name[32]);

	void init_primitives();
	int createPyramid4();
};


class G5EManagerWMO
{	
public:
	int id;
	char name[32];
	G5EWorldMeshObject *wmo;
};
class G5EManagerWMOList
{	
public:
	G5EManagerWMOList();
	~G5EManagerWMOList();
	G5EManagerWMO *mwmo;
	G5EManagerWMOList *next;
	G5EManagerWMOList *prev;
};
class G5EStaticWorldManager
{
private:
	G5EStaticMeshManager *smm;
	G5EManagerWMOList *first;
	G5EManagerWMOList *last;
	G5EManagerWMOList *mwmo[MAXWORLDOBJECTS];
public:
	G5EStaticWorldManager(G5EStaticMeshManager *smm);
	~G5EStaticWorldManager();
	int createWorldMesh(int meshid, char name[32]);
	void deleteWorldMesh(int id);
	void deleteWorldMesh(char name[32]);
	int getId(char name[32]);
	void getWorldMesh(G5EWorldMeshObject **worldmesh, int id);
	void getWorldMesh(G5EWorldMeshObject **worldmesh, char name[32]);
	void translatef(int id, float x, float y, float z);
	void translatef(char name[32], float x, float y, float z);
	void scalef(char name[32], float x, float y, float z);
	void scalef(int id, float x, float y, float z);
	void rotatef(int id, float x, float y, float z);
	void rotatef(char name[32], float x, float y, float z);
	void setTranslationf(int id, float x, float y, float z);
	void setTranslationf(char name[32], float x, float y, float z);
	void setScalingf(int id, float x, float y, float z);
	void setScalingf(char name[32], float x, float y, float z);
	void setRotationf(int id, float x, float y, float z);
	void setRotationf(char name[32], float x, float y, float z);

	
};
#endif
