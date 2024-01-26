// REFERENCE IS ANTHONY WILLIAMS' C++ CONCURRENCY (2nd, up to C++17) TEXT
#include <thread>
#include <iostream>
#include <string.h>

class background_task
{
public:
	// callable object (a class here) that overloads ()
	void operator()() const
	{
		do_something();
		do_something_else();
	}
};

background_task f; // class as the callable type
// f copied into storage bellonging to new thread of exectuion we call my_thread
// and then invoked. We need the copy behavior here to act as that of the original
// or may get unexpected behavior.
std::thread my_thread(f);

// When passing a function object to the thread constructor, avoid **C++'s most vexing parse**!!
// If you pass a temp rather than named variable, the syntax can be the same as that of a function declaration
// So then compiler interprets as such rather than object defn
std::thread my_thread(background_task()); // becomes function declaration that aims to return std::thread

// declares a my_thread function taking in a single param (of type pointer-to-function-taking-no-params-returning-background_task-object) and return
//  a std::thread object rather than launching a new thread!

std::thread my_thread((background_task()));
std::thread my_thread{background_task()};

// this avoids this error by naming function object in either of these two ways.
//  extra () in first prevents interpretation as a function declaration, allowing my_thread
//  to be declared as a variable of type std::thread. Seconds uses the new unfirom init syntax to declare variable

// Another way to avoid this is by lambda expression.

std::thread my_thread([]
					  {
	do_something();
	do_something_else(); });

// NOTE once youve spawned the thread you need to decide whether to wait for it to finish witha join
// or leave it to run on its own by detaching it. If you dont decide before std::thread object is destroyed
// then program is terminated (std::thread calls std::terminate() by its destructor); thus need to know state even with exceptions

// If you dont wait for thread to finish, need to ensure data it touches is valid until thread done with it else its accessing object after its been destroyed
// see when thread func holds ptrs or references to local variables and thread hasnt finished execution when function exits

struct func
{
	int &i;
	func(int &i_) : i(i_) {}
	void operator()()
	{
		for (unsigned j = 0; j < 1'000'000'000; ++j)
		{
			do_something(i); // potential access to dangling ref
		}
	}
};

// main thread comes in here to construct my_func with reference to some_local_state
void oops()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func); // main thread starts new thread called my_thread which calls func::operator() which refers to some_local_state
	// << doesnt wait for thread to finish >>
	my_thread.detach(); // explicitly saying i will not wait for thread
						// main thread detaches its spawn, destroys some_local_state and ecists oops
}
// other thread may still be running the func::operator() call and do_something that refers to some_local_state which has been destroyed => UNDEFINED

// A way around this is to make th ehtread function self-contained and copy in data to thread rather than sharing it; if you really dont want to use join
// you have to look out for access to local variables of the object in that function unless its guaranteed to terminate before function exit

// EXCEPTION HANDLING WITH C++ STL THREADS
/*
	We need to ensure that we've called join() or detach() before satd::thread object is destroyed. If we detaching, we can usually call detach() immediately after
	the thread has been started so this isnt a problem. BUT if you want to wait for it to wrap up then you need to be strategic as to where join() will be placed -- as it may be skipped during exceptions!
*/

void f()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	try
	{
		do_something_in_current_thread();
	}
	catch (...)
	{
		t.join();
		throw;
	}
	t.join();
}
// all exist paths are covered in join(); try/catch blocks is verbose
// so need to ensure we scoped it correctly with minimal code

// USING RAII to wait for a thread to complete
// aka use join in the destructor
class thread_guard
{
	std::thread &t;

public:
	explicit thread_guard(std::thread &t_) : t(t_) {}
	// Without explicit, implicit conversion is allowed from std::thread to thread_guard (undefined):
	// std::thread myThread(someFunction);
	// thread_guard guard = myThread; // Implicit conversion (without explicit)

	~thread_guard()
	{
		// join() can be called only once for a given thread of execution,
		// so it would be a mistake to do so if the thread had already been joined.
		if (t.joinable())
			t.join();
	}
	// disable copy and assignment constructor that would be auto provided by
	// compiler as doing so may create copy/assign object which might outlive scope of thread it was
	// joining
	thread_guard(thread_guard const &) = delete;
	thread_guard &operator=(thread_guard const &) = delete;
};

void f()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	do_something_in_current_thread();
} // now some thread reached end of execution so g is detroyed first
  // and the thread is join'd in the destructor; this also happens if the function exists because
  // do_something_in_current_thread throws an exception

// dont need to wait for thread to finish? just use detach because it breaks the
// association with the std::thread object and ensures std::terminate() wont be called
// when std::std object is destroyed, even though the thread is still running in the background
// this hands over management of that thread to the Runtime Library
// these detached threads are called daemon threads after UNIX concept of daemon process runnign in background w/o explicit UI

std::thread t(do_background_work);
t.detach();
assert(!t.joinable()); // std::thread object no longer associated with actual thread of execution

// to detach thread from std::thread object there must be a thread to detach: you cant detach() on a std::thread obj
// with no associtaed thread of execution

void edit_doc(std::string const &filename)
{
	open_doc_and_display_gui(filename);
	while (!done_editing())
	{
		user_command cmd = get_user_input();

		if (cmd.type == open_new_doc)
		{
			// opening new doc requires starting  a new thread
			std::string const new_name = get_filename_from_user();
			std::thread t(edit_doc, new_name);
			// we dont care on waiting for threads to finish as we work
			// on unrelated documents (each thread handling a new one in this design)
			t.detach();
		}
		else
		{
			process_user_input(cmd);
		}
	}
}

// Passing args to a thread function

void f(int i, std::string const &s);
std::thread t(f, 3, "hello");

// new thread of execution associated with t, which calls f(3,"hello")
// note that even though f takes std::string as the second param, the string
// literal is passed as a char const* and converted to std::string only in
// the conext of the new thread

void f(int i, std::string const &s);
void oops(int some_param)
{
	char buffer[1024];
	// OOPS: ptr to *local* variable buffer passed to new thread and
	// significant chance that oops will exit before buffer has been
	// converted to a std::string on the new thread==>undefined
	// as buffer may be destroyed before complete!!
	sprintf(buffer, "%i", some_param);
	std::thread t(f, 3, buffer); // buffer's char * implicitly converted to std::string
	t.detach();
}

void not_oops(int some_param)
{
	char buffer[1024];
	sprintf(buffer, "%i", some_param);
	std::thread t(f, 3, std::string(buffer)); // now avoid using dangling ptr by casting before passing
	t.detach();
}

void update_data_for_widget(widget_id w, widget_data &data);
void oops_again(widget_id w)
{
	widget_data data;
	// std::thread contructor isn't aware that data is passed by ref and blindly copies the values
	//  as rvalues in order to work with move-only types and thus tries to call
	//  update_data_for_widget with an rvalue==>fails to compile because you cant pass
	//  rvalue to a function expecting non-const ref
	std::thread t(update_data_for_widget, w, data);
	display_status();
	t.join();
	process_widget_data(data);
}

// fix is to force a pass by reference than a temp copy of data

std::thread t(update_data_for_widget, w, std::ref(data));

// You can also bind addresses

class X
{
public:
	void do_lengthy_work(int i);
};
X my_x;
std::thread t(&X::do_lengthy_work, &my_x, 2);
// This invokes my_x.do_lengthy_work(2) on new thread as address of my_x is
// supplied as obj ptr. third argument is first arg of member function

// std::unique_ptr provided auto mem mgmt for dyn allocated objects. Only one instance
// can point to given obj at a time and when instance destryoed, the pointed-to obj is dleteted
// move constructor and move assignment operator allow ownership to be transferred
// around between std::unique_ptr instances -- leaves the source obj with a nullptr

struct big_object
{
	char *z; // Pointer to char (C-style string)
	int i;

	// Constructor to initialize members
	big_object() : z(nullptr), i(0)
	{
		// Allocate memory for the default string "default"
		z = new char[8]; // recall null terminated c-string
		strcpy(z, "default");
	}

	// Destructor to free allocated memory
	~big_object()
	{
		delete[] z;
	}

	// Public function to prepare data
	void prepare_data(int i_)
	{
		i += i_;
	}

	// Copy constructor to perform a deep copy
	big_object(const big_object &other) : z(nullptr), i(other.i)
	{
		z = new char[strlen(other.z) + 1];
		strcpy(z, other.z);
	}

	// Copy assignment operator to perform a deep copy
	big_object &operator=(const big_object &other)
	{
		if (this != &other)
		{
			delete[] z;

			z = new char[strlen(other.z) + 1];
			strcpy(z, other.z);

			i = other.i;
		}
		return *this;
	}

	// Move constructor
	big_object(big_object &&other) noexcept : z(other.z), i(other.i)
	{
		other.z = nullptr;
		other.i = 0;
	}

	// Move assignment operator
	big_object &operator=(big_object &&other) noexcept
	{
		if (this != &other)
		{
			delete[] z;

			z = other.z;
			i = other.i;

			other.z = nullptr;
			other.i = 0;
		}
		return *this;
	}
};

// std::move to transfer ownership of a dynamic object into a thread

void process_big_object(std::unique_ptr<big_object>){/*something*/};
std::unique_ptr<big_object> p(new big_object);
p->prepare_data(42);
std::thread t{process_big_object, std::move(p)};
// By specifying std::move(p) in the std::thread constructor, the ownership of big_object is transferred first into internal storage
// for the newly created thread and then into process_big_object.

// Trasnfger thread ownership

void foo();
void bar();
std::thread t1(foo); // new thread for t1; foo is a temp object
// Now transfer thread over to t2; t1 no longer has associated thread of execution
//  explicit call of move since t1 is a named object
std::thread t2 = std::move(t1);
// bar is seen as a temp object -- moving from temps is automatic and implicit
// so will not require move semantics
t1 = std::thread(bar);
// t3 is default constructed which means its created without any assoc thrd of exec
std::thread t3;
// ownership transfer to t3 with explicit call of move() since t2 is named object
t3 = std::move(t2);
// transfer back to where t1 started; but in this case t1 had an associated thread
t1 = std::move(t3); // this line terminates program as t1 holding bar info; std::terminate() invoked
// thus we must explicitly wait for a thread to complete or detach it before destruction,
// and the same applies to assignment: can't just drop a thread by assigning a new
// value to the std::thread object that manages it

// transfer ownership out of a function using move support semantics
std::thread f()
{
	void foo();
	// The implicit move constructor of std::thread supports
	// transferring ownership of the thread object from the
	// local scope of the f() function to the calling code,
	// so return invokes the move const of std thread
	// to transfer to calling obj (callee)
	return std::thread(foo);
}
std::thread g()
{
	void bar(int);
	std::thread t(bar, 42) return t; // move semantics to calling object from local
}

// Likewise, if ownership should be transferred into a function,
//  it can accept an instance of std::thread by value as one of the params
void f(std::thread t);
void g()
{
	void some_function();
	f(std::thread(some_function));
	std::thread t(some_function);
	f(std::move(t));
}