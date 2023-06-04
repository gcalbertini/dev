#include <iostream>
#include <vector>
using namespace std;

struct X {
    int val;
    void out(const string& s, int nv) { cerr << this << "->" << s << ":" << val << "(" << nv << ")\n"; }

    X() {
        out("X()", 0);
        val = 0;
    }  // default constructor

    X(int v) {
        val = v;
        out("X(int)", v);
    }

    X(const X& x) {
        val = x.val;
        out("X(X&)", x.val);
    }  // copy constructor

    X& operator=(const X& rhs) {
        out("X::operator()", rhs.val);
        val = rhs.val;
        return *this;
    }  // copy assignment

    ~X() { out("~X()", 0); }  // destructor
};

X glob(2);  // a global variable
X copy(X a) { return a; }
X copy2(X a) {
    X aa = a;
    return aa;
}
X& ref_to(X& a) { return a; }
X* make(int i) {
    X a(i);
    return new X(a);
}
struct XX {
    X a;
    X b;
};

//https://stackoverflow.com/questions/50083082/crtexe-c-issue-about-debugging-c-c-files-in-vscode
int main(int argc, char** argv) {

    X loc{4};         // local variable;
    X loc2{loc};      // copy construction
    loc = X{5};       // copy assignment
    loc2 = copy(loc); // call by value and return
    loc2 = copy2(loc);
    X loc3{6};
    X& r = ref_to(loc);
    delete make(7);
    delete make(8);
    std::vector<X> v(4);
    XX loc4;
    X* p = new X{9};
    delete p;
    X* pp = new X[5];
    delete[] pp;
    
    return 0;
}
