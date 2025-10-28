#include "include/mul.h"
#include <cstring>

static bool isZero(const inf_int& x) {
    return (x.getLength() == 1 && x.getDigits()[0] == '0');
}

inf_int mul(const inf_int& a, const inf_int& b)
{
    if (isZero(a) || isZero(b)) {
        inf_int zero(0);
        return zero;
    }
    inf_int result(0);
    for (unsigned int i = 0; i < a.getLength(); i++) {
        int da = a.getDigits()[i] - '0';
        for (unsigned int j = 0; j < b.getLength(); j++) {
            int db = b.getDigits()[j] - '0';
            int prod = da * db;
            int idx = i + j + 1;
            int carry = prod;
            while (carry > 0) {
                int digitVal = carry % 10;
                result.Add((char)('0' + digitVal), idx);
                carry /= 10;
                idx++;
            }
        }
    }
    bool signResult = (a.isPositive() == b.isPositive());
    result.setSign(signResult);
    unsigned int L = result.getLength();
    const char* rd = result.getDigits();
    while (L > 1 && rd[L - 1] == '0') L--;
    char* normal = new char[L + 1];
    for (unsigned int k = 0; k < L; k++) normal[k] = rd[L - 1 - k];
    normal[L] = '\0';
    inf_int cleaned(normal);
    cleaned.setSign(signResult);
    delete[] normal;
    return cleaned;
}
