#ifndef HIC_MATH
#define HIC_MATH
#define PI 3.1415
#include <math.h>
#include "g5e_std.h"
class G5EPoint
{
public:
	float x,y,z;
	G5EPoint();
	G5EPoint(float x, float y, float z);
	bool operator ==(G5EPoint point);
	G5EPoint operator =(G5EPoint point);
};
class G5EVector3
{
public:
	float v1,v2,v3;
	G5EVector3();
	G5EVector3(float INv1, float INv2, float INv3);
	~G5EVector3();
	G5EVector3 operator+(G5EVector3 INgvector3);
	G5EVector3 operator=(G5EVector3 INgvector3);
	G5EVector3 operator-(G5EVector3 INgvector3);
	G5EVector3 operator+=(G5EVector3 INgvector3);
	G5EVector3 operator-=(G5EVector3 INgvector3);
	bool operator==(G5EVector3 INgvector3);
	float dot(G5EVector3 INgvector3);
	G5EVector3 cross(G5EVector3 INgvector3);
	G5EVector3 normalize();
	float length();

};
class G5EVector4 
{
public:
	float v1,v2,v3,v4;
	G5EVector4();
	G5EVector4(float INv1, float INv2, float INv3, float INv4);
	~G5EVector4();
	G5EVector4 operator+(G5EVector4 INgvector4);
	G5EVector4 operator=(G5EVector4 INgvector4);
	G5EVector4 operator-(G5EVector4 INgvector4);
	G5EVector4 operator+=(G5EVector4 INgvector4);
	G5EVector4 operator-=(G5EVector4 INgvector4);
	bool operator ==(G5EVector4 INgvector4);
	float dot(G5EVector4 INgvector4);
	G5EVector4 normalize();
	float length();

};
class G5EMatrix4
{
public:
	float a[16];
	G5EMatrix4();
	G5EMatrix4(float *INa);
	~G5EMatrix4();
	G5EMatrix4 operator*(G5EMatrix4 INgmatrix4);
	G5EMatrix4 getCurrentGLMatrix();
	//G5EMatrix4 operator=(G5EMatrix3 INgmatrix3);
};
class G5EMatrix3
{
public:
	float a[9];
	G5EMatrix3();
	G5EMatrix3(float *INa);
	~G5EMatrix3();
	G5EMatrix3 operator*(G5EMatrix3 INgmatrix3);
	G5EVector3 operator*(G5EVector3 INvector3);
	G5EMatrix3 operator=(G5EMatrix4 INgmatrix4);
	G5EMatrix3 operator=(G5EMatrix3 INgmatrix3);
	G5EMatrix3 operator-(G5EMatrix3 INgmatrix3);
	G5EMatrix3 invert();
	G5EMatrix3 transpose();
};
#endif