#ifndef MY_VEC_TEMPLATE_HPP
#define MY_VEC_TEMPLATE_HPP

#ifndef UTILS_HPP
#define UTILS_HPP
#include "utils.hpp"
#endif // utils.hpp

// Naive: only assumed this will operate under limited conditions for standard numerical type objects lol
// Allocator used with C++11 in mind though deprecation warnings for construct/destroy methods in C++17 and in C++20 removed; intended to manipulate (generic) uninit memory storage
namespace myNaive
{
    template <class T, typename A = std::allocator<T>> // class or typename used interchangeably
    class babyVectorTemplate
    {
        std::size_t sz;    // the size, an unsigned integer type of any sizeof expression
                           // and as is guaranteed to be able to express the maximum size of any object (including any array) in C++
                           // see note on constructor with init lst
        T *elem;           // ptr to first elem (of type T) or 0.0
        std::size_t space; // number of elements plus number of free slots
        A alloc; //use allocate to handle memory for elements
    public:
        // constructors
        babyVectorTemplate() : sz{0}, elem{nullptr}, space{0} {}
        explicit babyVectorTemplate(std::size_t s, T def = T());   // default constructor without implicit conversions; T() default value of type unless specified by user
        explicit babyVectorTemplate(std::initializer_list<T> lst); // default init-list constructor without implicit conversions
        babyVectorTemplate(const babyVectorTemplate &rhs);         //(deep) copy constructor
        babyVectorTemplate(babyVectorTemplate &&rhs);              // move constructor to avoid expensive copies for prev unint object (C++ 11)

        // overloads
        babyVectorTemplate &operator=(babyVectorTemplate &&rhs);      // move assignment for prev init object
        babyVectorTemplate &operator=(const babyVectorTemplate &rhs); // deep copy assignment for originally init object
        const T &operator[](int n) const { return elem[n]; }          // unchecked access for "backwards compatability" or efficiency
        T &operator[](int n) { return elem[n]; }                      // unchecked access for "backwards compatability" or efficiency
        T &at(int n);                                                 // checked access for slow Kings
        const T &at(int n) const;                                     // checked access for slow Kings that const

        // king shit
        std::size_t size() const { return sz; } // the current size
        void resize(int newsize);
        void reserve(int newalloc);
        std::size_t capacity() const { return space; }
        void push_back(const T &);
        T *checkElem() { return elem; }

        // destructor
        ~babyVectorTemplate() { delete[] elem; } // frees memory
    };

};

#endif // myVecTemplate