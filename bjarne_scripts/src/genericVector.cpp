#include "genericVector.hpp"

namespace myNaive
{
    // Default constructor with size_t passed as arg
    template <class T, typename A>
    generalVector<T, A>::generalVector(size_t n) : myVecBase<T, A>(n) //(A{}, n) but A's default constructor for our already default allocator doesn't need to be overwritten again
    {
        cout << "I inherited default constructor from the base!\n";
    }

    // Default list-init constructor
    template <class T, typename A>
    generalVector<T, A>::generalVector(std::initializer_list<T> lst) : myVecBase<T, A>(lst.size())
    {
        cout << "I inherited default list constructor from the base and filled with default values!\n";
    }

    // Copy constructor
    template <class T, typename A>
    generalVector<T, A>::generalVector(const generalVector &rhs)
        : myVecBase<T, A>(rhs.alloc, rhs.space)
    {
        uninitialized_copy(rhs.elem, rhs.elem + rhs.sz, this->elem); // Since construct(...) deprecated in C++17/20: calls construct on each element in the input sequence to “copy” that
                                                                     // element into the destination. That algorithm uses the iterator dereference operator
                                                                     // to fetch elements from the input sequence
        cout << "I made a new (copy) constructor! Base didn't have one. New space is " << space << " and new size is " << sz << "!\n";
    }

    // Copy assignment overload
    template <class T, typename A>
    generalVector<T, A> &generalVector<T, A>::operator=(const generalVector &rhs)
    {                     // copy assignment; this added for clarity
        if (this != &rhs) // Self-assignment check
        {
            // Deallocate existing memory
            std::allocator_traits<A>::deallocate(this->alloc, this->elem, this->space);

            // Copy the allocator and size from the rhs object
            this->alloc = rhs.alloc;
            this->sz = rhs.sz;
            this->space = rhs.space;

            // Allocate new memory and copy the elements
            this->elem = std::allocator_traits<A>::allocate(this->alloc, this->space);
            uninitialized_copy(rhs.elem, rhs.elem + rhs.sz, this->elem);
        }
        cout << "I used copy assignment overload. Base didn't have one. New space is " << space << " and new size is " << sz << "!\n";
        return *this;
    }

    //  typically don't need to use destroy explicitly for move semantics; during the move operation, the source object is typically left
    // in a state where it's safe to be destroyed, and the destructor will be called on the source object when it goes out of scope or is explicitly destroyed
    // same logic applies to copy ops where intent is to copy over objects first and foremost

    // Move constructor
    template <class T, typename A>
    generalVector<T, A>::generalVector(generalVector &&rhs) : myVecBase<T, A>(std::move(rhs.alloc), rhs.space) // signaling that we are done with the resources held by rhs.alloc, and we can take ownership of those resources in the new object.
    {
        this->elem = rhs.elem;
        this->sz = rhs.sz;
        rhs.elem = nullptr;
        rhs.sz = 0;
        rhs.space = 0;
        cout << "I created another move constructor instead of STL default. Base didn't have one. New space is " << space << " and new size is " << sz << "!\n";
    }

    // Move assignment
    template <class T, typename A>
    generalVector<T, A> &generalVector<T, A>::operator=(generalVector &&rhs)
    {
        if (this != &rhs) // Self-assignment check
        {
            // Deallocate existing memory
            std::allocator_traits<A>::deallocate(this->alloc, this->elem, this->space);

            // Move the allocator and size from the rhs object
            this->alloc = std::move(rhs.alloc);
            this->sz = rhs.sz;
            this->space = rhs.space;

            // Move the pointer from the rhs object
            this->elem = rhs.elem;

            // Reset the rhs object
            rhs.elem = nullptr;
            rhs.sz = 0;
            rhs.space = 0;
        }
        cout << "I used move assignment. Base didn't have one. New space is " << space << " and new size is " << sz << "!\n";
        return *this;
    }

};