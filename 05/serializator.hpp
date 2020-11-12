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
        try {
            handler(object);
        }
        catch (const Error& exception) {
            return exception;
        }
        return process(std::forward<ArgsT>(args)...);
    }
    template <class T>
    Error process(T&& object)
    {
        try {
            handler(object);
        }
        catch (const Error& exception) {
            return exception;
        }
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
    template <class T>
    void handler(T)
    {
        throw Error::CorruptedArchive;
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

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }

private:
    std::istream& in_;

    template <class T, class... ArgsT>
    Error process(T&& object, ArgsT&&... args)
    {
        try {
            funct(object);
        }
        catch (const Error& exception) {
            return exception;
        }
        return process(std::forward<ArgsT>(args)...);
    }

    template <class T>
    Error process(T&& object)
    {
        try {
            funct(object);
        }
        catch (const Error& err) {
            return err;
        }
        return Error::NoError;
    }

    void funct(bool& value)
    {
        std::string text;
        in_ >> text;
        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            throw Error::CorruptedArchive;
    }

    void funct(uint64_t& value)
    {
        std::string text;
        in_ >> text;
        if (!isdigit(text[0])) {
            throw Error::CorruptedArchive;
        }
        try {
            value = stoull(text);
        }
        catch (const std::logic_error& exception) {
            throw Error::CorruptedArchive;
        }
    }
    template <class T>
    void funct(T)
    {
        throw Error::CorruptedArchive;
    }
};