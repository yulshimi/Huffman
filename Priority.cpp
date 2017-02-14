#include <iostream>
#include <queue>
#include <vector>
using namespace std;
class myInt
{
public:
  bool operator<(myInt& other)
  {
    if(m_int != other.m_int)
    {
      return m_int > other.m_int;
    }
  }

  int m_int; 
};
class myComp
{
public:
  bool operator()(myInt a, myInt b)
  {
    return a < b;
  }
};

ostream& operator<<(ostream& outs, myInt& my_int)
{
  outs << my_int.m_int << endl;
  return outs;
}
int main ()
{
  priority_queue<int> myQueue;
  priority_queue<int*> ptrQueue;
  myQueue.push(100);
  myQueue.push(999);
  myQueue.push(10);
  myQueue.push(44);
  myQueue.push(444);
  myQueue.push(222);
  myQueue.push(77);
  myQueue.push(991);
  myQueue.push(111);
  myQueue.push(2299);
  int mySize = myQueue.size();
  for(int i=0; i < mySize; ++i)
  {
    cout << myQueue.top() << endl;
    myQueue.pop();
  }
  int* ptrArray[10];
  for(int i=0; i < 10; ++i)
  {
    ptrArray[i] = NULL;
  }
  for(int i=0; i < 10; ++i)
  {
    ptrQueue.push(ptrArray[i]);
  }
  for(int i=0; i < 10; ++i)
  {
    //cout << ptrQueue.top() << endl;
    ptrQueue.pop();
  }
  vector<int> myVector;
  myInt myInt_Array[20];
  priority_queue<myInt, vector<myInt>, myComp> Reverse;
  for(int i=0; i < 20; ++i)
  {
    myInt_Array[i].m_int = i;  
  }
  for(int i=0; i < 20; ++i)
  {
    Reverse.push(myInt_Array[i]);
  }
  for(int i=0; i < 20; ++i)
  {
    myInt temp_int;
    temp_int = Reverse.top();
    cout << temp_int << endl;
    Reverse.pop();
  }
  return 0;
}
