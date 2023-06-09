#ifndef MY_BASE_VEC_HPP
#define MY_BASE_VEC_HPP

#include <iostream>  // Added for printing exception messages
#include <stdexcept> // Added for std::out_of_range
#include <algorithm>
#include <memory>

template <class T, class A>
class generalVec;

using namespace std;

template <class T, class A>
struct vecBase
{
    A alloc;      // allocator; C++17 in mind
    T *elem;      // start of allocation
    size_t sz;    // num elements
    size_t space; // amount of alloc space

    vecBase(const A &a, size_t N) : alloc{a}, sz{N}, space{N}
    {
        elem = std::allocator_traits<A>::allocate(alloc, N);
        std::uninitialized_fill_n(elem, N, T()); // Fill elements with default-constructed values
        std::cout << "vecBase::vecBase(N)\n";
    }

    vecBase(const A &a, std::initializer_list<T> lst) : alloc{a}, sz{lst.size()}, space{lst.size()}
    {
        std::uninitialized_copy(lst.begin(), lst.end(), elem);
        std::cout << "vecBase::vecBase(lst)\n";
    }

    vecBase(const vecBase &rhs)
        : alloc(std::allocator_traits<A>::select_on_container_copy_construction(rhs.alloc)),
          sz(rhs.sz), space(rhs.space)
    {
        elem = std::allocator_traits<A>::allocate(alloc, this->sz);
        std::cout << "vecBase::vecBase(const vecBase&)\n";
        try
        {
            std::uninitialized_copy(rhs.elem, rhs.elem + rhs.sz, elem);
        }
        catch (...)
        {
            std::allocator_traits<A>::deallocate(alloc, elem, this->sz);
            throw;
        }
    }

    vecBase(vecBase &&rhs)
        : alloc(std::move(rhs.alloc)), elem(rhs.elem), sz(rhs.sz), space(rhs.space)
    {
        rhs.elem = nullptr;
        rhs.sz = 0;
        rhs.space = 0;
        std::cout << "vecBase::vecBase(vecBase&&)\n";
    }

    virtual ~vecBase() // in case we have a base ptr to derived class
    {
        if (elem)
        {
            std::allocator_traits<A>::destroy(alloc, elem);
            std::allocator_traits<A>::deallocate(alloc, elem, space);
        }
        std::cout << "~vecBase::vecBase()\n";
    }

    template <class U, class B>
    friend class generalVec;
};

#endif // MY_BASE_VEC_HPP
