#include <iostream>
#include <thread>

void hello(){
	std::cout << "Hello but concurrent!!\n";
}
int main(){
	std::thread t (hello); // spawn a new thread t with hello as initial function; the other in main
	t.join(); // main thread could possibly continue execution and end program before other done with hello so join them back
}