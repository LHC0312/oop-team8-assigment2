#include "inf_int.h"
#include <string>
#include <algorithm>
#include <cstring>

inf_int::inf_int()
{
    this->digits = new char[2];
    this->digits[0] = '0';
    this->digits[1] = '\0';
    this->length = 1;
    this->thesign = true;
}

inf_int::inf_int(int n)
{
    char buf[100];

    if (n < 0) {
        this->thesign = false;
        n = -n;
    } else {
        this->thesign = true;
    }

    int i = 0;
    while (n > 0) {
        buf[i] = (n % 10) + '0';
        n /= 10;
        i++;
    }

    if (i == 0) {
        this->digits = new char[2];
        this->digits[0] = '0';
        this->digits[1] = '\0';
        this->length = 1;
        this->thesign = true;
    } else {
        buf[i] = '\0';
        this->digits = new char[i + 1];
        this->length = i;
        std::strcpy(this->digits, buf);
    }
}

inf_int::inf_int(const char* str)
{
    if (str == nullptr || *str == '\0') {
        digits = new char[2];
        digits[0] = '0';
        digits[1] = '\0';
        length = 1;
        thesign = true;
        return;
    }

    if (str[0] == '-') {
        thesign = false;
        str++;
    } else {
        thesign = true;
    }

    while (*str == '0' && *(str + 1) != '\0') {
        str++;
    }

    int L = std::strlen(str);
    length = L;

    digits = new char[L + 1];
    for (int i = 0; i < L; i++) {
        digits[i] = str[L - 1 - i];
    }
    digits[L] = '\0';

    if (length == 1 && digits[0] == '0') {
        thesign = true;
    }
}

inf_int::inf_int(const inf_int& a)
{
    this->digits = new char[a.length + 1];
    std::strcpy(this->digits, a.digits);
    this->length = a.length;
    this->thesign = a.thesign;
}

inf_int::~inf_int()
{
    delete[] digits;
}

inf_int& inf_int::operator=(const inf_int& a)
{
    if (this != &a) {
        delete[] this->digits;
        this->digits = new char[a.length + 1];
        std::strcpy(this->digits, a.digits);
        this->length = a.length;
        this->thesign = a.thesign;
    }
    return *this;
}

void inf_int::Add(const char num, const unsigned int index)
{
    if (this->length < index) {
        unsigned int newLen = index;
        char* newDigits = new char[newLen + 1];

        for (unsigned int i = 0; i < newLen; i++) {
            if (i < this->length) {
                newDigits[i] = this->digits[i];
            } else {
                newDigits[i] = '0';
            }
        }
        newDigits[newLen] = '\0';

        delete[] this->digits;
        this->digits = newDigits;
        this->length = newLen;
    }

    if (this->digits[index - 1] < '0') {
        this->digits[index - 1] = '0';
    }

    this->digits[index - 1] += (num - '0');

    if (this->digits[index - 1] > '9') {
        this->digits[index - 1] -= 10;
        Add('1', index + 1);
    }
}

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

// 비교 연산자들
bool operator==(const inf_int& a, const inf_int& b)
{
    if (a.thesign != b.thesign) return false;
    if (a.length != b.length) return false;


    for (unsigned int i = 0; i < a.length; i++) {
        if (a.digits[i] != b.digits[i]) return false;
    }
    return true;
}

bool operator!=(const inf_int& a, const inf_int& b)
{
    return !(a == b);
}

bool operator>(const inf_int& a, const inf_int& b)
{
    if (a.thesign != b.thesign)
        return a.thesign;

    if (a.length != b.length) {
        if (a.thesign) {
            return (a.length > b.length);
        } else {
            return (a.length < b.length);
        }
    }

    // 길이도 같으면 가장 높은 자리부터 비교
    for (int i = a.length - 1; i >= 0; i--) {
        if (a.digits[i] == b.digits[i]) continue;
        if (a.thesign) {
            return a.digits[i] > b.digits[i];
        } else {
            return a.digits[i] < b.digits[i];
        }
    }

    return false;
}

bool operator<(const inf_int& a, const inf_int& b)
{
    return !(a == b || a > b);
}


inf_int operator+(const inf_int& a, const inf_int& b)
{
    if (a.isPositive() == b.isPositive()) {
        inf_int temp = addAbs(a, b);
        temp.setSign(a.isPositive());
        return temp;
    }
    inf_int bFlipped = b;
    bFlipped.setSign(!bFlipped.isPositive());
    return a - bFlipped;
}

inf_int operator-(const inf_int& a, const inf_int& b)
{
    if (a.isPositive() != b.isPositive()) {
        inf_int bFlipped = b;
        bFlipped.setSign(!bFlipped.isPositive());
        return a + bFlipped;
    }
    int cmp = absCompare(a, b);
    if (cmp == 0) {
        return inf_int(0);
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

inf_int operator*(const inf_int& a, const inf_int& b)
{
    if (isZero(a) || isZero(b)) {
        return inf_int(0);
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

std::ostream& operator<<(std::ostream& out, const inf_int& a)
{
    if (!a.thesign && !(a.length == 1 && a.digits[0] == '0')) {
        out << '-';
    }

    for (int i = a.length - 1; i >= 0; i--) {
        out << a.digits[i];
    }

    return out;
}
