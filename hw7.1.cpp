//Use std:: packaged_task to create your own implementation of async
//Since async's can be called with any number of arguments, it should be variadic. 
// C++ indicates this with an ellipsis “…”. Look online or in our notes and homework for examples of where we've done this
//The return type, it is very messy, so we leverage the fact(mentioned in lecture 1) that C++ lets us leave the return type as 
//auto and it will deduce it from the return statement
//This gives us a signature something like the following
//template<typename Func, typename ...Args>
//auto my_async (Func f, Args ... args ) { /* … */}
//Since we don't do a join when using async (why?), you can call your new threads detach() method to allow it to run independently

#include<iostream>
#include<future>
#include<chrono>

using namespace std;
using namespace std::chrono_literals;

template<typename Func, typename T, typename ...Args>
//auto my_async (Func f, Args && ... args ) { 
//	packaged_task<Func> pt{ f };
//	future<T> fv = pt.get_future();
//	pt(std::forward<Args>(args)...);
//}

auto my_async(Func f, Args ... args) {
	packaged_task<Func> pt{ f };
	future<T> fv = pt.get_future();
	pt(args...);
}


auto sleep = []() {this_thread::sleep_for(5s); };

int main() {
	return 0;

}