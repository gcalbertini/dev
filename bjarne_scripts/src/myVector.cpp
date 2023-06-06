#include "myVector.hpp"

namespace myNaive
{
    babyVector::babyVector(std::size_t s) : sz{s}, elem{new double[s]}, space{s}
    {
        // constructor to alloc doubles; let elem point to them and store s in sz the current size
        // allows us to write babyVector v(3) with three elements set to default value of 0.0
        for (std::size_t i = 0; i < s; ++i)
            elem[i] = 0.0; // init elements with 0.0 by default
    }                      // default constructor

    babyVector::babyVector(std::initializer_list<double> lst) : sz{lst.size()}, elem{new double[sz]}, space{lst.size()}
    {

        // included size_t as there was implicit conversion of lst.size() which is of type size_t (e.g. a 64-bit unsigned integer) to an int
        // (e.g. 32-bit signed) and with {} gives a narrowing error
        // Now allows us to write babyVector v {1.0, 2.0, 3.0} instead of
        // babyVector v(3); then v[0] = 1.0, etc
        std::copy(lst.begin(), lst.end(), elem);

    } // list-init constructor; elem will be taken care of by destructor

    babyVector::babyVector(const babyVector &rhs) : sz{rhs.sz}, elem{new double[rhs.sz]}, space{rhs.space}
    {

        std::copy(rhs.elem, rhs.elem + rhs.sz, elem); // capture the (CONTIGUOUS) heap mem thereby including relevant member params
                                                      //  and avoids the ugly 'for (std::size_t i = 0; i < sz; ++i) elem[i] = rhs.elem[i];'
                                                      // (deep) copy constructor for originally uninit object
    }                                                 // elem will be taken care of by destructor

    babyVector::babyVector(babyVector &&rhs) : sz{rhs.sz}, elem{rhs.elem}, space{rhs.space}
    { // move constructor
        rhs.sz = 0;
        rhs.elem = nullptr;
    } // now rhs is the empty vector after being moved

    babyVector &babyVector::operator=(const babyVector &rhs)
    {                     // copy assignment; like copy constructor but we must deal with old elements
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

                double *p = new double[rhs.sz];            // allocate new space
                std::copy(rhs.elem, rhs.elem + rhs.sz, p); // copy elements
                delete[] elem;                             // dealloc old space
                space = sz = rhs.sz;                       // set new size and elements
                elem = p;
            }
        }

        return *this;
    } // p will be taken care of by destructor

    babyVector &babyVector::operator=(babyVector &&rhs)
    {                    // move assignment
        delete[] elem;   // dealloc old space
        elem = rhs.elem; // copy rhs elem and sz
        sz = rhs.sz;
        rhs.elem = nullptr; // make rhs empty vector
        rhs.sz = 0;
        return *this;
    }
    void babyVector::resize(int newsize)
    {
        reserve(newsize);
        for (int i = sz; i < newsize; ++i)
            elem[i] = 0.0; // init new elements
        sz = newsize;
    }
    void babyVector::reserve(int newalloc)
    {
        if (newalloc <= space)
            return;                       // never decrease allocation
        double *p = new double[newalloc]; // alloc new space
        for (std::size_t i = 0; i < sz; ++i)
            p[i] = elem[i];
        delete[] elem; // dealloc old space and reset
        elem = p;
        space = newalloc;
    } // elem will be cleaned up by destructor
    void babyVector::push_back(const double &d)
    {
        if (space == 0)
            reserve(8);       // start with space for 8 elements
        else if (sz == space) // get more space, usually done by doubling it
            reserve(2 * space); 
        elem[sz] = d;
        ++sz;
    }
}
