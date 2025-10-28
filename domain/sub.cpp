#include "include/sub.h"
#include "include/add.h"
#include <cstring>

static int absCompare(const inf_int& a, const inf_int& b) {
    if (a.getLength() > b.getLength()) return 1;
    if (a.getLength() < b.getLength()) return -1;
    for (int i = (int)a.getLength() - 1; i >= 0; i--) {
        char da = a.getDigits()[i];
        char db = b.getDigits()[i];
        if (da > db) return 1;
        if (da < db) return -1;
    }
    return 0;
}

static bool isZero(const inf_int& x) {
    return (x.getLength() == 1 && x.getDigits()[0] == '0');
}

static inf_int subAbs(const inf_int& A, const inf_int& B) {
    inf_int result(0);
    unsigned int maxLen = A.getLength();
    char* buf = new char[maxLen + 1];
    int borrow = 0;
    for (unsigned int i = 0; i < maxLen; i++) {
        int da = (i < A.getLength() ? (A.getDigits()[i] - '0') : 0);
        int db = (i < B.getLength() ? (B.getDigits()[i] - '0') : 0);
        int val = da - db - borrow;
        if (val < 0) { val += 10; borrow = 1; } else borrow = 0;
        buf[i] = (char)(val + '0');
    }
    unsigned int newLen = maxLen;
    while (newLen > 1 && buf[newLen - 1] == '0') newLen--;
    buf[newLen] = '\0';
    char* normal = new char[newLen + 1];
    for (unsigned int i = 0; i < newLen; i++) normal[i] = buf[newLen - 1 - i];
    normal[newLen] = '\0';
    inf_int finalResult(normal);
    delete[] normal;
    delete[] buf;
    return finalResult;
}

inf_int sub(const inf_int& a, const inf_int& b)
{
    if (a.isPositive() != b.isPositive()) {
        inf_int bFlipped = b;
        bFlipped.setSign(!bFlipped.isPositive());
        inf_int tmp = add(a, bFlipped);
        return tmp;
    }
    int cmp = absCompare(a, b);
    if (cmp == 0) {
        inf_int zero(0);
        return zero;
    }
    const inf_int* bigger;
    const inf_int* smaller;
    bool resultSign;
    if (cmp == 1) {
        bigger = &a;
        smaller = &b;
        resultSign = a.isPositive();
    } else {
        bigger = &b;
        smaller = &a;
        resultSign = !a.isPositive();
    }
    inf_int magnitude = subAbs(*bigger, *smaller);
    if (isZero(magnitude)) magnitude.setSign(true);
    else magnitude.setSign(resultSign);
    return magnitude;
}
