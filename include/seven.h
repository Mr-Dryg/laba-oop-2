#pragma once
#include <iostream>
#include <string>

class Seven
{
private:
    unsigned char *buf = new unsigned char[10];
public:
    Seven();
    // Seven(const size_t & n, unsigned char t = 0);
    Seven(const std::initializer_list<unsigned char> & t);
    // Seven(const std::string & t);
    // Seven(const Seven & other);
    // Seven(Seven && other) noexcept;
    virtual ~Seven() noexcept;
};