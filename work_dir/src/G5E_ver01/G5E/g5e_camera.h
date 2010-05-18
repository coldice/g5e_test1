#ifndef HIC_CAMERA
#define HIC_CAMERA
#define CAM_MODE_FREE 1
#define CAM_MODE_CENTER 2
#define MIN_DISTANCE 5
#include "g5e_std.h"
#include "g5e_world.h"


class G5ECamera
{
private:
	
	G5EVector3 viewvec3;
	G5EVector3 upvec3;
	float viewangle;
	float nearerCP, farerCP;
	float screenformat;
	G5EWorldObject *target;
public:
	G5ECamera();
	~G5ECamera();
	
	G5EVector3 pos; // !temporarely public!

	void SetPosition(float INx, float INy, float INz);
	void SetPosition(G5EVector3 INposvec3);
	int SetViewVec3(float INx, float INy, float INz);
	int SetUpVec3(float INx, float INy, float INz);
	int SetViewVec3(G5EVector3 INviewvec3);
	int SetUpVec3(G5EVector3 INupvec3);
	int setViewangle(float INviewangle);
	int setClippingPlanes(float INnearerCP, float INfarerCP);
	int setScreenFormat(float INscreenformat);
	int center(G5EWorldObject *INtarget);
	void free();

	void LoadPerspective();
	void LoadTransformation();
	void zoom(float val);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void rotateLeft(float angle); 
	void rotateRight(float angle); 
	void rotateUp(float angle); 
	void rotateDown(float angle); 
	void rollLeft(float angle);
	void rollRight(float angle);
	void moveFor(float distance);
	void moveBack(float distance);
	void moveLeft(float distance);
	void moveRight(float distance);
	void moveUp(float distance);
	void moveDown(float distance);
};
#endif