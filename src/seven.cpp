#include "../include/seven.h"
#include <stdexcept>

Seven::Seven(const std::initializer_list<unsigned char> & t)
{
    int i = 0;
    for (const auto& digit : t)
    {
        if (0 <= digit && digit <= 6)
        {
            buf[i]
        }
        else
        {
            throw std::invalid_argument("Digit must be between 0 and 6");
        }
    }

}