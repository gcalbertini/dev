#ifndef MY_VEC_TEMPLATE_HPP
#define MY_VEC_TEMPLATE_HPP

#include <memory>    // Include the <memory> header for C++17/20 allocator
#include <algorithm> //for swap
#include "myVectorBase.hpp"

// Naive: only assumed this will operate under limited conditions for standard numerical type objects lol
// Allocator used with C++17 in mind

namespace myNaive
{
    template <class T, typename A = std::allocator<T>> // class or typename used interchangeably; default allocator used
    class generalVector : public myVecBase<T, A>
    {
    public:
        // constructors
        generalVector() = default;                   // summons myVecBase() : sz{0}, elem{nullptr}, space{0} {}
        explicit generalVector(size_t n);            // explicit keyword is used to avoid implicit conversions from size_t to generalVector
                                                     // generalVector<int> vec2 = 10 is ERROR (intention not clear!) but generalVector<int> vec1(5) is OK
        generalVector(std::initializer_list<T> lst); // default init-list constructor without implicit conversions; not explicit as
                                                     // generalVector<int> vec = {1, 2, 3} is understandable
        generalVector(const generalVector &rhs);     //(deep) copy constructor
        generalVector(generalVector &&rhs);          // move constructor to avoid expensive copies for prev unint object (C++ 11)

        // overloads
        generalVector &operator=(generalVector &&rhs);      // move assignment for prev init object
        generalVector &operator=(const generalVector &rhs); // deep copy assignment for originally init object

        // king shit
        void resize(size_t newsize);
        void reserve(size_t newalloc);
        void push_back(const T &val);

        ~generalVector()
        {
            std::allocator_traits<A>::destroy(this->alloc, this->elem); // Call the destructor for each element as we dealt with uninitialized memory buffers
            std::allocator_traits<A>::deallocate(this->alloc, this->elem, this->space);
        }
    };

};

#endif // MY_VEC_TEMPLATE_HPP
