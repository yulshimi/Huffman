#include <fstream>
#include <iostream>
using namespace std;
int main ()
{
  ifstream in_stream;
  in_stream.open("theprince.txt");
  char myChar = in_stream.get();
  cout << myChar;
  for(int i=0; i < 100; ++i)
  {
    myChar = in_stream.get();
    cout << myChar;
  }
  return 0;
}
