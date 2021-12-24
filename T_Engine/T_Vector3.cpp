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

T_Vector3 T_Vector3::operator*(T_Matrix3& m)
{
	T_Vector3 ret;
	for (int i = 0; i < 3; ++i) {
		for (int r = 0; r < 3; ++r) {
			ret[i] += (*this)[i] * m[r][i];
		}
	}
	return ret;
}

float& T_Vector3::operator[](int t)
{
	switch (t)
	{
	case 0:
	case 1:
	case 2:
		return val[t];
	default:
		throw new std::out_of_range("试图在三维向量中取到更高维（或者更低维)");
	}
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

T_Matrix3::T_Matrix3()
{
}


float* T_Matrix3::operator[](int t)
{
	switch (t)
	{
	case 0:
	case 1:
	case 2:
		return val + (t * 3);
	default:
		throw new std::out_of_range("试图在三相矩阵中取到更高相（或者更低相)");
	}
}

T_Matrix3 T_Matrix3::operator*(T_Matrix3& m)
{
	T_Matrix3 ret;
	for (int i = 0; i < 3; ++i) {
		for (int r = 0; r < 3; ++r) {
			ret[i][r] += (*this)[i][r] * m[r][i];
		}
	}
	return ret;
}

T_Vector3 T_Matrix3::operator*(T_Vector3& v)
{
	T_Vector3 ret;
	for (int i = 0; i < 3; ++i) {
		for (int r = 0; r < 3; ++r) {
			ret[i] += v[i] * (*this)[i][r];
		}
	}
	return ret;
}
