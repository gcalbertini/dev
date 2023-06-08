#ifndef MY_VEC_TEMPLATE_HPP
#define MY_VEC_TEMPLATE_HPP

#include "myVectorBase.hpp"

// Naive: only assumed this will operate under limited conditions for standard numerical type objects lol
// Allocator used with C++17 in mind

namespace myNaive
{
    template <class T, typename A = std::allocator<T>> // class or typename used interchangeably; default allocator used
    class generalVector : private myVecBase<T, A>
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
        generalVector &operator=(generalVector &&rhs);            // move assignment for prev init object
        generalVector &operator=(const generalVector &rhs);       // deep copy assignment for originally init object
        const double &operator[](int n) const { return elem[n]; } // access: read for const vector
        double &operator[](int n) { return elem[n]; }             // access: read for non-const vector

        // king shit
        std::size_t size() const { return sz; } // the current size
        void resize(int newsize);
        void reserve(int newalloc);
        std::size_t capacity() const { return space; }
        void push_back(const T &val);
        double *checkElem() { return elem; }

        ~generalVector()
        {
            allocator_traits<A>::destroy(this->alloc, this->elem); // Call the destructor for each element as we dealt with uninitialized memory buffers
            allocator_traits<A>::deallocate(this->alloc, this->elem, this->space);
        }
    };

};

#endif // MY_VEC_TEMPLATE_HPP
