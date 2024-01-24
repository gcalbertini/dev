#include <thread>
#include <iostream>

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

// When passing a function object to the thread constructor, avoid C++'s most vexing parse!!
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

std::thread my_thread([] {
	do_something();
	do_something_else();
});

// NOTE once youve spawned the thread you need to decide whether to wait for it to finish witha join
// or leave it to run on its own by detaching it. If you dont decide before std::thread object is destroyed
// then program is terminated (std::thread calls std::terminate() by its destructor); thus need to know state even with exceptions

// If you dont wait for thread to finish, need to ensure data it touches is valid until thread done with it else its accessing object after its been destroyed
// see when thread func holds ptrs or references to local variables and thread hasnt finished execution when function exits

struct func{
	int &i;
	func(int& i) : i(i_){}
	void operator()(){
		for (unsigned j=0; j<1'000'000; ++j){
			do_something(i);
		}
	}
};

void oops(){
	int some_local_state = 0;
	func my_func(some_local_state);
	my_thread.detach();
}