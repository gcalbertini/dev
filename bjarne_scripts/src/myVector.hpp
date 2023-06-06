#ifndef MY_VEC_HPP
#define MY_VEC_HPP

#ifndef UTILS_HPP
#define UTILS_HPP
#include "utils.hpp"
#endif // utils.hpp
namespace myNaive
{

    class babyVector
    {
        /*
            invariant:
                if 0<=n<sz, elem[n] is element n
                sz<=space;
                if sz < space there is space for (space-sz) doubles after elem[sz-1]
        */
        std::size_t sz;    // the size, an unsigned integer type of any sizeof expression
                           // and as is guaranteed to be able to express the maximum size of any object (including any array) in C++
                           // see note on constructor with init lst
        double *elem;      // ptr to first elem (of type double) or 0
        std::size_t space; // number of elements plus number of free slots
    public:
        // constructors
        babyVector() : sz{0}, elem{nullptr}, space{0} {}
        explicit babyVector(std::size_t s);                     // default constructor without implicit conversions
        explicit babyVector(std::initializer_list<double> lst); // default init-list constructor without implicit conversions
        babyVector(const babyVector &rhs);                      //(deep) copy constructor
        babyVector(babyVector &&rhs);                           // move constructor to avoid expensive copies for prev unint object (C++ 11)

        // overloads
        babyVector &operator=(babyVector &&rhs);                  // move assignment for prev init object
        babyVector &operator=(const babyVector &rhs);             // deep copy assignment for originally init object
        const double &operator[](int n) const { return elem[n]; } // access: read for const vector
        double &operator[](int n) { return elem[n]; }             // access: read for non-const vector

        // king shit
        std::size_t size() const { return sz; } // the current size
        void resize(int newsize);
        void reserve(int newalloc);
        std::size_t capacity() const { return space; }
        void push_back(const double &d);
        double *checkElem() { return elem; }

        // destructor
        ~babyVector() { delete[] elem; } // frees memory
    };

    /* Generic Programming Example:
    template <typename T> //or class T
    class babyVectorTemplate
    {
      
    std::size_t sz;    // the size, an unsigned integer type of any sizeof expression
                       // and as is guaranteed to be able to express the maximum size of any object (including any array) in C++
                       // see note on constructor with init lst
    T *elem;           // ptr to first elem (of type T) or 0
    std::size_t space; // number of elements plus number of free slots

    public:
    // constructors
    babyVectorTemplate() : sz{0}, elem{nullptr}, space{0} {}
    explicit babyVectorTemplate(std::size_t s);                // default constructor without implicit conversions
    explicit babyVectorTemplate(std::initializer_list<T> lst); // default init-list constructor without implicit conversions
    babyVectorTemplate(const babyVectorTemplate &rhs);         //(deep) copy constructor
    babyVectorTemplate(babyVectorTemplate &&rhs);              // move constructor to avoid expensive copies for prev unint object (C++ 11)

    // overloads
    babyVectorTemplate &operator=(babyVectorTemplate &&rhs);      // move assignment for prev init object
    babyVectorTemplate &operator=(const babyVectorTemplate &rhs); // deep copy assignment for originally init object
    const T &operator[](int n) const { return elem[n]; }          // access: read for const vector
    T &operator[](int n) { return elem[n]; }                      // access: read for non-const vector

    // king shit
    std::size_t size() const { return sz; } // the current size
    void resize(int newsize);
    void reserve(int newalloc);
    std::size_t capacity() const { return space; }
    void push_back(const T &d);
    T *checkElem() { return elem; }

    // destructor
    ~babyVector() { delete[] elem; } // frees memory
    */
};

#endif // myVec