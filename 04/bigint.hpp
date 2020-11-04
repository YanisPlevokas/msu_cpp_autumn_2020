#pragma once
#include <iostream>
using namespace std;

class BigInt
{
    char* mas;
    size_t size;
    bool negFlag;
    bool zeroFlag;

public:
    BigInt(char* m, size_t s, bool isn);
    BigInt(long long x);
    BigInt();
    BigInt(const BigInt& value);
    BigInt(const string& numb);
    BigInt(BigInt&& value);
    BigInt& operator=(const BigInt& value);
    BigInt& operator=(BigInt&& value);
    BigInt operator+(const BigInt& value) const;
    BigInt operator*(const BigInt& value) const;
    BigInt operator-(const BigInt& value) const;
    BigInt operator-() const;
    bool operator==(const BigInt& value) const;
    bool operator!=(const BigInt& value) const;
    bool operator>=(const BigInt& value) const;
    bool operator<=(const BigInt& value) const;
    bool operator<(const BigInt& value) const;
    bool operator>(const BigInt& value) const;
    friend std::ostream& operator<<(std::ostream& out, const BigInt& value);
    ~BigInt();
};
