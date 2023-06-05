#include <iostream>
#include <vector>
using namespace std;

struct X
{
    int val;
    void out(const string &s, int nv) { cerr << this << "->" << s << ":" << val << "(" << nv << ")\n"; }

    X()
    {
        out("X()", 0);
        val = 0;
    } // default constructor

    X(int v)
    {
        val = v;
        out("X(int)", v);
    }

    X(const X &x)
    {
        val = x.val;
        out("X(X&)", x.val);
    } // copy constructor

    X &operator=(const X &rhs)
    {
        out("X::operator()", rhs.val);
        val = rhs.val;
        return *this;
    } // copy assignment

    ~X() { out("~X()", 0); } // destructor
};

X glob(2); // a global variable
X copy(X a) { return a; }
X copy2(X a)
{
    X aa = a;
    return aa;
}
X &ref_to(X &a) { return a; }
X *make(int i)
{
    X a(i);
    return new X(a);
}
struct XX
{
    X a;
    X b;
};

int main(int argc, char **argv)
{
    // A copy constructor is used to initialize a *previously uninitialized object* from some other object's data: A(const A& rhs) : data_(rhs.data_) {}
    // An assignment operator is used to *replace the data of a previously initialized object* with some other object's data: A& operator=(const A& rhs) {data_ = rhs.data_; return *this;}

    X loc{4}; // local variable;
    cout << "\n";
    X loc2{loc}; // copy construction
    cout << "\n";
    loc = X{5}; // copy assignment; destructor of X{5} object then called as it was copied over
    cout << "\n";
    loc2 = copy(loc); // first: a copy of loc passed to copy(loc') and makes implied call to copy constructor so that (uninitialized) loc'<--copy of loc;
                      // next: copy routine is called; local object a is created by IMPLIED calling copy instructor so (uninitialized) a<--loc' and returns initialized a to become object for copy(loc');
                      // next: copy assignment called by (previously) initialized loc2; finally: destructor for a called and then destructor for copy(a')
    cout << "\n";
    loc2 = copy2(loc); // first: a copy of loc passed to copy2(loc') and loc' makes implied call to copy constructor so that loc'<--copy of loc;
                       // next: copy2 routine is called; local object aa is created (instantaneously uninitialized) and EXPLICITLY calls copy instructor so aa<--a and returns aa;
                       // next: copy assignment called by (previously) initalized loc2 ; finally: destructor for a called then that for copy2(a), which is explicitly named aa
    cout << "\n";
    X loc3{6}; // another local variable
    cout << "\n";
    X &r = ref_to(loc); // simply creates reference to loc and return, a variable in local scope (of main routine)
    cout << "\n";
    delete make(7); // first call make, which creates a function-local object called a of type X; next: a new object type pointer-to-X is
                    // allocated memory on the HEAP and is then uninitialized until it calls copy constructor so that new X = a and returns this for make(7) pointer to object X; next: delete which prompts
                    // destructor of non-dynamically allocated a FIRST and then calls destructor of dynamically allocated pointer make(8) LAST
    cout << "\n";
    delete make(8); // see above
    cout << "\n";
    std::vector<X> v(4); // want a vector object v holding x4 objects of type X --> get garbage_num(0) printed as val is not init for each (until right after call to out) and 0 passed to nv
                         // do not be fooled -- garbage_num can also be 0 at that point in time in the register
    cout << "\n";
    XX loc4; // struct XX called and holds x2 struct objects of type X which are get garbage_num(0) as each default init (val set to 0 after call to out)
    cout << "\n";
    X *p = new X{9}; // first create object X{9} and put pointer to it directly on heap
    cout << "\n";
    delete p; // then call destructor for the pointer
    cout << "\n";
    X *pp = new X[5]; // similar but now pointer to array of default constructed objects of type X
    cout << "\n";
    delete[] pp;

    return 0;
}
