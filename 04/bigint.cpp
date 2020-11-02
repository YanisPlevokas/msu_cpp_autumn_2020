#include <iostream>
using namespace std;
#include "bigint.hpp"

BigInt::BigInt()
{
    size = 1;
    negFlag = false;
    zeroFlag = true;
    mas = new char[1]();
}

BigInt::BigInt(long long x)
{
    negFlag = false;
    if (x < 0)
    {
        x = -x;
        negFlag = true;
    }
    zeroFlag = false;
    if (x == 0)
    {
        mas = new char[1]();
        size = 1;
        zeroFlag = true;
    }
    else
    {
        size = 0;
        mas = new char[20]();
        while (x > 0)
        {
            mas[size] = x % 10;
            size++;
            x = x / 10;
        }
    }
}
BigInt::BigInt(string numb)
{
    negFlag = false;
    int localSdvig = 0;
    if (numb[0] == '-')
    {
        negFlag = true;
        localSdvig = 1;
    }
    zeroFlag = false;
    if (numb[0] == 0)
    {
        mas = new char[1]();
        size = 1;
        zeroFlag = true;
    }
    else
    {
        mas = new char[numb.length() - localSdvig];
        size = numb.length() - localSdvig;
        for (int i = 0; i < numb.length() - localSdvig; i++)
        {
            mas[i] = numb[numb.length() - i - 1] - '0';
        }
    }
}
BigInt::BigInt(char* m, size_t s, bool isn)
{
    mas = m;
    size = s;
    negFlag = isn;
    zeroFlag = ((size == 1) && (mas[0] == 0));
}

BigInt::~BigInt()
{
    delete[] mas;
}

BigInt::BigInt(const BigInt& value)
{
    mas = new char[value.size];
    negFlag = value.negFlag;
    size = value.size;
    zeroFlag = value.zeroFlag;
    copy(value.mas, value.mas + size, mas);
}

BigInt& BigInt::operator=(const BigInt& value)
{
    if (value == *this)
    {
        return *this;
    }
    char* tmp = new char[value.size];
    delete[] mas;
    mas = tmp;
    size = value.size;
    negFlag = value.negFlag;
    zeroFlag = value.zeroFlag;
    copy(value.mas, value.mas + size, mas);
    return *this;
}

BigInt::BigInt(BigInt&& value)
{
    size = value.size;
    negFlag = value.negFlag;
    zeroFlag = value.zeroFlag;
    delete[] mas;
    mas = value.mas;
    value.mas = nullptr;
    value.size = 0;
}

BigInt& BigInt::operator=(BigInt&& value)
{
    if (*this == value)
    {
        return *this;
    }
    delete[] mas;
    mas = value.mas;
    size = value.size;
    negFlag = value.negFlag;
    zeroFlag = value.zeroFlag;
    value.mas = nullptr;
    value.size = 0;
    return *this;
}

BigInt BigInt::operator-() const
{
    BigInt tmp(*this);
    tmp.negFlag = !tmp.negFlag;
    return tmp;
}

bool BigInt::operator==(const BigInt& value) const
{
    if (size != value.size)
    {
        return false;
    }
    if (zeroFlag && value.zeroFlag)
    {
        return true;
    }
    if (negFlag != value.negFlag)
    {
        return false;
    }
    for (int i = size - 1; i >= 0; i--)
    {
        if (mas[i] != value.mas[i])
        {
            return false;
        }
    }
    return true;
}

bool BigInt::operator!=(const BigInt& value) const
{
    return !(*this == value);
}

bool BigInt::operator<=(const BigInt& value) const
{
    if (value == *this)
    {
        return true;
    }
    if (value.negFlag && !negFlag)
    {
        return false;
    }
    if (!value.negFlag && negFlag)
    {
        return true;
    }
    if (!value.negFlag && !negFlag)
    {
        if (value.size > size)
        {
            return true;
        }
        if (value.size < size)
        {
            return false;
        }
        for (int i = size - 1; i >= 0; i--)
        {
            if (mas[i] > value.mas[i])
            {
                return false;
            }
            else if (mas[i] < value.mas[i])
            {
                return true;
            }
        }
        return true;
    }
    else if (value.negFlag && negFlag)
    {
        if (value.size > size)
        {
            return false;
        }
        if (value.size < size)
        {
            return true;
        }
        for (int i = size - 1; i >= 0; i--)
        {
            if (mas[i] > value.mas[i])
            {
                return true;
            }
            else if (mas[i] < value.mas[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool BigInt::operator>(const BigInt& value) const
{
    return !(*this <= value);
}

bool BigInt::operator>=(const BigInt& value) const
{
    return (*this > value || *this == value);
}

bool BigInt::operator<(const BigInt& value) const
{
    return !(*this >= value);
}

BigInt BigInt::operator+(const BigInt& value) const
{
    if (!negFlag && value.negFlag)
    {
        auto tmp = -value;
        return (*this).operator-(tmp);
    }
    if (negFlag && !value.negFlag)
    {
        auto tmp = -(*this);
        return value.operator-(tmp);
    }
    int max_size = 0;
    int min_size = 0;
    if (size >= value.size)
    {
        max_size = size;
        min_size = value.size;
    }
    else
    {
        max_size = value.size;
        min_size = size;
    }
    char carry = 0;
    char* res = new char[max_size + 1]();
    int i = 0;
    for (; i < min_size; i++)
    {
        res[i] = (mas[i] + value.mas[i] + carry) % 10;
        carry = (mas[i] + value.mas[i] + carry) / 10;
    }
    for (; i < max_size; i++)
    {
        if (max_size == size)
        {
            res[i] = (mas[i] + carry) % 10;
            carry = (mas[i] + carry) / 10;
        }
        else
        {
            res[i] = (value.mas[i] + carry) % 10;
            carry = (value.mas[i] + carry) / 10;
        }
    }
    int res_size = max_size;
    if (carry > 0)
    {
        res[i] = carry;
        res_size++;
    }
    return BigInt(res, res_size, negFlag);
}
BigInt BigInt::operator*(const BigInt& value) const
{
    BigInt result(new char[value.size + size], value.size + size, (value.negFlag ^ negFlag));
    int j;
    for (int i = 0; i < result.size; i++)
    {
        result.mas[i] = 0;
    }
    for (int i = 0; i < size; i++)
    {
        int carry = 0;
        int digit;
        for (j = i; j < value.size + i; j++)
        {
            digit = result.mas[j] + (value.mas[j - i] * mas[i]) + carry;
            carry = digit / 10;
            result.mas[j] = digit % 10;
        }
        if (carry)
        {
            digit = result.mas[j] + carry;
            carry = digit / 10;
            result.mas[j] = digit % 10;
        }
    }
    return result;
}
BigInt BigInt::operator-(const BigInt& value) const
{
    if (!negFlag && value.negFlag)
    {
        auto tmp = -value;
        return (*this).operator+(tmp);
    }
    if (negFlag && !value.negFlag)
    {
        auto tmp = -(*this);
        return -(value.operator+(tmp));
    }
    if (negFlag && value.negFlag)
    {
        auto tmp1 = -(*this);
        auto tmp2 = -value;
        return -(tmp1 - tmp2);
    }
    if (size > value.size)
    {
        char* res = new char[size]();
        int carry = 0;
        int i = 0;
        for (; i < value.size; i++)
        {
            res[i] = mas[i] - carry - value.mas[i];
            carry = 0;
            if (res[i] < 0)
            {
                res[i] += 10;
                carry = 1;
            }
        }
        for (; i < size; i++)
        {
            res[i] = mas[i] - carry;
            carry = 0;
            if (res[i] < 0)
            {
                res[i] += 10;
                carry = 1;
            }
        }
        i--;
        while (res[i] == 0)
        {
            i--;
        }
        return BigInt(res, i + 1, false);
    }
    else if (value.size > size)
    {
        char* res = new char[value.size]();
        int carry = 0;
        int i = 0;
        for (; i < size; i++)
        {
            res[i] = value.mas[i] - carry - mas[i];
            carry = 0;
            if (res[i] < 0)
            {
                res[i] += 10;
                carry = 1;
            }
        }
        for (; i < value.size; i++)
        {
            res[i] = value.mas[i] - carry;
            carry = 0;
            if (res[i] < 0)
            {
                res[i] += 10;
                carry = 1;
            }
        }
        i--;
        while (res[i] == 0)
        {
            i--;
        }
        return BigInt(res, i + 1, true);
    }
    else
    {
        if (*this == value)
        {
            return BigInt(0);
        }
        if (*this > value)
        {
            char* res = new char[size]();
            int carry = 0;
            int i = 0;
            for (; i < size; i++)
            {
                res[i] = mas[i] - carry - value.mas[i];
                carry = 0;
                if (res[i] < 0)
                {
                    res[i] += 10;
                    carry = 1;
                }
            }
            i--;
            while (res[i] == 0)
            {
                i--;
            }
            return BigInt(res, i + 1, false);
        }
        else
        {
            char* res = new char[size]();
            int carry = 0;
            int i = 0;
            for (; i < size; i++)
            {
                res[i] = value.mas[i] - carry - mas[i];
                carry = 0;
                if (res[i] < 0)
                {
                    res[i] += 10;
                    carry = 1;
                }
            }
            i--;
            while (res[i] == 0)
            {
                i--;
            }
            return BigInt(res, i + 1, true);
        }
    }
}

std::ostream& operator<<(std::ostream& out, const BigInt& value)
{
    int firstZeroFlag = 0;
    if (value.zeroFlag)
    {
        out << "0";
        return out;
    }
    if (value.negFlag)
    {
        out << '-';
    }
    for (int i = value.size - 1; i >= 0; i--)
    {
        if ((int(value.mas[i]) == 0) && (!firstZeroFlag))
        {
            firstZeroFlag = 1;
        }
        else
            out << int(value.mas[i]);
    }
    return out;
}