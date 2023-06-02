#include "naiveLList.hpp"

void print_all(Link *ptr)
{
    std::cout << "{";
    while (ptr)
    {
        std::cout << ptr->value;
        if (ptr = ptr->getNext())
            std::cout << ",";
    }
    std::cout << "}";
}

Link *Link::insert(Link *n)
{ // insert n before this object; return n. Note this is a ptr that pts to the object for which
    // the member function is called and so doesn't need to be mentioned to access its members

    if (n == nullptr)
        return this;
    if (this == nullptr)
        return n;
    n->succ = this; // this object comes after n
    if (prev)
        prev->succ = n; // aka if (this->prev) this->prev->succ = n;
    n->prev = prev;     // aka n->prev = this->prev; so that the object's predecessor becomes n's predecessor
    prev = n;           // aka  this->prev = n; so that n becomes the object's predecessor
    return n;
}

Link *Link::add(Link *n)
{
    // insert after this object; return n
    if (n == nullptr)
        return this;
    if (this == nullptr)
        return n;
    n->prev = this; // n comes after this object
    if (succ)
        succ->prev = n;
    n->succ = succ;
    succ = n;
    return n;
}

Link *Link::erase()
{
    // erase *n from this list; return n's successor
    if (!this)
        return nullptr;

    if (succ)
        succ->prev = prev;
    if (prev)
        prev->succ = succ;
    return succ;
}

Link *Link::find(const std::string &s)
{
    // Find the object before or after the one containing s; return nullptr if not found
    Link *current = this;
    Link *previous = prev;

    // Find after this object
    while (current)
    {
        if (current->value == s)
            return current;
        current = current->succ;
    }

    // Try to find if it was before this object
    while (previous)
    {
        if (previous->value == s)
            return previous;
        previous = previous->prev;
    }
    return nullptr; // give up
}

const Link *Link::find(const std::string &s) const
{
    // Find the object before or after the one containing s; return nullptr if not found
    // ensure it does not allow modifications to the object it points to (but pointed value not const)
    const Link *current = this;
    const Link *previous = prev;

    // Find after this object
    while (current)
    {
        if (current->value == s)
            return current;
        current = current->succ;
    }

    // Try to find if it was before this object
    while (previous)
    {
        if (previous->value == s)
            return previous;
        previous = previous->prev;
    }

    return nullptr; // give up
}

Link *Link::advance(int n)
{
    // move n positions in list and return nullptr for not found; positive n moves forward and neg backward
    Link *current = this; 
    if (current == nullptr)
        return nullptr;
    if (0 < n)
    {
        while (n--)
        {
            if (current->succ == nullptr)
                return nullptr;
            current = current->succ;
        } // note post-increment which yields the value before the increment as its value
    }
    else if (n < 0)
    {
        while (n++)
        {
            if (current->prev == nullptr)
                return nullptr;
            current = current->prev;
        }
    }
    return current;
}
