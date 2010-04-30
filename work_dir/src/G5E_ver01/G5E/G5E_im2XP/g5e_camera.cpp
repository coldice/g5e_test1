#include "g5e_camera.h"
G5EDrawCamera::G5EDrawCamera(float INviewangle, float INnearerCP, float INfarerCP)
{
	this->viewangle = INviewangle;
	this->nearerCP = INnearerCP;
	this->farerCP = INfarerCP;
	this->translate.x = 0;
	this->translate.y = 0;
	this->translate.z = 0;
	this->rotate.x = 0;
	this->rotate.y = 0;
	this->rotate.z = 0;
}
void G5EDrawCamera::rotateX(float angle)
{
	this->rotate.x += angle;
	if(this->rotate.x>360) this->rotate.x-=360; 
	if(this->rotate.x<0) this->rotate.x+=360; 
}
void G5EDrawCamera::rotateY(float angle)
{
	this->rotate.y += angle;
	if(this->rotate.y>360) this->rotate.y-=360; 
	if(this->rotate.y<0) this->rotate.y+=360; 
}
void G5EDrawCamera::rotateZ(float angle)
{
	this->rotate.z += angle;
	if(this->rotate.z>360) this->rotate.z-=360; 
	if(this->rotate.z<0) this->rotate.z+=360; 
}
void G5EDrawCamera::translateX(float dist)
{
	this->translate.x+=dist;
}
void G5EDrawCamera::translateY(float dist)
{
	this->translate.y+=dist;
}	
void G5EDrawCamera::translateZ(float dist)
{
	this->translate.z+=dist;
}
void G5EDrawCamera::zoom(float val)
{
	if(val>0 && this->viewangle>1.0f) this->viewangle-=val;
	if(val<0 && this->viewangle<85.0f) this->viewangle-=val; 
}

void G5EDrawCamera::LoadPerspective()
{
	gluPerspective(this->viewangle, 4.0f/3.0f, nearerCP, farerCP);    // TO DO: Bildschirmverhältnis dynamisieren
}
void G5EDrawCamera::LoadRotation()
{
	glRotatef(this->rotate.x,1.0f, 0.0f, 0.0f);
	glRotatef(this->rotate.y,0.0f, 1.0f, 0.0f);
	glRotatef(this->rotate.z,0.0f, 0.0f, 1.0f);
}
void G5EDrawCamera::LoadTranslation()
{
	glTranslatef(this->translate.x,this->translate.y,this->translate.z);
}
void G5EDrawCamera::moveForwards(float dist)
{
	translate.x-=sin((rotate.y/360)*2*PI)*dist;
	translate.z+=cos((rotate.y/360)*2*PI)*dist;
	translate.y+=sin((rotate.x/360)*2*PI)*dist;
}
void G5EDrawCamera::moveBackwards(float dist)
{
	translate.x+=sin((rotate.y/360)*2*PI)*dist;
	translate.z-=cos((rotate.y/360)*2*PI)*dist;
	translate.y-=sin((rotate.x/360)*2*PI)*dist;
}
void G5EDrawCamera::moveLeft(float dist)
{
	translate.x-=sin(((rotate.y-90)/360)*2*PI)*dist;
	translate.z+=cos(((rotate.y-90)/360)*2*PI)*dist;
}
void G5EDrawCamera::moveRight(float dist)
{
	translate.x-=sin(((rotate.y+90)/360)*2*PI)*dist;
	translate.z+=cos(((rotate.y+90)/360)*2*PI)*dist;
}


G5ECamera::G5ECamera()
{
	float m[16];
	G5EMatrix4 tempMat4;
	this->viewvec3 = G5EVector3(0.0f,0.0f,1.0f);
	this->upvec3 = G5EVector3(0.0f,1.0f,0.0f);
	glPushMatrix();
		glLoadIdentity();
		glRotatef(0.5f, viewvec3.v1, viewvec3.v2, viewvec3.v3);
		tempMat4.getCurrentGLMatrix();
		this->rotmatvv = tempMat4;
		this->rotmatvvinv = this->rotmatvv;
		this->rotmatvvinv.transpose();

		glLoadIdentity();
		glRotatef(0.5f, upvec3.v1, upvec3.v2, upvec3.v3);
		tempMat4.getCurrentGLMatrix();
		this->rotmatuv = tempMat4;		
		this->rotmatuvinv = this->rotmatuv;
		this->rotmatuvinv.transpose();

	glPopMatrix();
}
G5ECamera::~G5ECamera() {}
int G5ECamera::SetViewVec3(float INx, float INy, float INz)
{
	if(INx == 0 && INy==0 && INz==0) return G5E_INVALID_VECTOR;
	this->viewvec3.v1 = INx;
	this->viewvec3.v2 = INy;
	this->viewvec3.v3 = INz;
	this->viewvec3.normalize();
	return G5E_SUCCESS;
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
void G5ECamera::SetTransformation()
{
	G5EVector3 e3 = G5EVector3(0,0,1.0f);
	G5EVector3 e2 = G5EVector3(0,1.0f,0);
	if(!(e2==upvec3))
	{
		G5EVector3 crossuve2 = upvec3.cross(e2);
		glRotatef((-acos(upvec3.dot(e2))*360)/(2*3.14), crossuve2.v1, crossuve2.v2, crossuve2.v3);
	glPushMatrix();
		glLoadIdentity();
		glRotatef((-acos(upvec3.dot(e2))*360)/(2*3.14), crossuve2.v1, crossuve2.v2, crossuve2.v3);
		G5EMatrix4 tempMat4;
		tempMat4.getCurrentGLMatrix();
		G5EMatrix3 tempMat3;
		tempMat3 = tempMat4;
		e3 = tempMat3 * e3;
	glPopMatrix();
	}
	if(!(e3==viewvec3))
	{
		G5EVector3 crossvve3 = viewvec3.cross(e3);
		/*float test = (-acos(viewvec3.dot(e3))*360)/(2*3.14);
		LOG_VALUE("Angle: %f",test);*/
		glRotatef((-acos(viewvec3.dot(e3))*360)/(2*3.14), crossvve3.v1, crossvve3.v2, crossvve3.v3);
	}

	/*glPushMatrix();
		glLoadIdentity();
		glRotatef((-acos(viewvec3.dot(e3))*360)/(2*3.14), upvec3.v1, upvec3.v2, upvec3.v3);
		float m[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
	glPopMatrix();*/
}
void G5ECamera::Setrotmatvv(float angle)
{
	float m[16];
	G5EMatrix4 tempMat4;
	glPushMatrix();
		glLoadIdentity();
		glRotatef(angle, viewvec3.v1, viewvec3.v2, viewvec3.v3);
		tempMat4.getCurrentGLMatrix();
		this->rotmatvv = tempMat4;
		this->rotmatvvinv = this->rotmatvv;
		this->rotmatvvinv.transpose();
	glPopMatrix();
}
void G5ECamera::Setrotmatuv(float angle)
{
	float m[16];
	G5EMatrix4 tempMat4;
	glPushMatrix();
		glLoadIdentity();
		glRotatef(angle, upvec3.v1, upvec3.v2, upvec3.v3);
		tempMat4.getCurrentGLMatrix();
		this->rotmatuv = tempMat4;
		this->rotmatuvinv = this->rotmatuv;
		this->rotmatuvinv.transpose();
	glPopMatrix();
}
void G5ECamera::rotateLeft()
{
	viewvec3 = this->rotmatuv * viewvec3;
	Setrotmatvv(0.5f);
}
void G5ECamera::rotateRight()
{
	viewvec3 = this->rotmatuvinv * viewvec3;
	Setrotmatvv(0.5f);
}
void G5ECamera::rollLeft()
{
	this->upvec3 = rotmatvv * this->upvec3;
	float vec3[3];
	vec3[0] = this->upvec3.v1;
	vec3[1] = this->upvec3.v2;
	vec3[2] = this->upvec3.v3;
	LOG_VECTOR3(vec3);
	Setrotmatuv(0.5f);
}
void G5ECamera::rollRight()
{
	upvec3 = rotmatvvinv * this->upvec3;
	float vec3[3];
	vec3[0] = this->upvec3.v1;
	vec3[1] = this->upvec3.v2;
	vec3[2] = this->upvec3.v3;
	LOG_VECTOR3(vec3);
	Setrotmatuv(0.5f);
}