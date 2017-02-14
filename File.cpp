#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
int main ()
{
  string myString = "My name is Phillip Jo";
  char myChar;
  int myInt = 9999;
  ofstream out_stream;
  out_stream.open("myText.txt");
  out_stream << myString << endl;
  out_stream << myString << endl;
  out_stream << myInt << endl;
  out_stream.close();
  ifstream in_stream;
  in_stream.open("myText.txt");
  for(int i=0; i < 3; ++i)
  {
    getline(in_stream, myString);
  }
  cout << myString << endl;
  string number = "1000";
  int m_int;
  m_int = atoi(number.c_str());
  cout << m_int << endl;
  cout << (char)0 << endl;
  return 0;
}
