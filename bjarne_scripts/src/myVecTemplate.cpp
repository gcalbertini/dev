#include "myVecTemplate.hpp"

namespace myNaive
{
    template <class T, typename A>
    babyVectorTemplate<T, A>::babyVectorTemplate(std::size_t s, T def = T()) : sz{s}, elem{new T[s]}, space{s} // careful here, [] may not be overloaded for all types -- might need more methods for type deduction!
    {
        for (std::size_t i = 0; i < s; ++i)
            elem[i] = T();
    }

    template <class T, typename A>
    babyVectorTemplate<T, A>::babyVectorTemplate(std::initializer_list<T> lst) : sz{lst.size()}, elem{new T[sz]}, space{lst.size()}
    {
        std::copy(lst.begin(), lst.end(), elem);
    }

    template <class T, typename A>
    babyVectorTemplate<T, A>::babyVectorTemplate(const babyVectorTemplate &rhs) : sz{rhs.sz}, elem{new T[rhs.sz]}, space{rhs.space}
    {
        std::copy(rhs.elem, rhs.elem + rhs.sz, elem);
    }

    template <class T, typename A>
    babyVectorTemplate<T, A>::babyVectorTemplate(babyVectorTemplate &&rhs) : sz{rhs.sz}, elem{rhs.elem}, space{rhs.space}
    {
        rhs.sz = 0;
        rhs.elem = nullptr;
    }

    template <class T, typename A>
    babyVectorTemplate<T, A> &babyVectorTemplate<T, A>::operator=(babyVectorTemplate &&rhs)
    {
        delete[] elem;   // dealloc old space
        elem = rhs.elem; // copy rhs elem and sz
        sz = rhs.sz;
        rhs.elem = nullptr; // make rhs empty vector
        rhs.sz = 0;
        return *this;
    }

    template <class T, typename A>
    babyVectorTemplate<T, A> &babyVectorTemplate<T, A>::operator=(const babyVectorTemplate &rhs)
    {
        if (this != &rhs) // check for self-assignment
        {
            if (rhs.sz <= space)
            {
                for (int i = 0; i < rhs.sz; ++i)
                    elem[i] = rhs.elem[i]; // copy elements
                sz = rhs.sz;
            }
            else
            {

                T *p = new T[rhs.sz];                      // allocate new space
                std::copy(rhs.elem, rhs.elem + rhs.sz, p); // copy elements
                delete[] elem;                             // dealloc old space
                space = sz = rhs.sz;                       // set new size and elements
                elem = p;
            }
        }
        return *this;
    }
    template <class T, typename A>
    T &babyVectorTemplate<T, A>::at(int n)
    {
        if (n < 0 || sz <= n) throw out_of_range();
        return elem[n];
    }

    template <class T, typename A>
    const T &babyVectorTemplate<T, A>::at(int n) const
    {
        if (n < 0 || sz <= n) throw out_of_range();
        return elem[n];
    }

    template <class T, typename A>
    void babyVectorTemplate<T, A>::resize(int newsize)
    {
        reserve(newsize);
        for (int i = sz; i < newsize; ++i) std::allocator_traits<A>::construct(alloc, &elem[i], val);
        for (int i = newsize; i < sz; ++i) std::allocator_traits<A>::destroy(alloc, &elem[i]);
        sz = newsize;
    }

    template <class T, class A>
    void babyVectorTemplate<T, A>::reserve(int newalloc)
    {
        // note we cannot use assignment because for types such as string, assignment assumes target area initialized
        if (newalloc <= space)
            return;                      // never decrease allocation
        T *p = alloc.allocate(newalloc); // allocate new space
        for (int i = 0; i < sz; ++i)
            std::allocator_traits<A>::construct(alloc, &p[i], elem[i]); // copy
        for (int i = 0; i < sz; ++i)
            std::allocator_traits<A>::destroy(alloc, &elem[i]); // destroy
        alloc.deallocate(elem, space);                          // dealloc old space
        elem = p;
        space = newalloc;
    }

    template <class T, typename A>
    void babyVectorTemplate<T, A>::push_back(const T & v)
    {
        if (space == 0)
            reserve(8);       // start with space for 8 elements
        else if (sz == space) // get more space, usually done by doubling it
            reserve(2 * space); 
        elem[sz] = v;
        ++sz;
    }


};