#include <memory> // Include the <memory> header for C++17/20 allocator
#include <algorithm> //for swap
#include "genericVector.hpp"

// Note: Explicitly need ot use this-> as we refer to a member of the derived class as opposed to base class
namespace myNaive
{
    // Default constructor with size_t passed as arg
    template <class T, typename A>
    generalVector<T, A>::generalVector(size_t n) : myVecBase<T, A>(A{}, n)
    {
        std::cout << "I inherited default constructor from the base!\n";
    }

    // Default list-init constructor
    template <class T, typename A>
    generalVector<T, A>::generalVector(std::initializer_list<T> lst) : myVecBase<T, A>(A{}, lst.size())
    {
        std::cout << "I inherited default list constructor from the base and filled with default values!\n";
    }

    // Copy constructor
    template <class T, typename A>
    generalVector<T, A>::generalVector(const generalVector &rhs)
        : myVecBase<T, A>(rhs.alloc, rhs.space)
    {
        std::uninitialized_copy(rhs.elem, rhs.elem + rhs.sz, this->elem); // Since construct(...) deprecated in C++17/20: calls construct on each element in the input sequence to “copy” that
                                                                     // element size_to the destination. That algorithm uses the iterator dereference operator
                                                                     // to fetch elements from the input sequence
        std::cout << "I made a new (copy) constructor! Base didn't have one. New space is " << this->space << " and new size is " << this->sz << "!\n";
    }

    // Copy assignment overload
    template <class T, typename A>
    generalVector<T, A> &generalVector<T, A>::operator=(const generalVector &rhs)
    {
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
            std::uninitialized_copy(rhs.elem, rhs.elem + rhs.sz, this->elem);
        }
        std::cout << "I used copy assignment overload. Base didn't have one. New space is " << this->space << " and new size is " << this->sz << "!\n";
        return *this;
    }

    template <class T, typename A>
    void generalVector<T, A>::resize(size_t newsize)
    {
        reserve(newsize);
        for (size_t i = this->sz; i < newsize; ++i)
            this->elem[i] = T(); // init new elements
        this->sz = newsize;
    }

    template <class T, typename A>
    void generalVector<T, A>::reserve(size_t newalloc)
    {
        if (newalloc <= this->capacity())
            return; // never decrease allocation
        // allocate new space here
        myVecBase<T, A> b{this->alloc, newalloc};                    // allocate new space
        std::uninitialized_copy(this->elem, this->elem + this->size(), b.elem); // copy
        std::allocator_traits<A>::destroy(this->alloc, this->elem);       // destroy old
        std::swap<myVecBase<T, A>>(*this, b);                             // swap representations
    }

    template <class T, typename A>
    void generalVector<T, A>::push_back(const T &val)
    {
        if (this->space == 0)
            reserve(8);       // start with space for 8 elements
        else if (this->sz == this->space) // get more space, usually done by doubling it
            reserve(2 * this->space);
        this->elem[this->sz] = val;
        this->sz = this->sz + 1;
    }

    //  typically don't need to use destroy explicitly for move semantics; during the move operation, the source object is typically left
    // in a state where it's safe to be destroyed, and the destructor will be called on the source object when it goes out of scope or is explicitly destroyed
    // same logic applies to copy ops where size_tent is to copy over objects first and foremost

    // Move constructor
    template <class T, typename A>
    generalVector<T, A>::generalVector(generalVector &&rhs) : myVecBase<T, A>(std::move(rhs.alloc), rhs.space) // signaling that we are done with the resources held by rhs.alloc, and we can take ownership of those resources in the new object.
    {
        this->elem = rhs.elem;
        this->sz = rhs.sz;
        rhs.elem = nullptr;
        rhs.sz = 0;
        rhs.space = 0;
        std::cout << "I created another move constructor instead of STL default. Base didn't have one. New space is " << this->space << " and new size is " << this->sz << "!\n";
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

            // Move the posize_ter from the rhs object
            this->elem = rhs.elem;

            // Reset the rhs object
            rhs.elem = nullptr;
            rhs.sz = 0;
            rhs.space = 0;
        }
        std::cout << "I used move assignment. Base didn't have one. New space is " << this->space << " and new size is " << this->sz << "!\n";
        return *this;
    }

};