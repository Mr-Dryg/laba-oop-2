#pragma once
#include <string>

#define GROW 5

class Buffer
{
private:
    size_t size;
    size_t max_size;
    unsigned char* buf = nullptr;
    void set_max_size(const size_t& new_max_size);
public:
    Buffer() : size{0}, max_size{5}, buf {new unsigned char[max_size]{'\0'}} {};
    Buffer(std::string t);
    // конструктор копирования
    Buffer(const Buffer&  other);
    virtual ~Buffer() noexcept;
    
    size_t get_size() const;
    void set_elem(const int& i, const unsigned char& elem);
    void push_back(const unsigned char& elem);
    unsigned char get_elem(const int& i) const;
    std::string get_buffer() const;

    // оператор присваивания копированием
    Buffer& operator=(const Buffer& other);

    friend std::ostream& operator<<(std::ostream& os, const Buffer& buf) {
        os << buf.get_buffer();
        return os;
    }
};