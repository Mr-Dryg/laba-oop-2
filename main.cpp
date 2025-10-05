#include <iostream>
#include "include/buffer.h"

int main()
{
    Buffer buf{};
    std::cout << buf.get_buffer() << '\n';
}