#ifndef MY_GEN_VEC_BASE_HPP
#define MY_GEN_VEC_BASE_HPP

#include <iostream>
#include <algorithm>
#include <memory>

namespace myNaive
{
    template <class T, class A>
    struct baseVec
    {
        A alloc;           // use to allocate to handle mem for elements
        std::size_t sz;    // the size, an unsigned integer type of any sizeof expression
                           // and as is guaranteed to be able to express the maximum size of any object (including any array) in C++
                           // see note on constructor with init lst
        T *elem;           // ptr to first elem (of type T) or 0
        std::size_t space; // number of elements plus number of free slots

        baseVec(const A &a, size_t n) : alloc{a}, elem{alloc.allocate(n)}, sz{n}, space{n} {};

        // Copy constructor
        baseVec(const baseVec &other)
            : alloc(other.alloc), sz(other.sz), elem(alloc.allocate(other.space)), space(other.space)
        {
            std::uninitialized_copy(other.elem, other.elem + other.sz, elem);
        }

        baseVec(const A &a, std::initializer_list<T> lst) : alloc{a}, sz{lst.size()}, space{lst.size()}
        {
            std::uninitialized_copy(lst.begin(), lst.end(), elem);
            std::cout << "vecBase::vecBase(lst)\n";
        }

        // Copy assignment operator
        baseVec &operator=(const baseVec &other)
        {
            if (this != &other)
            {
                // Deallocate existing memory
                alloc.deallocate(elem, space);

                // Copy member variables from the other object
                alloc = other.alloc;
                sz = other.sz;
                space = other.space;

                // Allocate new memory
                elem = alloc.allocate(space);

                // Copy elements from other.elem to elem
                std::uninitialized_copy(other.elem, other.elem + other.sz, elem);
            }
            return *this;
        }

        // Move constructor
        baseVec(baseVec &&other)
            : alloc(std::move(other.alloc)), sz(other.sz), elem(other.elem), space(other.space)
        {
            other.sz = 0;
            other.elem = nullptr;
            other.space = 0;
        }

        // Move assignment operator
        baseVec &operator=(baseVec &&other)
        {
            if (this != &other)
            {
                // Deallocate existing memory
                alloc.deallocate(elem, space);

                // Move member variables from the other object
                alloc = std::move(other.alloc);
                sz = other.sz;
                elem = other.elem;
                space = other.space;

                // Reset the other object
                other.sz = 0;
                other.elem = nullptr;
                other.space = 0;
            }
            return *this;
        }

        ~baseVec()
        {
            alloc.deallocate(elem, space);
        }
    };

}

#endif