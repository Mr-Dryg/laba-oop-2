#include "../include/buffer.h"
#include <algorithm>
#include <string.h>

Buffer::Buffer()
{
    this->size = 0;
}

Buffer::Buffer(std::string t)
{
    this->set_max_size(t.length());
    this->size = t.length();
    for (int i=0; i < t.length(); i++)
        this->buf[i] = t[i];
}

Buffer::Buffer(const Buffer & other)
{
    this->set_max_size(other.get_size());
    std::copy(other.buf, other.buf + other.size, this->buf);
}

Buffer::~Buffer() noexcept
{
    delete [] this->buf;
    this->max_size = 0;
    this->size = 0;
}

void Buffer::set_max_size(const size_t &new_max_size)
{
    if (new_max_size == this->max_size)
        return;
    else if (new_max_size < this->max_size)
    {
        this->max_size = new_max_size;
        this->buf[this->max_size] = '\0';
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

size_t Buffer::get_size() const
{
    if (this->size == 0)
        return 1;
    return this->size;
}

bool Buffer::set_elem(const int &i, const unsigned char &elem)
{
    if (!(0 <= i && i < this->size))
        return false;
    this->buf[i] = elem;
    return true;
}

void Buffer::append(const unsigned char &elem)
{
    if (this->size + 1 == this->max_size)
        this->set_max_size(this->max_size + GROW);
    this->buf[this->size++] = elem;
}

unsigned char Buffer::get_elem(const int &i) const
{
    if (this->size == 0)
        return '0';
    return this->buf[i];
}

std::string Buffer::get_buffer() const
{
    if (this->size == 0)
        return "0";
    return reinterpret_cast<const char*>(this->buf);
}
