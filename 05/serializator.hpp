#pragma once
#include <iostream>

enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';

public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }

private:
    std::ostream& out_;

    template <class T, class... ArgsT>
    Error process(T&& object, ArgsT&&... args)
    {
        handler(object);
        return process(std::forward<ArgsT>(args)...);
    }
    template <class T>
    Error process(T&& object)
    {
        handler(object);
        return Error::NoError;
    }
    void handler(bool obj)
    {
        out_ << (obj ? "true" : "false") << Separator;
    }
    void handler(uint64_t obj)
    {
        out_ << obj << Separator;
    }
};

class Deserializer {
    static constexpr char Separator = ' ';

public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class T, class... ArgsT>
    Error operator()(T&& object, ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }

private:
    std::istream& in_;

    template <class T, class... ArgsT>
    Error process(T&& object, ArgsT&&... args)
    {
        auto res = funct(object);
        if (res == Error::CorruptedArchive) {
            return Error::CorruptedArchive;
        }
        return process(std::forward<ArgsT>(args)...);
    }

    template <class T>
    Error process(T&& object)
    {
        return funct(object);
    }

    Error funct(bool& value)
    {
        std::string text;
        in_ >> text;
        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }

    Error funct(uint64_t& a)
    {
        std::string text;
        in_ >> text;
        try {
            if (!isdigit(text[0])) {
                return Error::CorruptedArchive;
            }
            a = std::stoull(text);
            return Error::NoError;
        }
        catch (const std::exception& e) {
            return Error::CorruptedArchive;
        }
    }
};