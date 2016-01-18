#include <iostream>
#include <thread>
#include <string>
#include <mutex>
using namespace std;

void function_1()
{
	cout << "Beauty is only skin-deep" << endl;
}

class Fctor {
public: 
	void operator()(string& msg) 
	{
		cout << "From t: " << msg << endl;
		msg = "modified by t1";
	}
};

class stack
{
	int* _data;  // int array
	std::mutex _mu;
public: 
	void pop(); // pops off the item on top of the stack 
	int& top();

}

int main()
{
	string s = "Original message";
	thread t1((Fctor()), ref(s));  // s no longer belonged to the main thread

	//cout << "From main: " << s << endl;

	//cout << std::thread::hardware_concurrency() << endl;

	t1.join();
	
	ostream output;
	output << "Hey" << endl;

	getchar();
	return 0;

}