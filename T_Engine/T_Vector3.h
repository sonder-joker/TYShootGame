#pragma once
#include <math.h>
class T_Vector3
{
public:
	T_Vector3(void) :x(0), y(0), z(0) {};
	T_Vector3(float x1, float y1, float z1) :x(x1), y(y1), z(z1) {};
	T_Vector3(const T_Vector3& v);

	T_Vector3 operator =(const T_Vector3& v); //赋值运算符重载

	// +-*/不同的重载方式
	T_Vector3 operator +(const T_Vector3& v);
	T_Vector3 operator -(const T_Vector3& v);
	T_Vector3 operator *(const T_Vector3& v);
	T_Vector3 operator /(const T_Vector3& v);

	T_Vector3 operator +(float a);
	T_Vector3 operator -(float a);
	T_Vector3 operator *(float a);
	T_Vector3 operator /(float a);

	float dot(const T_Vector3& v1, const T_Vector3& v2);      //2个向量的数量积
	T_Vector3 Cross(const T_Vector3& v1, const T_Vector3& v2); //2个向量的向量积
	float length();     //求向量的长度
	T_Vector3 Normalize();//单位化向量
	T_Vector3 Scale(float n);//向量按比例缩放 
	virtual ~T_Vector3(void);

private:
	float x;
	float y;
	float z;
};
