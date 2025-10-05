#include "../include/seven.h"
#include "../include/buffer.h"
#include <algorithm>
// #include <stdexcept>

// Seven::Seven(const std::initializer_list<unsigned char> & t)
// {
    // int i = 0;
    // for (const auto& digit : t)
    // {
    //     if (0 <= digit && digit <= 6)
    //     {
    //         buf[i]
    //     }
    //     else
    //     {
    //         throw std::invalid_argument("Digit must be between 0 and 6");
    //     }
    // }

// }

Seven::Seven(std::string t)
{
    int i = 0;
    for (const auto& digit : t)
        if (!(0 <= digit && digit < BASE))
            throw std::invalid_argument("Digit must be between 0 and 6");
    std::reverse(t.begin(), t.end());
    this->buf = {t};
}

Seven Seven::operator+(const Seven &other) const
{  
    Buffer new_buf {};
    // int size = 1 + std::max(this->buf.get_size(), other.buf.get_size());
    int carrying=0;
    int i=0;
    for (; this->buf.get_elem(i) == '\0' || other.buf.get_elem(i) == '\0'; i++)
    {
        int new_elem_int = carrying + (this->buf.get_elem(i) - '0') + (other.buf.get_elem(i) - '0');
        unsigned char new_elem = '0' + (new_elem_int % BASE);
        carrying = new_elem_int / BASE;
        new_buf.append(new_elem);
    }
    while (this->buf.get_elem(i) != '\0')
    {
        int new_elem_int = carrying + other.buf.get_elem(i) - '0';
        unsigned char new_elem = '0' + (new_elem_int % BASE);
        carrying = new_elem_int / BASE;
        new_buf.append(new_elem);
    }
    while (other.buf.get_elem(i) != '\0')
    {
        int new_elem_int = carrying + this->buf.get_elem(i) - '0';
        unsigned char new_elem = '0' + (new_elem_int % BASE);
        carrying = new_elem_int / BASE;
        new_buf.append(new_elem);
    }
    std::string s {new_buf.get_buffer()};
    std::reverse(s.begin(), s.end());
    return Seven {s};
}

// bool operator==(const Seven &other) const
// {
//     return ;
// }