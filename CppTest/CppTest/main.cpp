#include <iostream> 

using namespace std;
//class A 
//{
//public:
//	A() : a(0) { cout << "new A" << endl; };
//	void foo()
//	{
//		cout << a << endl; 
//	}
//private:	
//	int a;
//};
//
//class B : public A
//{
//public:
//	B() : b(0) { cout << "new B" << endl; };
//	void foo()
//	{
//		cout << b << endl; 
//	}
//private:	
//	int b;
//};
#include <string>
#include <set>
class Uncopyable
{
protected:  
     Uncopyable() { }
     ~Uncopyable() { }
private:
     Uncopyable (const Uncopyable&);
     Uncopyable& operator=(const Uncopyable&);  
};

class HomeForSale //: private Uncopyable
{ 
public:
	 //HomeForSale() {};
	 //~HomeForSale() {};
private:
     HomeForSale(const HomeForSale&);   // copy constructor
     HomeForSale& operator=(const HomeForSale&);  // copy assignment
};

class HasPtr
{
	int* ptr;
	int  cnt;
public:
	HasPtr(int* i) : ptr(i), cnt(1) {}
	HasPtr(HasPtr& rhs)
		: ptr(rhs.ptr)
	{
		rhs.cnt++;
		cnt = rhs.cnt;
		cout << "copy: " << cnt << endl;
	}
	void getCnt()
	{
		cout << "get cnt: " << cnt << endl;
	}
};

class Dog
{ 
public:
     virtual Dog* clone()
     {
          return (new Dog(*this));
     }
};

#include "BitOperation.h"
#include <bitset>

int bitSwapRequired(int a, int b) 
{
    int c = a ^ b;
    string binary = bitset<32>(c).to_string();
    int res = 0;
    for (int i = 0; i < binary.size(); ++i)
    {
        if (binary[i] == '1')
            res ++;
    }
    return res;
}

int main () 
{
	//cout << divide(12, -7) << endl;

	cout << bitSwapRequired(14,32) << endl;





	getchar();
	return 0;
}