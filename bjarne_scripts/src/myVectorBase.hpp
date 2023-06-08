#ifndef MY_VEC_BASE
#define MY_VEC_BASE

#ifndef UTILS_HPP
#define UTILS_HPP
#include "utils.hpp"

#include <memory> // Include the <memory> header for C++17/20 allocator

/*
 Why make this? Allocator methods may throw an exception and not be able to returned or return prematurely
 leaving dangling memory references from free store; using unique_ptr may be a solution but is not
 the one thats most expressive of our intent -- the base class is a fundamental concept dealing with free store access
 and vector classes are an interface to it. This then leverages RAII by having pointers (initialized in constructor)
 have their mem cleanup accounted for after destructors called after objects exit from local function routines.
*/

template <class T, class A>
struct myVecBase // struct members public by default
{
    A alloc;      // allocator
    T *elem;      // start of allocation
    size_t sz;    // number of elements
    size_t space; // amount of allocated space

    void print() const
    {
        cout << "myVecBase { alloc=" << alloc << "; elem=" << elem << "; sz=" << sz << "; space =" << space "};\n";
    }

    myVecBase() : sz{0}, elem{nullptr}, space{0} {}
    {
        cout << "myVecBase::myVecBase(Default size/space= 0);\n";
    }

    myVecBase(const A &a, size_t n) : alloc{a}, elem{allocator_traits<A>::allocate(alloc, n)}, sz{n}, space{n}
    {
        cout << "myVecBase::myVecBase(alloc=" << alloc << ", size=" << n ");\n";
    }

    myVecBase(const A &a, initializer_list<T> lst) : alloc{a}, sz{lst.size()}, elem{allocator_traits<A>::allocate(alloc, sz)}, space{sz}
    {
        uninitialized_copy(lst.begin(), lst.end(), this->elem); // or just elem as this is from object calling its own member (and a base class)
        cout << "myVecBase::myVecBase(alloc_lst=" << alloc << ", size=" << lst.size() ");\n";
    }

    virtual ~myVecBase() //by making the destructor virtual, the derived class destructors will be called properly when deleting through a pointer to the base class
    {
        cout << "myVecBase::~myVecBase();\n";
    } // destructor
};

#endif // utils.hpp
#endif // myVecBase