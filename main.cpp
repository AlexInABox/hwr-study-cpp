#include <iostream>
#include "functions.h"

int freaky_number = 1234;
std::string test = "This is a string";

long long longnumber = 123;

void functionA(){
    std::cout << "Hi mom!" << std::endl;
}

int main()
{
    std::cout << "Hi mom!" << std::endl;
    std::cout << test << std::endl;
    std::cout << freaky_number << std::endl;

    functionA();
    functionF();
    return 0;
}