
#include<iostream>
#include<future>
#include<type_traits>

using namespace std;
using namespace std::chrono_literals;


template<typename Func, typename ...Args>
auto my_async(Func f, Args ... args) {
	
	packaged_task<decltype(f(args...))(Args...)> pt(f);
	future<decltype(f(args...))> fv = pt.get_future();

	std::jthread jt(std::move(pt), args...);
	jt.detach();//allow no block, asynchronous
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

	/*std::future<int> f1 = async(counter,1000);
	std::future<int> f2 = async(counter,1000);
	cout << f1.get()<<std::endl;
	cout << f2.get()<<std::endl;*/

	std::future<int> f3 = my_async(counter,1000);
	std::future<int> f4 = my_async(counter,1000);

	cout << f3.get() << std::endl;
	cout << f4.get() << std::endl;
	return 0;
}