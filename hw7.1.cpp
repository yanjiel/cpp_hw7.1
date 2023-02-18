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
#include<type_traits>

using namespace std;
using namespace std::chrono_literals;


//template<typename Func, typename T, typename ...Args>
//auto my_async (Func f, Args && ... args ) { 
//	packaged_task<Func> pt{ f };
//	future<T> fv = pt.get_future();
//	pt(std::forward<Args>(args)...);
//}

template<typename Func, typename ...Args>
auto my_async(Func f, Args ... args) {
	
	packaged_task<decltype(f(args...))(Args...)> pt(f);
	future<decltype(f(args...))> fv = pt.get_future();

	pt(args..);
	//std::jthread jt(std::move(pt), args...);
	return fv;
}


int counter(int i = 0) {
	for (auto cnt = 0; cnt < i; cnt++) { 
		cout << cnt; 
	}
	cout << "done counting" << std::endl;  
	return i; 
};

int main() {

	std::future<int> f1 = async(counter,0);
	std::future<int> f2 = async(counter,0);

	//std::future<int> f3 = my_async(counter);
	//std::future<int> f4 = my_async(counter);

	cout << f1.get()<<std::endl;
	cout << f2.get()<<std::endl;
	/*cout << f3.get() << std::endl;
	cout << f4.get() << std::endl;*/
	return 0;
}