#include "../include/seven.h"
#include "../include/buffer.h"
#include <algorithm>
#include <string>
#include <stdexcept>

Seven::Seven(std::string t)
{
    int i = 0;
    for (const auto& digit : t)
        if (!('0' <= digit && digit < '0' + BASE))
        {
            throw std::invalid_argument("Invalid digit for base-7 number");
        }
            
    std::reverse(t.begin(), t.end());
    this->buf = {t};
    this->remove_leading_zeros();
}

std::string Seven::get_string() const
{
    std::string res {this->buf.get_buffer()};
    std::reverse(res.begin(), res.end());
    return res;
}

Seven& Seven::operator=(const Seven& other)
{
    if (this != &other)
    {
        this->buf = other.buf;
    }
    return *this;
}

Seven Seven::operator+(const Seven& other) const
{  
    Buffer new_buf {};
    int carrying=0;
    int i=0;
    for (; i < this->buf.get_size() && i < other.buf.get_size(); i++)
    {
        int new_elem_int = carrying + (this->buf.get_elem(i) - '0') + (other.buf.get_elem(i) - '0');
        unsigned char new_elem = '0' + (new_elem_int % BASE);
        carrying = new_elem_int / BASE;
        new_buf.push_back(new_elem);
    }
    for (;i < this->buf.get_size(); i++)
    {
        int new_elem_int = carrying + this->buf.get_elem(i) - '0';
        unsigned char new_elem = '0' + (new_elem_int % BASE);
        carrying = new_elem_int / BASE;
        new_buf.push_back(new_elem);
    }
    for (;i < other.buf.get_size(); i++)
    {
        int new_elem_int = carrying + other.buf.get_elem(i) - '0';
        unsigned char new_elem = '0' + (new_elem_int % BASE);
        carrying = new_elem_int / BASE;
        new_buf.push_back(new_elem);
    }
    while (carrying)
    {
        int new_elem_int = carrying;
        unsigned char new_elem = '0' + (new_elem_int % BASE);
        carrying = new_elem_int / BASE;
        new_buf.push_back(new_elem);
    }
    std::string s {new_buf.get_buffer()};
    std::reverse(s.begin(), s.end());
    return Seven {s};
}

Seven Seven::operator-(const Seven& other) const
{
    if (*this < other)
        throw std::invalid_argument("Other must be lower or equal");
    Buffer new_buf {};
    int carrying = 0;
    int i = 0;
    for (; i < other.buf.get_size(); i++)
    {
        int new_elem_int = carrying + (this->buf.get_elem(i) - '0') - (other.buf.get_elem(i) - '0');
        unsigned char new_elem;
        if (new_elem_int < 0)
        {
            new_elem = '0' + (new_elem_int + BASE);
            carrying = -1;
        }
        else
        {
            new_elem = '0' + new_elem_int;
            carrying = 0;
        }
        new_buf.push_back(new_elem);
    }
    for (; i < this->buf.get_size(); i++)
    {
        int new_elem_int = carrying + (this->buf.get_elem(i) - '0');
        unsigned char new_elem;
        if (new_elem_int < 0)
        {
            new_elem = '0' + (new_elem_int + BASE);
            carrying = -1;
        }
        else
        {
            new_elem = '0' + new_elem_int;
            carrying = 0;
        }
        new_buf.push_back(new_elem);
    }
    std::string s {new_buf.get_buffer()};
    std::reverse(s.begin(), s.end());
    return Seven {s};
}

bool Seven::operator>(const Seven& other) const
{
    if (this->buf.get_size() != other.buf.get_size())
        return this->buf.get_size() > other.buf.get_size();
    int i = 0;
    int min_size = std::min(this->buf.get_size(), other.buf.get_size());
    for (;i < min_size && this->buf.get_elem(i) == other.buf.get_elem(i); i++);
    return this->buf.get_elem(i) > other.buf.get_elem(i);
}

bool Seven::operator<(const Seven& other) const
{
    if (this->buf.get_size() != other.buf.get_size())
        return this->buf.get_size() < other.buf.get_size();
    int i = 0;
    int min_size = std::min(this->buf.get_size(), other.buf.get_size());
    for (;i < min_size && this->buf.get_elem(i) == other.buf.get_elem(i); i++);
    return this->buf.get_elem(i) < other.buf.get_elem(i);
}

bool Seven::operator>=(const Seven& other) const
{
    return *this > other || *this == other;
}

bool Seven::operator<=(const Seven& other) const
{
    return *this < other || *this == other;
}

bool Seven::operator==(const Seven& other) const
{
    return this->buf.get_buffer() == other.buf.get_buffer();
}

bool Seven::operator!=(const Seven& other) const
{
    return this->buf.get_buffer() != other.buf.get_buffer();
}

void Seven::remove_leading_zeros()
{
    int i = this->buf.get_size() - 1;
    for (; i > 0 && this->buf.get_elem(i) == '0'; i--)
        this->buf.set_elem(i, '\0');
}