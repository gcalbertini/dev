#ifndef MY_GEN_VEC_HPP
#define MY_GEN_VEC_HPP

#include "baseVec.hpp"

namespace myNaive {
    template <class T, class A = std::allocator<T>>
    class genericVec : private baseVec<T, A> {
    public:
        // Default constructor
        genericVec(size_t n)
            : baseVec<T, A>(n) {
            // Additional assignments specific to the derived class, if any
        }

        // Copy constructor
        genericVec(const genericVec& rhs)
            : baseVec<T, A>(rhs) {
            // Additional assignments specific to the derived class, if any
        }

        // Copy assignment operator
        genericVec& operator=(const genericVec& rhs) {
            if (this != &rhs) {
                baseVec<T, A>::operator=(rhs);  // Call base class copy assignment operator

                // Additional assignments specific to the derived class, if any
            }
            return *this;
        }

        // Move constructor
        genericVec(genericVec&& other)
            : baseVec<T, A>(std::move(other)) {
            // Additional move constructor logic specific to derived class
        }

        // Move assignment operator
        genericVec& operator=(genericVec&& other) {
            if (this != &other) {
                // Call base class move assignment operator
                baseVec<T, A>::operator=(std::move(other));

                // Additional move assignment logic specific to derived class
            }
            return *this;
        }

        // Overloads
        genericVec& operator=(genericVec&& rhs);                      // Move assignment for previously initialized object
        genericVec& operator=(const genericVec& rhs);                 // Deep copy assignment for originally initialized object
        const T& operator[](size_t n) const { return this->elem[n]; } // Non-checked access: read for const vector
        T& operator[](size_t n) { return this->elem[n]; }             // Non-checked access: read for non-const vector
        T& at(size_t n)                                               // Checked access: read for const vector
        {
            if (n >= this->sz) {
                throw std::out_of_range("Index out of range");
            }
            return this->elem[n];
        }

        const T& at(size_t n) const // Checked access: read for non-const vector
        {
            if (n >= this->sz) {
                throw std::out_of_range("Index out of range");
            }
            return this->elem[n];
        }

        // Member functions
        std::size_t size() const { return this->sz; }  // Current size
        void resize(size_t newsize);
        void reserve(size_t newalloc);
        std::size_t capacity() const { return this->space; }
        void push_back(const T& d);
        T* checkElem() { return this->elem; }

        // Destructor
        ~genericVec() { delete[] this->elem; }  // Frees memory
    };
};

#endif // MY_GEN_VEC_HPP
