#pragma once

#include <math.h>
#include <exception>
#include <stdexcept>

struct T_Matrix3;

struct T_Vector3
{
public:
	T_Vector3(void) { x = y = z = 0; };
	T_Vector3(float x1, float y1, float z1) { val[0] = x1, val[1] = y1, val[2] = z1; };
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

	T_Vector3 operator *(T_Matrix3& m);

	float& operator[](int t);

	float dot(const T_Vector3& v1, const T_Vector3& v2);      //2个向量的数量积
	T_Vector3 Cross(const T_Vector3& v1, const T_Vector3& v2); //2个向量的向量积
	float length();     //求向量的长度
	T_Vector3 Normalize();//单位化向量
	T_Vector3 Scale(float n);//向量按比例缩放 
	virtual ~T_Vector3(void);

	float val[3];

	float& x=val[0];
	float& y=val[1];
	float& z=val[2];
};

struct T_Matrix3
{
public:
	float val[9] = { 0,0,0,0,0,0,0,0,0 };

	T_Matrix3();
	T_Matrix3(
		float v11, float v12, float v13,
		float v21, float v22, float v23,
		float v31, float v32, float v33
	);

	float* operator[](int t);
	T_Matrix3 operator*(T_Matrix3& m);
	T_Vector3 operator*(T_Vector3& v);
};