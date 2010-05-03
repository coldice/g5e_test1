#include "g5e_math.h"
G5EPoint::G5EPoint()
{
	x=0;
	y=0;
	z=0;
}
G5EPoint::G5EPoint(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
bool G5EPoint::operator ==(G5EPoint point)
{
	if(this->x == point.x && this->y == point.y && this->z == point.z) return 1;
	else return 0;
}
G5EPoint G5EPoint::operator =(G5EPoint point)
{
	this->x = point.x;
	this->y = point.y;
	this->z = point.z;
	return *this;
}
// ************************ Vector 3 ********************************
G5EVector3::G5EVector3()
{
	v1 = 0;
	v2 = 0;
	v3 = 0;
}
G5EVector3::G5EVector3(float INv1, float INv2, float INv3)
{
	v1 = INv1;
	v2 = INv2;
	v3 = INv3;
}
G5EVector3::~G5EVector3(){}

G5EVector3 G5EVector3::operator +(G5EVector3 INgvector3)
{
	G5EVector3 retVec3;
	retVec3.v1 = this->v1 + INgvector3.v1;
	retVec3.v2 = this->v2 + INgvector3.v2;
	retVec3.v3 = this->v3 + INgvector3.v3;
	return retVec3;
}
G5EVector3 G5EVector3::operator +=(G5EVector3 INgvector3)
{
	this->v1 += INgvector3.v1;
	this->v2 += INgvector3.v2;
	this->v3 += INgvector3.v3;
	return *this;
}
G5EVector3 G5EVector3::operator -(G5EVector3 INgvector3)
{
	G5EVector3 retVec3;
	retVec3.v1 = this->v1 - INgvector3.v1;
	retVec3.v2 = this->v2 - INgvector3.v2;
	retVec3.v3 = this->v3 - INgvector3.v3;
	return retVec3;
}	
G5EVector3 G5EVector3::operator=(G5EPoint INgpoint)
{
	this->v1 = INgpoint.x;
	this->v2 = INgpoint.y;
	this->v3 = INgpoint.z;
	return *this;
}
G5EVector3 G5EVector3::operator-(G5EPoint INgpoint)
{
	G5EVector3 tempvec3;
	tempvec3.v1 = this->v1 - INgpoint.x;
	tempvec3.v2 = this->v2 - INgpoint.y;
	tempvec3.v3 = this->v3 - INgpoint.z;
	return tempvec3;
}
G5EVector3 G5EVector3::operator+(G5EPoint INgpoint)
{
	G5EVector3 tempvec3;
	tempvec3.v1 = this->v1 + INgpoint.x;
	tempvec3.v2 = this->v2 + INgpoint.y;
	tempvec3.v3 = this->v3 + INgpoint.z;
	return tempvec3;
}
G5EVector3 G5EVector3::operator -=(G5EVector3 INgvector3)
{
	this->v1 -= INgvector3.v1;
	this->v2 -= INgvector3.v2;
	this->v3 -= INgvector3.v3;
	return *this;
}
G5EVector3 G5EVector3::operator =(G5EVector3 INgvector3)
{
	this->v1 = INgvector3.v1;
	this->v2 = INgvector3.v2;
	this->v3 = INgvector3.v3;
	return *this;
}
G5EVector3 G5EVector3::operator*(float INskalar)
{
	G5EVector3 tempVec3;
	tempVec3.v1 = this->v1*INskalar;
	tempVec3.v2 = this->v2*INskalar;
	tempVec3.v3 = this->v3*INskalar;
	return tempVec3;
}
bool G5EVector3::operator==(G5EVector3 INgvector3)
{
	if(this->v1==INgvector3.v1 && this->v2==INgvector3.v2 && this->v3==INgvector3.v3) return true;
	else return false;
}
float G5EVector3::dot(G5EVector3 INgvector3)
{
	return this->v1*INgvector3.v1+this->v2*INgvector3.v2+this->v3*INgvector3.v3;
}
float G5EVector3::length()
{
	return sqrt((this->v1*this->v1)+(this->v2*this->v2)+(this->v3*this->v3));
}
G5EVector3 G5EVector3::normalize()
{
	float length;
	length = this->length();
	if (length==0) return *this;
	v1 /= length;
	v2 /= length;
	v3 /= length;
	return *this;
}

G5EVector3 G5EVector3::cross(G5EVector3 INgvector3)
{
	return G5EVector3(this->v2*INgvector3.v3-this->v3*INgvector3.v2,this->v3*INgvector3.v1-this->v1*INgvector3.v3,this->v1*INgvector3.v2-this->v2*INgvector3.v1);
}
// ************************ Vector 4 ********************************
G5EVector4::G5EVector4()
{
	v1 = 0;
	v2 = 0;
	v3 = 0;
	v4 = 0;
}
G5EVector4::G5EVector4(float INv1, float INv2, float INv3, float INv4)
{
	v1 = INv1;
	v2 = INv2;
	v3 = INv3;
	v4 = INv4;
}
G5EVector4::~G5EVector4(){}

G5EVector4 G5EVector4::operator +(G5EVector4 INgvector4)
{
	G5EVector4 retVec4;
	retVec4.v1 = this->v1 + INgvector4.v1;
	retVec4.v2 = this->v2 + INgvector4.v2;
	retVec4.v3 = this->v3 + INgvector4.v3;
	retVec4.v4 = this->v4 + INgvector4.v4;
	return retVec4;
}
G5EVector4 G5EVector4::operator +=(G5EVector4 INgvector4)
{
	this->v1 += INgvector4.v1;
	this->v2 += INgvector4.v2;
	this->v3 += INgvector4.v3;
	this->v4 += INgvector4.v4;
	return *this;
}
G5EVector4 G5EVector4::operator -=(G5EVector4 INgvector4)
{
	this->v1 -= INgvector4.v1;
	this->v2 -= INgvector4.v2;
	this->v3 -= INgvector4.v3;
	this->v4 -= INgvector4.v4;
	return *this;
}
G5EVector4 G5EVector4::operator -(G5EVector4 INgvector4)
{
	G5EVector4 retVec4;
	retVec4.v1 = this->v1 - INgvector4.v1;
	retVec4.v2 = this->v2 - INgvector4.v2;
	retVec4.v3 = this->v3 - INgvector4.v3;
	retVec4.v4 = this->v4 - INgvector4.v4;
	return retVec4;
}	
G5EVector4 G5EVector4::operator =(G5EVector4 INgvector4)
{
	this->v1 = INgvector4.v1;
	this->v2 = INgvector4.v2;
	this->v3 = INgvector4.v3;
	this->v4 = INgvector4.v4;
	return *this;
}
bool G5EVector4::operator==(G5EVector4 INgvector4)
{
	if(this->v1==INgvector4.v1 && this->v2==INgvector4.v2 && this->v3==INgvector4.v3 && this->v4==INgvector4.v4) return true;
	else return false;
}
float G5EVector4::dot(G5EVector4 INgvector4)
{
	return this->v1*INgvector4.v1+this->v2*INgvector4.v2+this->v3*INgvector4.v3+this->v4*INgvector4.v4;
}
float G5EVector4::length()
{
	return sqrt((this->v1*this->v1)+(this->v2*this->v2)+(this->v3*this->v3)+(this->v4*this->v4));
}
G5EVector4 G5EVector4::normalize()
{
	float length;
	length = this->length();
	if (length==0) return *this;
	v1 /= length;
	v2 /= length;
	v3 /= length;
	v4 /= length;
	return *this;
}



/********************************** MATRIX 4 *************************************/
G5EMatrix4::G5EMatrix4()
{
	this->a[0] = 1;
	this->a[1] = 0;
	this->a[2] = 0;
	this->a[3] = 0;
	this->a[4] = 0;
	this->a[5] = 1;
	this->a[6] = 0;
	this->a[7] = 0;
	this->a[8] = 0;
	this->a[9] = 0;
	this->a[10] = 1;
	this->a[11] = 0;
	this->a[12] = 0;
	this->a[13] = 0;
	this->a[14] = 0;
	this->a[15] = 1;
}
G5EMatrix4::G5EMatrix4(float *INa)
{
	this->a[0] = INa[0];
	this->a[1] = INa[1];
	this->a[2] = INa[2];
	this->a[3] = INa[3];
	this->a[4] = INa[4];
	this->a[5] = INa[5];
	this->a[6] = INa[6];
	this->a[7] = INa[7];
	this->a[8] = INa[8];
	this->a[9] = INa[9];
	this->a[10] = INa[10];
	this->a[11] = INa[11];
	this->a[12] = INa[12];
	this->a[13] = INa[13];
	this->a[14] = INa[14];
	this->a[15] = INa[15];
}
G5EMatrix4::~G5EMatrix4(){}
G5EMatrix4 G5EMatrix4::operator *(G5EMatrix4 INmatrix)
{
	G5EMatrix4 tempMat4 = G5EMatrix4();
	tempMat4.a[0] = this->a[0]*INmatrix.a[0] + this->a[1]*INmatrix.a[4] + this->a[2]*INmatrix.a[8]+ this->a[3]*INmatrix.a[12];  
	tempMat4.a[1] = this->a[0]*INmatrix.a[1] + this->a[1]*INmatrix.a[5] + this->a[2]*INmatrix.a[9] + this->a[3]*INmatrix.a[13]; 
	tempMat4.a[2] = this->a[0]*INmatrix.a[2] + this->a[1]*INmatrix.a[6] + this->a[2]*INmatrix.a[10] + this->a[3]*INmatrix.a[14]; 
	tempMat4.a[3] = this->a[0]*INmatrix.a[3] + this->a[1]*INmatrix.a[7] + this->a[2]*INmatrix.a[11] + this->a[3]*INmatrix.a[15]; 

	tempMat4.a[4] = this->a[4]*INmatrix.a[0] + this->a[5]*INmatrix.a[4] + this->a[6]*INmatrix.a[8] + this->a[7]*INmatrix.a[12];
	tempMat4.a[5] = this->a[4]*INmatrix.a[1] + this->a[5]*INmatrix.a[5] + this->a[6]*INmatrix.a[9] + this->a[7]*INmatrix.a[13]; 
	tempMat4.a[6] = this->a[4]*INmatrix.a[2] + this->a[5]*INmatrix.a[6] + this->a[6]*INmatrix.a[10] + this->a[7]*INmatrix.a[14]; 
	tempMat4.a[7] = this->a[4]*INmatrix.a[3] + this->a[5]*INmatrix.a[7] + this->a[6]*INmatrix.a[11] + this->a[7]*INmatrix.a[15]; 

	tempMat4.a[8] = this->a[8]*INmatrix.a[0] + this->a[9]*INmatrix.a[4] + this->a[10]*INmatrix.a[8] + this->a[11]*INmatrix.a[12];
	tempMat4.a[9] = this->a[8]*INmatrix.a[1] + this->a[9]*INmatrix.a[5] + this->a[10]*INmatrix.a[9] + this->a[11]*INmatrix.a[13]; 
	tempMat4.a[10] = this->a[8]*INmatrix.a[2] + this->a[9]*INmatrix.a[6] + this->a[10]*INmatrix.a[10] + this->a[11]*INmatrix.a[14]; 
	tempMat4.a[11] = this->a[8]*INmatrix.a[3] + this->a[9]*INmatrix.a[7] + this->a[10]*INmatrix.a[11] + this->a[11]*INmatrix.a[15];

	tempMat4.a[12] = this->a[12]*INmatrix.a[0] + this->a[13]*INmatrix.a[4] + this->a[14]*INmatrix.a[8] + this->a[15]*INmatrix.a[12];
	tempMat4.a[13] = this->a[12]*INmatrix.a[1] + this->a[13]*INmatrix.a[5] + this->a[14]*INmatrix.a[9] + this->a[15]*INmatrix.a[13]; 
	tempMat4.a[14] = this->a[12]*INmatrix.a[2] + this->a[13]*INmatrix.a[6] + this->a[14]*INmatrix.a[10] + this->a[15]*INmatrix.a[14]; 
	tempMat4.a[15] = this->a[12]*INmatrix.a[3] + this->a[13]*INmatrix.a[7] + this->a[14]*INmatrix.a[11] + this->a[15]*INmatrix.a[15];
	return tempMat4;
}
G5EMatrix4 G5EMatrix4::getCurrentGLMatrix()
{
	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	*this = G5EMatrix4(m);
	return *this;
}
G5EMatrix4 G5EMatrix4::getRotationMatrix(float angle, G5EVector3 rotaxis3)
{
	glPushMatrix();
		glLoadIdentity();
		glRotatef(angle, rotaxis3.v1, rotaxis3.v2, rotaxis3.v3);
		this->getCurrentGLMatrix();
	glPopMatrix();
	return *this;
}
/********************************** MATRIX 3 *************************************/
G5EMatrix3::G5EMatrix3()
{
	this->a[0] = 1;
	this->a[1] = 0;
	this->a[2] = 0;
	this->a[3] = 0;
	this->a[4] = 1;
	this->a[5] = 0;
	this->a[6] = 0;
	this->a[7] = 0;
	this->a[8] = 1;
}
G5EMatrix3::G5EMatrix3(float *INa)
{
	this->a[0] = INa[0];
	this->a[1] = INa[1];
	this->a[2] = INa[2];
	this->a[3] = INa[3];
	this->a[4] = INa[4];
	this->a[5] = INa[5];
	this->a[6] = INa[6];
	this->a[7] = INa[7];
	this->a[8] = INa[8];
}
G5EMatrix3::~G5EMatrix3(){}
G5EMatrix3 G5EMatrix3::operator*(G5EMatrix3 INmatrix3)
{
	G5EMatrix3 tempMat3 = G5EMatrix3();

	tempMat3.a[0] = this->a[0]*INmatrix3.a[0] + this->a[1]*INmatrix3.a[3] + this->a[2]*INmatrix3.a[6];  
	tempMat3.a[1] = this->a[0]*INmatrix3.a[1] + this->a[1]*INmatrix3.a[4] + this->a[2]*INmatrix3.a[7]; 
	tempMat3.a[2] = this->a[0]*INmatrix3.a[2] + this->a[1]*INmatrix3.a[5] + this->a[2]*INmatrix3.a[8]; 

	tempMat3.a[3] = this->a[3]*INmatrix3.a[0] + this->a[4]*INmatrix3.a[3] + this->a[5]*INmatrix3.a[6];
	tempMat3.a[4] = this->a[3]*INmatrix3.a[1] + this->a[4]*INmatrix3.a[4] + this->a[5]*INmatrix3.a[7]; 
	tempMat3.a[5] = this->a[3]*INmatrix3.a[2] + this->a[4]*INmatrix3.a[5] + this->a[5]*INmatrix3.a[8]; 

	tempMat3.a[6] = this->a[6]*INmatrix3.a[0] + this->a[7]*INmatrix3.a[3] + this->a[8]*INmatrix3.a[6];
	tempMat3.a[7] = this->a[6]*INmatrix3.a[1] + this->a[7]*INmatrix3.a[4] + this->a[8]*INmatrix3.a[7]; 
	tempMat3.a[8] = this->a[6]*INmatrix3.a[2] + this->a[7]*INmatrix3.a[5] + this->a[8]*INmatrix3.a[8]; 

	return tempMat3;
}
G5EVector3 G5EMatrix3::operator*(G5EVector3 INvector3)
{
	G5EVector3 retvec3;
	retvec3.v1 = this->a[0]*INvector3.v1 + this->a[1] * INvector3.v2 + this->a[2] * INvector3.v3;
	retvec3.v2 = this->a[3]*INvector3.v1 + this->a[4] * INvector3.v2 + this->a[5] * INvector3.v3;
	retvec3.v3 = this->a[6]*INvector3.v1 + this->a[7] * INvector3.v2 + this->a[8] * INvector3.v3;
	return retvec3;
}

G5EMatrix3 G5EMatrix3::operator=(G5EMatrix4 INgmatrix4)
{
	this->a[0] = INgmatrix4.a[0];
	this->a[1] = INgmatrix4.a[1];
	this->a[2] = INgmatrix4.a[2];
	this->a[3] = INgmatrix4.a[4];
	this->a[4] = INgmatrix4.a[5];
	this->a[5] = INgmatrix4.a[6];
	this->a[6] = INgmatrix4.a[8];
	this->a[7] = INgmatrix4.a[9];
	this->a[8] = INgmatrix4.a[10];
	return *this;
}
G5EMatrix3 G5EMatrix3::operator=(G5EMatrix3 INgmatrix3)
{
	this->a[0] = INgmatrix3.a[0];
	this->a[1] = INgmatrix3.a[1];
	this->a[2] = INgmatrix3.a[2];
	this->a[3] = INgmatrix3.a[3];
	this->a[4] = INgmatrix3.a[4];
	this->a[5] = INgmatrix3.a[5];
	this->a[6] = INgmatrix3.a[6];
	this->a[7] = INgmatrix3.a[7];
	this->a[8] = INgmatrix3.a[8];
	return *this;
}

G5EMatrix3 G5EMatrix3::operator-(G5EMatrix3 INgmatrix3)
{
	G5EMatrix3 tempMat3;
	tempMat3.a[0] = this->a[0] - INgmatrix3.a[0];
	tempMat3.a[1] = this->a[1] - INgmatrix3.a[1];
	tempMat3.a[2] = this->a[2] - INgmatrix3.a[2];
	tempMat3.a[3] = this->a[3] - INgmatrix3.a[3];
	tempMat3.a[4] = this->a[4] - INgmatrix3.a[4];
	tempMat3.a[5] = this->a[5] - INgmatrix3.a[5];
	tempMat3.a[6] = this->a[6] - INgmatrix3.a[6];
	tempMat3.a[7] = this->a[7] - INgmatrix3.a[7];
	tempMat3.a[8] = this->a[8] - INgmatrix3.a[8];
	return tempMat3;
}
G5EMatrix3 G5EMatrix3::invert()
{
	G5EMatrix3 tempMat3;
	float f;
	f = this->a[3]/this->a[0];
	this->a[3] = 0;
	this->a[4] -= this->a[1]*f;
	this->a[5] -= this->a[2]*f;
	tempMat3.a[3] -= tempMat3.a[0]*f;

	f = this->a[6]/this->a[0];
	this->a[6] = 0;
	this->a[7] -= this->a[1]*f;
	this->a[8] -= this->a[2]*f;
	tempMat3.a[6] -= tempMat3.a[0]*f;

	f = this->a[7]/this->a[4];
	this->a[7] = 0;
	this->a[8] -= this->a[5]*f;
	tempMat3.a[6] -= tempMat3.a[3]*f;
	tempMat3.a[7] -= tempMat3.a[4]*f;
	
	f = this->a[5]/this->a[8];
	this->a[5] = 0;
	tempMat3.a[3] -= tempMat3.a[6]*f;
	tempMat3.a[4] -= tempMat3.a[7]*f;
	tempMat3.a[5] -= tempMat3.a[8]*f;

	f = this->a[2]/this->a[8];
	this->a[2] = 0;
	tempMat3.a[0] -= tempMat3.a[6]*f;
	tempMat3.a[1] -= tempMat3.a[7]*f;
	tempMat3.a[2] -= tempMat3.a[8]*f;

	f = this->a[1]/this->a[4];
	this->a[1] = 0;
	tempMat3.a[0] -= tempMat3.a[3]*f;
	tempMat3.a[1] -= tempMat3.a[4]*f;
	tempMat3.a[2] -= tempMat3.a[5]*f;

	f = 1/this->a[0];
	this->a[0] = 1;
	tempMat3.a[0] *= f;
	tempMat3.a[1] *= f;
	tempMat3.a[2] *= f;

	f = 1/this->a[4];
	this->a[4] = 1;
	tempMat3.a[3] *= f;
	tempMat3.a[4] *= f;
	tempMat3.a[5] *= f;

	f = 1/this->a[8];
	this->a[8] = 1;
	tempMat3.a[6] *= f;
	tempMat3.a[7] *= f;
	tempMat3.a[8] *= f;
	*this = tempMat3;
	return *this;
}

G5EMatrix3 G5EMatrix3::transpose()
{
	G5EMatrix3 tempMat3 = *this;
	this->a[1] = tempMat3.a[3];;
	this->a[2] = tempMat3.a[6];
	this->a[3] = tempMat3.a[1];
	this->a[5] = tempMat3.a[7];
	this->a[6] = tempMat3.a[2];
	this->a[7] = tempMat3.a[5];
	return *this;
}
G5EMatrix3 G5EMatrix3::getRotationMatrix(float angle, G5EVector3 rotaxis3)
{
	G5EMatrix4 tempMat4;
	*this = tempMat4.getRotationMatrix(angle, rotaxis3);
	return *this;
}