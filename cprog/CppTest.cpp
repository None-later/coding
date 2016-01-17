#include<iostream>

using namespace std;

class A
{
private:
  int* ptr;
public:
  A() { ptr = new int; }
  A(const A& rhs)
  {
    ptr = new int;
    *ptr = *(rhs.ptr);
  }
  A& operator=(const A& rhs)
  {
     ptr = new int;
     *ptr = *rhs.ptr;
  }
  void printInfo()
  {
    cout << "address : " << ptr << " " << "val : " << *ptr << endl;
  }
};

int main(void)
{
  A obj1;
  A obj2;
  obj2 = obj1;
  obj1.printInfo();
  obj2.printInfo();
  return 0;
}


