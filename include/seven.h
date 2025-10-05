#pragma once
#include <iostream>
#include <string>
#include "buffer.h"

#define BASE 7

class Seven
{
private:
    Buffer buf;
public:
    Seven():Seven("0"){};
    // Seven(const size_t & n, unsigned char t = 0);
    // Seven(const std::initializer_list<unsigned char> & t);
    Seven(std::string t);
    // Seven(const Seven & other);
    // Seven(Seven && other) noexcept;
    virtual ~Seven() noexcept;

    Seven operator+(const Seven &other) const;
    bool operator==(const Seven &other) const = default;
};