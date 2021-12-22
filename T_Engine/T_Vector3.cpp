#include "T_Vector3.h"

T_Vector3::T_Vector3(const T_Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}


T_Vector3::~T_Vector3(void)
{

}

T_Vector3 T_Vector3::operator=(const T_Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

T_Vector3 T_Vector3::operator+(const T_Vector3& v)
{
	return T_Vector3(x + v.x, y + v.y, z + v.z);
}

T_Vector3 T_Vector3::operator-(const T_Vector3& v)
{
	return T_Vector3(x - v.x, y - v.y, z - v.z);
}

T_Vector3 T_Vector3::operator*(const T_Vector3& v)
{
	return T_Vector3(x * v.x, y * v.y, z * v.z);
}

T_Vector3 T_Vector3::operator/(const T_Vector3& v)
{
	if (v.x == 0 || v.y == 0 || v.z == 0)
		return *this;
	else
		return T_Vector3(x / v.x, y / v.y, z / v.z);
}

T_Vector3 T_Vector3::operator+(float a)
{
	return T_Vector3(x + a, y + a, z + a);
}

T_Vector3 T_Vector3::operator-(float a)
{
	return T_Vector3(x - a, y - a, z - a);
}

T_Vector3 T_Vector3::operator*(float a)
{
	return T_Vector3(x * a, y * a, z * a);
}

T_Vector3 T_Vector3::operator/(float a)
{
	if (a == 0)
		return *this;
	else
		return T_Vector3(x / a, y / a, z / a);
}

float T_Vector3::dot(const T_Vector3& v1, const T_Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

T_Vector3 T_Vector3::Cross(const T_Vector3& v1, const T_Vector3& v2)
{
	return T_Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.y);
}

float T_Vector3::length()
{
	return (float)sqrt(x * (double)x + y * (double)y + z * (double)z);
}

T_Vector3 T_Vector3::Normalize()
{
	if (this->length() == 0)
		return T_Vector3(0.0, 0.0, 0.0);
	else
		return T_Vector3(x / length(), y / length(), z / length());
}

T_Vector3 T_Vector3::Scale(float n)
{
	return T_Vector3(x * n, y * n, z * n);
}