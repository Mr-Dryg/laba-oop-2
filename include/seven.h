#pragma once
#include <string>
#include "buffer.h"

#define BASE 7

class Seven
{
private:
    Buffer buf;
public:
    Seven() : Seven("0") {};
    Seven(std::string t);
    // конструктор копирования
    Seven(const Seven& other) : Seven(other.get_string()) {};
    virtual ~Seven() noexcept = default;

    std::string get_string() const;
    
    // оператор присваивания копированием
    Seven& operator=(const Seven& other);

    Seven operator+(const Seven& other) const;
    Seven operator-(const Seven& other) const;
    bool operator>(const Seven& other) const;
    bool operator<(const Seven& other) const;
    bool operator>=(const Seven& other) const;
    bool operator<=(const Seven& other) const;
    bool operator==(const Seven& other) const;
    bool operator!=(const Seven& other) const;

    void remove_leading_zeros();

    friend std::ostream& operator<<(std::ostream& os, const Seven& num) {
        os << num.get_string();
        return os;
    }
};