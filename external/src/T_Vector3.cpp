#include "T_Vector3.h"

T_Vector3::T_Vector3(const T_Vector3& v)
{
    val[0] = v.x;
    val[1] = v.y;
    val[2] = v.z;
}


T_Vector3::~T_Vector3(void)
{

}

T_Vector3 T_Vector3::operator=(const T_Vector3& v)
{
    val[0] = v.x;
    val[1] = v.y;
    val[2] = v.z;
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
    return val[t];
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

T_Matrix3::T_Matrix3(float v11, float v12, float v13, float v21, float v22, float v23, float v31, float v32, float v33)
{
    val[0] = v11;
    val[1] = v12;
    val[2] = v13;
    val[3] = v21;
    val[4] = v22;
    val[5] = v23;
    val[6] = v31;
    val[7] = v32;
    val[8] = v33;
}


float* T_Matrix3::operator[](int t)
{
    return val + (t * 3);
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
