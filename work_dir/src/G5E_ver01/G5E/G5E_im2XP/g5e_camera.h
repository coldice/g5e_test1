#ifndef HIC_CAMERA
#define HIC_CAMERA

#include "g5e_std.h"
class G5EDrawCamera
{
private:
	G5EPoint rotate;
	G5EPoint translate;
public:
	float viewangle;
	float nearerCP, farerCP;
	G5EDrawCamera(float INviewangle, float INnearerCP, float INfarerCP);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void translateX(float dist);
	void translateY(float dist);	
	void translateZ(float dist);
	void zoom(float val);
	void LoadPerspective();
	void LoadRotation();
	void LoadTranslation();
	void moveForwards(float dist);
	void moveBackwards(float dist);
	void moveLeft(float dist);
	void moveRight(float dist);
};
class G5ECamera
{
private:
	G5EPoint pos;
	G5EVector3 viewvec3;
	G5EVector3 upvec3;
	G5EMatrix3 rotmatvv;
	G5EMatrix3 rotmatuv;
	G5EMatrix3 rotmatvvinv;
	G5EMatrix3 rotmatuvinv;
public:
	G5ECamera();
	~G5ECamera();
	int SetViewVec3(float INx, float INy, float INz);
	int SetUpVec3(float INx, float INy, float INz);
	void Setrotmatvv(float angle);
	void Setrotmatuv(float angle);
	void SetTransformation();
	void rotateLeft();
	void rotateRight();
	void rollRight();
	void rollLeft();
};
#endif