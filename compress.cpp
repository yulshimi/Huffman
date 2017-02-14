#include "HCTree.h"
#include "HCNode.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    return 0;
  }
  HCTree myTree;
  vector<int> freqVector;
  for(int i=0; i < 256; ++i)
  {
    freqVector.push_back(0);
  }
  ifstream in_stream;
  ofstream out_stream;
  in_stream.open(argv[1]);
  if(in_stream.fail())
  {
    cout << "File open fail......" << endl;
    return 0;
  }
  char myChar;
  if(!(in_stream.peek() == ifstream::traits_type::eof()))
  {
    while(1)
    {
      myChar = (unsigned char)in_stream.get();
      if(in_stream.eof())
      {
        break;
      }
      ++freqVector[(unsigned int)myChar];
    }
  }
  myTree.build(freqVector);
  in_stream.close();
  in_stream.open(argv[1]);
  out_stream.open(argv[2]);
  for(int i=0; i < 256; ++i)
  {
    out_stream << freqVector[i] << endl;
  }
  if(!(in_stream.peek() == ifstream::traits_type::eof()))
  {
    while(1)
    {
      myChar = (unsigned char)in_stream.get();
      if(in_stream.eof())
      {
        break;
      }
      myTree.encode(myChar, out_stream);
    }
  }
  in_stream.close();
  out_stream.close();  
  return 0;
}
