#include <iostream>
#include "serializator.hpp"
#include <sstream>
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

struct Data1 {
    int a;
    bool b;
    std::string c;

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

struct Data2 {
    uint64_t a;
    bool b;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b);
    }
    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b);
    }
};

void defaultWork()
{
    Data x{ 2, true, 5 };
    Data y{ 0, false, 0 };
    std::stringstream s1;
    Serializer serializer(s1);
    serializer.save(x);
    Deserializer deserializer(s1);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void Uint64Test()
{
    Data1 x{ -32, true, "23" };
    Data1 y{ 1, true, "23" };
    std::stringstream s2;
    Serializer serializer(s2);
    const Error err = serializer.save(x);
    assert(err == Error::CorruptedArchive);
    const Error err_2 = serializer.save(x);
    assert(err_2 == Error::CorruptedArchive);
}

void DeserializerTest()
{
    Data2 x{ 1, false };
    Data y{ 0, true, 0 };
    std::stringstream s3;
    Serializer serializer(s3);
    serializer.save(x);
    s3 << ' ' << "here now";
    Deserializer deserializer(s3);
    const Error err = deserializer.load(y);
    assert(err == Error::CorruptedArchive); // unable
}

int main()
{
    try {
        defaultWork();
        Uint64Test();
        DeserializerTest();
    }
    catch (...) {
        std::cout << "Everything is awful\n";
    }
    std::cout << "Everything is not so bad\n";

    return 0;
}