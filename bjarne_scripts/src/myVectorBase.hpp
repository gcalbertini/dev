#ifndef MY_VEC_BASE
#define MY_VEC_BASE

#ifndef UTILS_HPP
#define UTILS_HPP
#include "utils.hpp"

#include <memory>    // Include the <memory> header for C++17/20 allocator
#include <algorithm> //for swap

/*
 Why make this? Allocator methods may throw an exception and not be able to returned or return prematurely
 leaving dangling memory references from free store; using unique_ptr may be a solution but is not
 the one thats most expressive of our intent -- the base class is a fundamental concept dealing with free store access
 and vector classes are an interface to it. This then leverages RAII by having pointers (initialized in constructor)
 have their mem cleanup accounted for after destructors called after objects exit from local function routines.
*/
namespace myNaive
{

    template <class T, class A>
    class myVecBase
    {
    public:
        A alloc;      // allocator
        T *elem;      // start of allocation
        size_t sz;    // number of elements
        size_t space; // amount of allocated space

        const T &operator[](int n) const { return elem[n]; } // access: read for const vector
        T &operator[](int n) { return elem[n]; }             // access: read for non-const vector
        std::size_t capacity() const { return space; }       // the current space
        std::size_t size() const { return sz; }              // the current size
        T *checkElem() { return elem; }

        void print() const
        {
            std::cout << "myVecBase { elem=" << elem << "; sz=" << sz << "; space =" << space << "};\n";
        }

        myVecBase() : sz{0}, elem{nullptr}, space{0}
        {
            std::cout << "myVecBase::myVecBase(Default size/space= 0);\n";
        }

        myVecBase(const A &a, size_t n) : alloc{a}, elem{std::allocator_traits<A>::allocate(alloc, n)}, sz{n}, space{n}
        {
            std::cout << "myVecBase::myVecBase size=" << n << ");\n";
        }

        myVecBase(const A &a, std::initializer_list<T> lst) : alloc{a}, sz{lst.size()}, elem{std::allocator_traits<A>::allocate(alloc, sz)}, space{sz}
        {
            uninitialized_copy(lst.begin(), lst.end(), this->elem); // or just elem as this is from object calling its own member (and a base class)
            std::cout << "myVecBase::myVecBase(alloc_lst=" << alloc << ", size=" << lst.size() << ");\n";
        }

        virtual ~myVecBase() // by making the destructor virtual, the derived class destructors will be called properly when deleting through a pointer to the base class
        {
            std::cout << "myVecBase::~myVecBase();\n";
        } // destructor
    };

}

#endif // utils.hpp
#endif // myVecBase