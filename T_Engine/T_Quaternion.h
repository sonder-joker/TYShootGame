#pragma once
#ifndef T_QUATERNION_H
#define T_QUATERNION_H
#include <type_traits>
#include <iostream>
#include <stdexcept>
#include <math.h>

template<class T>
class T_Quaternion
{
    static_assert(std::is_arithmetic<T>::value, "Type Error");
public:
    T q_a, q_b, q_c, q_d;

    T_Quaternion();
    T_Quaternion(T a, T b, T c, T d);
    T_Quaternion<T> operator=(const T_Quaternion& a);
    T_Quaternion<T> operator+(const T_Quaternion& a);
    T_Quaternion<T> operator-(const T_Quaternion& a);
    T_Quaternion<T> operator*(const T_Quaternion& a);
    T_Quaternion<T> operator*(T a);
    template<T> friend T_Quaternion<T> operator*(T a, T_Quaternion b);
    bool operator==(const T_Quaternion& a);
    bool operator!=(const T_Quaternion& a);
    void inverse();
    double mod();
    void conjugate();
};

#endif

