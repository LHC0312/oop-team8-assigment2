#include "include/inf_int.h"
#include <cstring>      // strcpy, strcmp, memcpy
#include <cstdlib>      // abs, realloc (만약 realloc 안 쓰면 제거 가능)
#include <algorithm>    // std::max 등 필요하면

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
        // n == 0 인 경우
        this->digits = new char[2];
        this->digits[0] = '0';
        this->digits[1] = '\0';
        this->length = 1;
        this->thesign = true; // 0은 항상 양수 처리
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
    // 역순 저장
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

// 소멸자
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
                newDigits[i] = 0;
            }
        }

        newDigits[newLen] = '\0';

        delete[] this->digits;
        this->digits = newDigits;
        this->length = newLen;

        for (unsigned int i = 0; i < this->length; i++) {
            if (this->digits[i] < '0') {
                this->digits[i] = '0';
            }
        }
    }

    if (this->digits[index - 1] < '0') {
        this->digits[index - 1] = '0';
    }

    this->digits[index - 1] += (num - '0'); // 실제 덧셈

    if (this->digits[index - 1] > '9') {
        this->digits[index - 1] -= 10;
        Add('1', index + 1);
    }

    this->digits[this->length] = '\0';
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
