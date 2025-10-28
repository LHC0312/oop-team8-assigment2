#include "include/inf_int.h"
#include "include/add.h"
#include "include/sub.h"
#include "include/mul.h"

// 산술 연산자는 여기서 "연결부" 역할만 함
inf_int operator+(const inf_int& a, const inf_int& b)
{
    return add(a, b);
}

inf_int operator-(const inf_int& a, const inf_int& b)
{
    return sub(a, b);
}

inf_int operator*(const inf_int& a, const inf_int& b)
{
    return mul(a, b);
}
