#include <iostream>
#include "include/seven.h"

int main()
{
    Seven a("12");
    Seven b("13");
    Seven result = a - b;
    std::cout << result << '\n';
}