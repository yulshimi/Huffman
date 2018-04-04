#include <iostream>
#include <fstream>
using namespace std;
int main (int argc, char* argv[])
{
  ifstream in_stream;
  in_stream.open(argv[1]);
  int nextByte = 0;
  unsigned char nextChar;
  while((nextByte = in_stream.get()) != EOF)
  {
    nextChar = (unsigned char)nextByte;
    cout << nextChar << endl;
    cout << nextByte << endl;
  }
  return 0;
}
