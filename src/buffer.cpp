#include "../include/buffer.h"
#include <algorithm>
#include <stdexcept>
#include <string.h>

Buffer::Buffer(std::string t)
{
    this->size = t.length();
    this->max_size = t.length();
    this->buf = new unsigned char[this->max_size];
    for (size_t i = 0; i < t.length(); i++)
        this->buf[i] = t[i];
}

Buffer::Buffer(const Buffer& other) 
    : size(other.size), max_size(other.max_size), buf(new unsigned char[other.max_size])
{
    std::copy(other.buf, other.buf + other.size, this->buf);
}

Buffer::~Buffer() noexcept
{
    delete [] this->buf;
    this->buf = nullptr;
    this->max_size = 0;
    this->size = 0;
}

void Buffer::set_max_size(const size_t& new_max_size)
{
    if (new_max_size <= this->max_size)
        throw std::invalid_argument("New max_size must be greater than current size");
    unsigned char* new_buf = new unsigned char[new_max_size]{'\0'};
    size_t copy_size = std::min(this->size, new_max_size);
    std::copy(this->buf, this->buf + copy_size, new_buf);
    delete [] this->buf;
    this->buf = new_buf;
    this->max_size = new_max_size;
    this->size = copy_size;
}

size_t Buffer::get_size() const
{
    return this->size;
}

void Buffer::set_elem(const int& i, const unsigned char& elem)
{
    if (!(0 <= i && i < this->size))
        throw std::out_of_range("Index out of range");
    this->buf[i] = elem;
    if (elem == '\0')
        this->size = i;
}

void Buffer::push_back(const unsigned char& elem)
{
    if (this->size + 1 >= this->max_size)
        this->set_max_size(this->max_size + GROW);
    this->buf[this->size++] = elem;
}

unsigned char Buffer::get_elem(const int& i) const
{
    if (!(0 <= i && i <= this->size))
        throw std::out_of_range("Index out of range");
    return this->buf[i];
}

std::string Buffer::get_buffer() const
{
    return std::string(reinterpret_cast<const char*>(this->buf), this->size);
}

Buffer& Buffer::operator=(const Buffer& other)
{
    if (this != &other)
    {
        delete [] this->buf;
        
        this->size = other.size;
        this->max_size = other.max_size;
        this->buf = new unsigned char[this->max_size];
        std::copy(other.buf, other.buf + other.size, this->buf);
    }
    return *this;
}