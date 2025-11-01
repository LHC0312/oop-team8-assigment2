#include "inf_int.h"
#include <cstring>

using namespace std;

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
        strcpy(this->digits, buf);
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

    int L = strlen(str);
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
    strcpy(this->digits, a.digits);
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
        strcpy(this->digits, a.digits);
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
static inf_int divAbs(const inf_int& a, const inf_int& b) {
    inf_int remainder("0"); // 현재 나머지
    inf_int ten(10);
    std::string quotientStr;    // 몫을 문자열로 구성 (앞에서부터)

    // a의 가장 높은 자릿수부터 순회합니다.
    // (digits는 뒤집혀 있으므로, length - 1 부터 0 까지)
    for (int i = (int)a.getLength() - 1; i >= 0; i--) {

        // 1. "숫자 하나 내려받기" (remainder = remainder * 10 + next_digit)
        remainder = remainder * ten;

        // getDigits()[i] (i번째 자릿수)를 inf_int로 만듭니다.
        char digit_char[2] = { a.getDigits()[i], '\0' };
        inf_int nextDigit(digit_char);
        // inf_int(const char*) 생성자는 정방향 문자열을 받으므로 "3" -> 3

        remainder = remainder + nextDigit;

        // 2. 현재 나머지(remainder)가 b로 몇 번 나누어지는지 찾기 (0~9)
        int quotientDigit = 0;
        for (int q = 9; q >= 1; q--) {
            inf_int q_int(q); // inf_int(int) 생성자 사용

            // test = b * q
            inf_int test = b * q_int;

            // if (test <= remainder)
            if (absCompare(test, remainder) <= 0) {
                quotientDigit = q;
                remainder = remainder - test; // remainder = remainder - test
                break; // 몫의 현재 자릿수를 찾았으므로 중단
            }
        }
        quotientStr.push_back(quotientDigit + '0');
    }

    // 3. 몫 문자열 정리 (예: "00123" -> "123")
    // (inf_int(const char*) 생성자가 이미 앞쪽 0을 제거해줍니다.)
    return inf_int(quotientStr.c_str());
}

/**
 * @brief inf_int 나눗셈 연산자 (a / b)
 * (operator*와 유사한 구조로 작성)
 */
inf_int operator/(const inf_int& a, const inf_int& b)
{
    // 1. 엣지 케이스 처리 (b == 0)
    if (isZero(b)) {
        // 0으로 나누는 것은 정의되지 않음.
        // 여기서는 0을 반환합니다. (operator*가 0을 반환하는 것과 일관성)
        return inf_int(0);
    }

    // 2. 엣지 케이스 처리 (a == 0)
    if (isZero(a)) {
        return inf_int(0);
    }

    // 3. 정수 나눗셈의 엣지 케이스 (|a| < |b|)
    if (absCompare(a, b) == -1) {
        return inf_int(0);
    }

    // 4. 핵심 로직 호출 (divAbs 헬퍼 함수 사용)
    inf_int result = divAbs(a, b);

    // 5. 부호 결정 (operator*와 동일한 로직)
    bool signResult = (a.isPositive() == b.isPositive());
    result.setSign(signResult);

    // 6. 결과 정리
    // divAbs가 반환하는 `inf_int`는 이미 inf_int(const char*) 생성자를 통해
    // "00123" -> "123" 처리가 완료된 상태입니다.
    // (operator*의 cleanup 로직이 필요 없음)

    // 부호가 음수가 되었는데 값이 0인 경우 부호 정리
    if (isZero(result)) {
        result.setSign(true);
    }

    return result;
}
/**
 * @brief inf_int가 홀수인지 확인하는 static 헬퍼 함수
 */
static bool isOdd(const inf_int& a) {
    // 0은 짝수
    if (isZero(a)) {
        return false;
    }
    // digits[0] (가장 낮은 자릿수)가 홀수인지 확인
    return (a.getDigits()[0] - '0') % 2 != 0;
}

/**
 * @brief inf_int 거듭제곱 연산자 (a ^ b)
 * (제곱을 통한 거듭제곱 알고리즘 사용)
 */
inf_int operator^(const inf_int& a, const inf_int& b)
{
    // --- 1. 엣지 케이스 처리 ---

    // 1-1. 지수(b)가 0인 경우: a^0 = 1 (단, 0^0도 1로 처리)
    if (isZero(b)) {
        return inf_int(1);
    }

    // 1-2. 지수(b)가 음수인 경우: a^(-b) = 1 / a^b
    // 정수 클래스이므로, 결과는 0 (소수점 버림)
    if (!b.isPositive()) {
        return inf_int(0);
    }

    // (이제 b는 1 이상)

    // 1-3. 베이스(a)가 0인 경우: 0^b = 0
    if (isZero(a)) {
        return inf_int(0);
    }

    // 1-4. 베이스(a)가 1인 경우: 1^b = 1
    if (a.getLength() == 1 && a.getDigits()[0] == '1' && a.isPositive()) {
        return inf_int(1);
    }

    // 1-5. 베이스(a)가 -1인 경우: (-1)^b
    if (a.getLength() == 1 && a.getDigits()[0] == '1' && !a.isPositive()) {
        if (isOdd(b)) {
            return inf_int(-1); // b가 홀수면 -1
        } else {
            return inf_int(1);  // b가 짝수면 1
        }
    }

    // --- 2. 핵심 로직 (Exponentiation by Squaring) ---
    // (a^b 계산)

    inf_int base = a;
    inf_int exponent = b;
    inf_int result(1);
    inf_int two(2); // 2로 나누기 위한 상수

    // exponent가 0이 될 때까지 반복
    while (!isZero(exponent)) {

        // exponent가 홀수이면, result에 base를 곱함
        if (isOdd(exponent)) {
            result = result * base;
        }

        // base를 제곱함 (a -> a^2 -> a^4 -> a^8 ...)
        base = base * base;

        // exponent를 2로 나눔 (정수 나눗셈)
        exponent = exponent / two;
    }

    return result;
}
ostream& operator<<(ostream& out, const inf_int& a)
{
    if (!a.thesign && !(a.length == 1 && a.digits[0] == '0')) {
        out << '-';
    }

    for (int i = a.length - 1; i >= 0; i--) {
        out << a.digits[i];
    }

    return out;
}