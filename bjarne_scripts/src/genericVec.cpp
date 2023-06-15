#include "genericVec.hpp"

namespace myNaive
{
    template <class T, class A>
    genericVec<T, A>::genericVec(const genericVec &rhs)  : sz{rhs.sz}, elem{new double[rhs.sz]}, space{rhs.space}
    {
        std::uninitialized_copy(this->elem, this->elem + size(), rhs.elem) 
    }

    template <class T, class A>
    void genericVec<T, A>::resize(size_t newsize)
    {
        reserve(newsize);
        for (size_t i = sz; i < newsize; ++i)
            elem[i] = T(); // init new elements of default type
        this->sz = newsize;
    }

    template <class T, class A>
    void genericVec<T, A>::reserve(size_t newalloc)
    {
        if (newalloc <= space)
            return;                                                                 // never decrease allocation
        baseVec<T, A> b{this->alloc, newalloc};                                     // explicit this to override base member and use derived member; alloc new space
        std::uninitialized_copy(this->elem, this->elem + size(), b.elem)            // copy; will correctly handle throws from copy constructor and internal loop
            for (size_t i = 0; i < size(); ++i) this->alloc.destroy(this->elem[i]); // destroy old
        std::swap<baseVec<T, A>>(*this, b);                                         // swap representations
    }

    template <class T, class A>
    void genericVec<T, A>::push_back(const T &val)
    {
        if (space == 0)
            reserve(8); // start space for 8 elem
        else if (sz == space)
            reserve(2 * space);                     // get more space
        this->alloc.construct(this->elem[sz], val); // add val at the end
        ++sz;                                       // increase size
    }
}