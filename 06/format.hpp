#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

std::string process(const char* text, std::vector<std::string>& v)
{
    std::stringstream new_text;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '{') {
            if (text[i + 1] == '}') {
                throw std::runtime_error("expected value");
            }
            i++;
            size_t num = 0;
            while (text[i] != '}') {
                if (!isdigit(text[i])) {
                    throw std::runtime_error("expected closing scope");
                }
                num *= 10;
                num += text[i] - '0';
                i++;
            }
            if (num >= v.size()) {
                throw std::runtime_error("out of range");
            }
            new_text << v[num];
        }
        else if (text[i] == '}') {
            throw std::runtime_error("expected opening scope");
        }
        else {
            new_text << text[i];
        }
    }
    return new_text.str();
}

template <class T>
std::string process(const char* text, std::vector<std::string>& v, T&& arg)
{
    std::stringstream outp;
    outp << arg;
    v.push_back(outp.str());
    return process(text, v);
}

template <class T, class... Args>
std::string process(const char* text, std::vector<std::string>& v, T&& arg, Args&&... args)
{
    std::stringstream outp;
    outp << arg;
    v.push_back(outp.str());
    return process(text, v, std::forward<Args>(args)...);
}

template <class... Args>
std::string format(const char* text, Args&&... args)
{
    std::vector<std::string> v;
    return process(text, v, std::forward<Args>(args)...);
}