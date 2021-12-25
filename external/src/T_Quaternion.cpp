#include "T_Quaternion.h"
template<class T>
T_Quaternion<T>::T_Quaternion()
{

}

template<class T>
T_Quaternion<T>::T_Quaternion(T a, T b, T c, T d)
{

    this->q_a = a;
    this->q_b = b;
    this->q_c = c;
    this->q_d = d;
}

template<class T>
T_Quaternion<T> T_Quaternion<T>::operator+(const T_Quaternion& a)
{
    this->q_a += a.q_a;
    this->q_b += a.q_b;
    this->q_c += a.q_c;
    this->q_d += a.q_d;
    return *this;
}

template<class T>
T_Quaternion<T> T_Quaternion<T>::operator-(const T_Quaternion& a)
{
    this->q_a -= a.q_a;
    this->q_b -= a.q_b;
    this->q_c -= a.q_c;
    this->q_d -= a.q_d;
    return *this;
}

template<class T>
T_Quaternion<T> T_Quaternion<T>::operator*(const T_Quaternion& a)
{
    this->q_a *= a.q_a;
    this->q_b *= a.q_b;
    this->q_c *= a.q_c;
    this->q_d *= a.q_d;
    return *this;
}

template<class T>
T_Quaternion<T> T_Quaternion<T>::operator=(const T_Quaternion& a)
{
    this->q_a = a.q_a;
    this->q_b = a.q_b;
    this->q_c = a.q_c;
    this->q_d = a.q_d;
    return *this;
}

template<class T>
bool T_Quaternion<T>::operator==(const T_Quaternion& a)
{
    if (this->q_a == a.q_a && this->q_b == a.q_b && this->q_c == a.q_c && this->q_d == a.q_d)
        return  true;
    else return false;
}

template<class T>
bool T_Quaternion<T>::operator!=(const T_Quaternion& a)
{
    return !(*this == a);
}

template<class T>
void T_Quaternion<T>::conjugate()
{
    this->q_b = -q_b;
    this->q_c = -q_c;
    this->q_d = -q_d;
}

template<class T>
double T_Quaternion<T>::mod()
{
    return sqrt(this->q_a * this->q_a + this->q_b * this->q_b + this->q_c * this->q_c + this->q_d * this->q_d);
}

template<class T>
void T_Quaternion<T>::inverse()
{
    try {
        if (this->mod() < 1e-6) throw std::overflow_error("Division by Zero");
        else
            return this->conjugate() / this->mod();
    }
    catch (std::exception a) {
        std::cerr << a.what() << std::endl;
    }
    //将模为零的情况做异常抛出
}

template<class T>
T_Quaternion<T> operator*(T a, T_Quaternion<T> b)
{
    return b * a;
}

template<class T>
T_Quaternion<T> T_Quaternion<T>::operator*(T a)
{
    this->q_a *= a;
    this->q_b *= a;
    this->q_c *= a;
    this->q_d *= a;
    return *this;
}
