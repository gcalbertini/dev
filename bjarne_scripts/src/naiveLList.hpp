
#ifndef NAIVE_LL_HPP
#define NAIVE_LL_HPP

#ifndef UTILS_HPP
#define UTILS_HPP
#include "utils.hpp"
#endif // UTILS_HPP

class Link
{
    // Naive implementation of doubly-linked list
public:
    std::string value;
    Link(const std::string &v, Link *p = nullptr, Link *s = nullptr) : value{v}, prev{p}, succ{s} {}

    Link *insert(Link *);                        // insert n before this object
    Link *add(Link *);                           // insert n after this object
    Link *erase();                         // remove object from list
    Link *find(const std::string &);             // find s in list
    const Link *find(const std::string &) const; // find s in const list
    Link *advance(int);                          // move n position in list

    Link *getNext() const { return succ; }
    Link *getPrevious() const { return prev; }

private:
    Link *succ;
    Link *prev;
};

void print_all(Link *);

#endif // NAIVE_LL_HPP