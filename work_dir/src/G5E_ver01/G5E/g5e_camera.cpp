#include "g5e_camera.h"

G5ECamera::G5ECamera()
{
	this->viewvec3 = G5EVector3(0.0f,0.0f,-1.0f);
	this->upvec3 = G5EVector3(0.0f,1.0f,0.0f);
	viewangle = 45.0f;
	nearerCP = 1.0f;
	farerCP = 100.0f;
	target = NULL;
}
G5ECamera::~G5ECamera() {}
void G5ECamera::zoom(float val)
{
	if(val>0 && this->viewangle>1.0f) this->viewangle-=val;
	if(val<0 && this->viewangle<85.0f) this->viewangle-=val; 
}
int G5ECamera::setViewangle(float INviewangle)
{
	if(INviewangle < 0 || INviewangle > 90) return G5E_INVALID_VALUE;
	viewangle = INviewangle;
	return G5E_SUCCESS;
}
int G5ECamera::setClippingPlanes(float INnearerCP, float INfarerCP)
{
	if(INnearerCP < 0 || INfarerCP < INnearerCP) return G5E_INVALID_VALUE;
	farerCP = INfarerCP;
	nearerCP = INnearerCP;
	return G5E_SUCCESS;
}
int G5ECamera::setScreenFormat(float INscreenformat)
{
	if(INscreenformat <= 0) return G5E_INVALID_VALUE;
	screenformat = INscreenformat;
	return G5E_SUCCESS;
}
void G5ECamera::LoadPerspective()
{
	gluPerspective(this->viewangle, 4.0f/3.0f, nearerCP, farerCP);    // TO DO: Bildschirmverhältnis dynamisieren
}
int G5ECamera::SetViewVec3(float INx, float INy, float INz)
{
	if(INx == 0 && INy==0 && INz==0) return G5E_INVALID_VECTOR;
	this->viewvec3.v1 = INx;
	this->viewvec3.v2 = INy;
	this->viewvec3.v3 = INz;
	this->viewvec3.normalize();
	return G5E_SUCCESS;
}
int G5ECamera::SetViewVec3(G5EVector3 INviewvec3)
{
	if(INviewvec3.length() == 0) return G5E_INVALID_VECTOR;
	this->viewvec3 = INviewvec3;
	this->viewvec3.normalize();
	return G5E_SUCCESS;
}
int G5ECamera::SetUpVec3(G5EVector3 INupvec3)
{
	if(INupvec3.length() == 0) return G5E_INVALID_VECTOR;
	this->upvec3 = INupvec3;
	this->upvec3.normalize();
	return G5E_SUCCESS;
}
void G5ECamera::SetPosition(float INx, float INy, float INz)
{
	this->pos.v1 = INx;
	this->pos.v2 = INy;
	this->pos.v3 = INz;
}
void G5ECamera::SetPosition(G5EVector3 INposvec3)
{
	this->pos = INposvec3;
}
int G5ECamera::SetUpVec3(float INx, float INy, float INz)
{
	if(INx == 0 && INy==0 && INz==0) return G5E_INVALID_VECTOR;
	this->upvec3.v1 = INx;
	this->upvec3.v2 = INy;
	this->upvec3.v3 = INz;
	this->upvec3.normalize();
	return G5E_SUCCESS;
}
int G5ECamera::center(G5EWorldObject *INtarget)
{
	if(INtarget == NULL) return G5E_INVALID_OBJECT;
	this->target = INtarget;
	pos = G5EVector3(0,0,0);
	pos.v3 += MIN_DISTANCE;
	G5EVector3 tempvec3;
	tempvec3 = target->translation;
	viewvec3 = G5EVector3(0,0,0) - pos;
	upvec3 = G5EVector3(0,1.0f,0);
	return G5E_SUCCESS;
}
void G5ECamera::free()
{
	if(target != NULL)
	{
		pos = pos + target->translation;
		this->target = NULL;
	}
}
void G5ECamera::LoadTransformation()
{
	if(target==NULL) gluLookAt(pos.v1, pos.v2, pos.v3, viewvec3.v1+pos.v1, viewvec3.v2+pos.v2, viewvec3.v3+pos.v3, upvec3.v1, upvec3.v2, upvec3.v3);
	else  gluLookAt(pos.v1+target->translation.x, pos.v2+target->translation.y, pos.v3+target->translation.z, viewvec3.v1+pos.v1+target->translation.x, viewvec3.v2+pos.v2+target->translation.y, viewvec3.v3+pos.v3+target->translation.z, upvec3.v1, upvec3.v2, upvec3.v3);
}
void G5ECamera::rotateY(float angle)
{
	G5EMatrix3 tempMat3;
	if(target == NULL) 
	{	
		tempMat3.getRotationMatrix(angle, upvec3);
		viewvec3 = tempMat3 * viewvec3;
	}
	else
	{
		G5EVector3 temppos =pos - target->translation;
		G5EVector3 e2 = G5EVector3(0,1.0f,0);
		tempMat3.getRotationMatrix(angle, e2);
		pos = tempMat3 * pos;
		upvec3 = tempMat3 * upvec3;
		viewvec3 = tempMat3 * viewvec3;
	}
}
void G5ECamera::rotateZ(float angle)
{
	G5EMatrix3 tempMat3;
	tempMat3.getRotationMatrix(angle, viewvec3);
	upvec3 = tempMat3 * upvec3;
}
void G5ECamera::rotateX(float angle)
{
	G5EMatrix3 tempMat3;
	G5EVector3 tempVec3 = viewvec3.cross(upvec3);
	tempMat3.getRotationMatrix(angle, tempVec3);
	upvec3 = tempMat3 * upvec3;
	viewvec3 = tempMat3 * viewvec3;
	if(target != NULL)
	{
		G5EVector3 temppos = pos - target->translation;
		pos = tempMat3 * pos;
	}
}
void G5ECamera::rotateRight(float angle)
{
	this->rotateY(angle);

}
void G5ECamera::rotateLeft(float angle)
{
	this->rotateY(-angle);
}
void G5ECamera::rotateUp(float angle)
{
	this->rotateX(angle);
}
void G5ECamera::rotateDown(float angle)
{
	this->rotateX(-angle);
}
void G5ECamera::rollRight(float angle)
{
	if(target == NULL) this->rotateZ(-angle);
}
void G5ECamera::rollLeft(float angle)
{
	if(target == NULL) this->rotateZ(angle);
}
void G5ECamera::moveFor(float distance)
{
	if(target == NULL) pos+= viewvec3*distance;
	else
	{
		if(pos.length() > MIN_DISTANCE) pos+= viewvec3*distance;
	}
}
void G5ECamera::moveBack(float distance)
{
	pos-= viewvec3*distance;
}
void G5ECamera::moveLeft(float distance)
{
	if(target == NULL)
	{
		G5EVector3 tempVec3 = viewvec3.cross(upvec3);
		tempVec3.normalize();
		pos-= tempVec3*distance;
	}
}
void G5ECamera::moveRight(float distance)
{
	if(target == NULL)
	{
		G5EVector3 tempVec3 = viewvec3.cross(upvec3);
		tempVec3.normalize();
		pos+= tempVec3*distance;
	}
}
void G5ECamera::moveUp(float distance)
{
	if(target == NULL) pos+= upvec3*distance;
}
void G5ECamera::moveDown(float distance)
{
	if(target == NULL) pos+= upvec3*distance;
}