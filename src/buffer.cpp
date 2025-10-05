#include "../include/buffer.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string.h>

Buffer::Buffer(std::string t)
{
    std::reverse(t.begin(), t.end());
    this->set_max_size(t.length());
    this->size = t.length();
    for (int i=0; i < t.length(); i++)
        this->buf[i] = t[i];
}

Buffer::~Buffer() noexcept
{
    delete [] this->buf;
    this->max_size = 0;
    this->size = 0;
}

void Buffer::set_max_size(const size_t &new_max_size)
{
    if (new_max_size <= this->max_size)
    {
        this->max_size = new_max_size;
        return;
    }
    unsigned char *new_buf = new unsigned char[new_max_size]{'\0'};
    for (int i=0; i < this->size; i++)
    {
        new_buf[i] = this->buf[i];
    }
    delete [] this->buf;
    this->buf = new_buf;
}

size_t Buffer::get_size()
{
    return this->size;
}

bool Buffer::set_elem(const int &i, const unsigned char &elem)
{
    if (!(0 <= i && i < this->size))
        return false;
    this->buf[i] = elem;
    return true;
}

unsigned char Buffer::get_elem(const int &i)
{
    return this->buf[i];
}

std::string Buffer::get_buffer(const bool &native)
{
    std::string res{reinterpret_cast<const char*>(this->buf)};
    if (!native)
        std::reverse(res.begin(), res.end());
    return res;
}

int main()
{
    Buffer buf{};
    std::cout << buf.get_buffer() << '\n';
}