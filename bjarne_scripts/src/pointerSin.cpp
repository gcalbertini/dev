#include "utils.hpp"

int *foo()
{
    int x = 5;
    // ...
    return &x;
}; // int x destroyed here

std::vector<int> &bar()
{
    std::vector<int> a{4};
    // ...
    return a;
}; // vector a destroyed here

int main()
{

    // dereference null pointer --> tinkering with memory you know nothing about
    int *p = nullptr;
    *p = 7;

    // nonsense; attempts to move this dubious pointer to another dubious mem address
    int *pp;
    int *a = p + *pp;

    // out of range access
    int a[5];       // 5 elements indexed 0 to 4
    int *p = &a[5]; // 6th element access; only try int *p = &a[0]; or simply int *p = a
    *p = 10;        // oops, element a[5] reference
    a[5] = 12;      // oops, a[4] is last element

    // access through deleted ptr
    int *pp = new int{7};
    // ...
    delete pp;
    // ...
    *pp = 13; // oops

    int *p = new int[4]; // array of objects
    delete p;            // deletes single object; need to use delete [] p; or Vector_ref

    int *pp = foo();
    // ...
    *pp = 10; // big oops -- return from local scope of function deallocates objects from stack
              // but insist on scribbling over its mem address

    std::vector<int> &p = bar();
    // ...
    p[2] = 1; // oops

    return 1;
}