#include "include/add.h"
#include "include/sub.h"
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

static inf_int addAbs(const inf_int& posA, const inf_int& posB) {
    inf_int result(0);
    unsigned int maxLen = (posA.getLength() > posB.getLength() ? posA.getLength() : posB.getLength());
    for (unsigned int i = 0; i < maxLen; i++) {
        if (i < posA.getLength()) result.Add(posA.getDigits()[i], i + 1);
        if (i < posB.getLength()) result.Add(posB.getDigits()[i], i + 1);
    }
    return result;
}

inf_int add(const inf_int& a, const inf_int& b)
{
    if (a.isPositive() == b.isPositive()) {
        inf_int temp = addAbs(a, b);
        temp.setSign(a.isPositive());
        return temp;
    }
    inf_int bFlipped = b;
    bFlipped.setSign(!bFlipped.isPositive());
    return sub(a, bFlipped);
}
