#include <iostream>
#include <exception>
#include <typeinfo>
#include <string>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;
//struct A
//{
//	char a;				// 32 : 1 byte		64 : 1 byte	
//	char b[2];			// 32 : 2 bytes		64 : 2 bytes
//	long c;				// 32 : 5 bytes		64 : 5 bytes
//	char* p;			// 32 : 4 bytes		64 : 8 bytes
//};
class Sample
{
private:
	int *ptr;
public:
	Sample(int i)
	{
		cout << "creating Sample" << endl;
		ptr = new int(i);
	}
	~Sample()
	{
		cout << "deleting Sample" << endl;
		delete ptr;
	}
	void PrintVal()
	{
		cout << "The value is " << *ptr;
	}
};
void SomeFunc(Sample x)
{
	cout << "In SomeFunc" << endl;
}
int main() 
{
	Sample s1(10);
	SomeFunc(s1);
	s1.PrintVal();
	return 0;
}
/////////////////////////////////////////////////////////
//
//class A
//{
//public:
//	//A() { cout << "creating A" << endl; }
//	void func() { cout<< "using func in A class" << endl; }
//};
//
//class B : public A
//{
//public:
//	//B() { cout << "creating B" << endl; }
//
//	using A::func;
//	void func(int a);
//};
//
//class base
//{
//public:
//     virtual void baseFun() { cout<<"from base"<< endl; }
//};
//class deri: public base
//{
//public:
//     virtual void baseFun() { cout<< "from derived"<< endl; }
//};
//void SomeFunc(base* baseObj)
//{
//     baseObj->baseFun();
//}
//int main()
//{
//     base baseObject;
//     SomeFunc(&baseObject);
//     deri deriObject;
//     SomeFunc(&deriObject);
//	 getchar();
//	 return 0;
//}
//
//
