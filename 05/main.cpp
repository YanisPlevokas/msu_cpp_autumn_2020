#include <iostream>
#include "serializator.hpp"
#include <sstream>

#define checkEqual(x, y)                                                                 \
    do {                                                                                 \
        if ((x) != (y)) {                                                                \
            std::cout << "at line " << __LINE__ << ": " << (x) << " != " << (y) << '\n'; \
        };                                                                               \
    } while (0)
#define checkTrue(cond)                                                   \
    do {                                                                  \
        if (!(cond))                                                      \
            std::cout << "at line " << __LINE__ << ": " << #cond << '\n'; \
    } while (0)

struct Data {
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

void FirstTest()
{
    Data x{ 1, true, 2 };
    std::stringstream s1;
    Serializer serializer(s1);
    checkTrue(serializer.save(x) == Error::NoError);
}

void SecondTest()
{
    Data y{ 0, false, 0 };
    std::stringstream s1;
    Serializer serializer(s1);
    Deserializer d1(s1);
    checkTrue(d1.load(y) == Error::NoError);
}

void ThirdTest()
{
    Data x{ 1, true, 2 };

    std::stringstream s1;

    Serializer serializer(s1);

    Data y{ 0, false, 0 };

    Deserializer d1(s1);
    checkEqual(x.a, y.a);
    checkEqual(x.b, y.b);
    checkEqual(x.c, y.c);
}

void FourthTest()
{
    Data y{ 0, false, 0 };
    auto s2 = std::stringstream("");
    Deserializer d2(s2);
    checkTrue(d2.load(y) == Error::CorruptedArchive);

    auto s3 = std::stringstream("1 2 3");
    Deserializer d3(s3);
    checkTrue(d3.load(y) == Error::CorruptedArchive);

    auto s4 = std::stringstream("1 true -3");
    Deserializer d4(s4);
    checkTrue(d4.load(y) == Error::CorruptedArchive);

    auto s5 = std::stringstream("false 1");
    Deserializer d5(s5);
    checkTrue(d5.load(y) == Error::CorruptedArchive);
}
void FifthTest()
{
    Data y{ 0, true, 0 };

    auto s6 = std::stringstream("100 false 500");
    Deserializer d6(s6);
    checkTrue(d6.load(y) == Error::NoError);

    checkEqual(y.a, 100);
    checkEqual(y.b, false);
    checkEqual(y.c, 500);
}

int main()
{
    try {
        FifthTest();
        SecondTest();
        ThirdTest();
        FourthTest();
        FifthTest();
    }
    catch (...) {
        std::cout << "Everything is awful\n";
    }
    std::cout << "Everything is not so bad\n";

    return 0;
}