#include <iostream>

struct Foo {
    int value;
    void print() {
        std::cout << "Value: " << value << std::endl;
    }
};

int main() {
    Foo obj{42};
    int Foo::*ptr = &Foo::value; // Pointer-to-member variable

    std::cout << obj.*ptr << std::endl; // Access member through object and pointer-to-member
    Foo* objPtr = &obj;
    std::cout << objPtr->*ptr << std::endl; // Access member through pointer-to-object and pointer-to-member

    void (Foo::*funcPtr)() = &Foo::print; // Pointer-to-member function
    (obj.*funcPtr)(); // Call member function through object and pointer-to-member-function
    (objPtr->*funcPtr)(); // Call member function through pointer-to-object and pointer-to-member-function

    return 0;
}