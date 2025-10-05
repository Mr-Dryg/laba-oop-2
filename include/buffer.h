#pragma once
#include <cstddef>
#include <iostream>
#include <new>
#include <string>

class Buffer
{
private:
    size_t size = 0;
    size_t max_size = 5;
    unsigned char *buf = new unsigned char[max_size]{'\0'};
    void set_max_size(const size_t &new_max_size);
public:
    Buffer():Buffer("0"){};
    Buffer(std::string t);
    virtual ~Buffer() noexcept;
    size_t get_size();
    bool set_elem(const int &i, const unsigned char &elem);
    unsigned char get_elem(const int &i);
    std::string get_buffer(const bool &native=false);
};