#ifndef MY_GENERAL_VEC_HPP
#define MY_GENERAL_VEC_HPP

#include <iostream>  // Added for printing exception messages
#include <stdexcept> // Added for std::out_of_range
#include "vecBase.hpp"

template <class T, class A = std::allocator<T>>
class generalVec : private vecBase<T, A>
{
public:
    using vecBase<T, std::allocator<T>>::vecBase;

    generalVec() : vecBase<T, std::allocator<T>>(std::allocator<T>(), 0)
    {
        this->elem = nullptr;
        this->sz = 0;
        this->space = 0;
    }

    explicit generalVec(size_t size) : vecBase<T, A>(A(), size)
    {
        try
        {
            this->elem = std::allocator_traits<A>::allocate(this->alloc, size);
            std::uninitialized_fill_n(this->elem, size, T()); // Fill elements with default-constructed values
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << "Exception caught in constructor: " << e.what() << std::endl; // Print exception message
            throw;
        }
    }

    generalVec(const generalVec &rhs) : vecBase<T, A>(rhs)
    {
        reserve(rhs.sz);
        std::uninitialized_copy(rhs.elem, rhs.elem + rhs.sz, this->elem);
        this->sz = rhs.sz;
    }

    generalVec(std::initializer_list<T> lst)
        : vecBase<T, A>(A{}, lst.size())
    {
        std::uninitialized_copy(lst.begin(), lst.end(), this->elem); // Fill elements with lst values
        this->sz = lst.size();
        this->space = lst.size();
    }

    void reserve(size_t n);
    void push_back(const T &value);
    void resize(size_t newsize, const T &val = T());
    T &at(size_t n);
    const T &at(size_t n) const;
    size_t capacity() const;
    size_t size() const;
    T *getElem() const;
    T *data(size_t n);
    const T *data(size_t n) const;

    T &operator[](size_t n);
    const T &operator[](size_t n) const;

    generalVec &operator=(const generalVec &rhs);
    generalVec &operator=(generalVec &&rhs);

    ~generalVec(); // Destructor
};

template <class T, class A>
generalVec<T, A>::~generalVec()
{
    std::cout << "Calls destructor of base class for cleanup.\n";
}

template <class T, class A>
inline void generalVec<T, A>::reserve(size_t n)
{
    if (n <= this->space)
        return;

    T *newElem = nullptr;
    try
    {
        newElem = std::allocator_traits<std::allocator<T>>::allocate(this->alloc, n);
        std::uninitialized_move(this->elem, this->elem + this->sz, newElem);
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Exception caught in reserve(): " << e.what() << std::endl; // Print exception message
        throw;
    }

    if (this->elem)
    {
        std::allocator_traits<std::allocator<T>>::deallocate(this->alloc, this->elem, this->space);
    }

    this->elem = newElem;
    this->space = n;
}

template <class T, class A>
inline void generalVec<T, A>::push_back(const T &value)
{
    if (this->space == 0)
    {
        reserve(8);
    }
    else if (this->sz == this->space)
    {
        size_t newSpace = this->space * 2;
        reserve(newSpace);
    }

    try
    {
        std::allocator_traits<std::allocator<T>>::construct(this->alloc, this->elem + this->sz, value);
        ++this->sz;
    }
    catch (const std::exception &e)
    {
        if (this->space > 0 && this->sz < this->space)
        {
            std::allocator_traits<std::allocator<T>>::destroy(this->alloc, this->elem + this->sz);
        }
        std::cerr << "Exception caught in push_back(): " << e.what() << std::endl; // Print exception message
        throw;
    }
}

template <class T, class A>
inline void generalVec<T, A>::resize(size_t newsize, const T &val)
{   
    if (newsize == this->sz){
        std::cerr << "Cannot resize to same size!\n";
    }

    if (newsize < this->sz)
    {

        for (size_t i = newsize; i < this->sz; ++i)
        {
            std::allocator_traits<std::allocator<T>>::destroy(this->alloc, this->elem + i);
        }
        this->sz = newsize;
    }
    else //(newsize > this->sz)
    {
        reserve(newsize);
        try
        {
            for (size_t i = this->sz; i < newsize; ++i)
            {
                std::allocator_traits<std::allocator<T>>::construct(this->alloc, this->elem + i, val);
            }
            this->sz = newsize;
        }
        catch (const std::exception &e)
        {
            for (size_t i = this->sz; i < newsize; ++i)
            {
                std::allocator_traits<std::allocator<T>>::destroy(this->alloc, this->elem + i);
            }
            std::cerr << "Exception caught in resize(): " << e.what() << std::endl; // Print exception message
            throw;
        }
    }
}

template <class T, class A>
inline T &generalVec<T, A>::at(size_t n)
{
    if (n >= this->sz)
    {
        throw std::out_of_range("Index out of range");
    }
    return this->elem[n];
}

template <class T, class A>
inline const T &generalVec<T, A>::at(size_t n) const
{
    if (n >= this->sz)
    {
        throw std::out_of_range("Index out of range");
    }
    return this->elem[n];
}

template <class T, class A>
inline size_t generalVec<T, A>::capacity() const
{
    return this->space;
}

template <class T, class A>
size_t generalVec<T, A>::size() const
{
    return this->sz;
}

template <class T, class A>
T *generalVec<T, A>::getElem() const
{
    return this->elem;
}

template <class T, class A>
inline T *generalVec<T, A>::data(size_t n)
{
    if (n >= this->sz)
    {
        throw std::out_of_range("Index out of range");
    }
    return this->elem + n;
}

template <class T, class A>
inline const T *generalVec<T, A>::data(size_t n) const
{
    if (n >= this->sz)
    {
        throw std::out_of_range("Index out of range");
    }
    return this->elem + n;
}

template <class T, class A>
inline T &generalVec<T, A>::operator[](size_t n)
{
    return this->elem[n];
}

template <class T, class A>
inline const T &generalVec<T, A>::operator[](size_t n) const
{
    return this->elem[n];
}

template <class T, class A>
inline generalVec<T, A> &generalVec<T, A>::operator=(const generalVec &rhs)
{
    if (this == &rhs)
        return *this;

    generalVec<T, A> temp(rhs);
    std::swap(*this, temp);
    return *this;
}

template <class T, class A>
inline generalVec<T, A> &generalVec<T, A>::operator=(generalVec &&rhs)
{
    if (this == &rhs)
        return *this;

    this->~generalVec();
    this->vecBase<T, std::allocator<T>>::operator=(std::move(rhs));
    return *this;
}

#endif // MY_GENERAL_VEC_HPP
