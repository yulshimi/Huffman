#include "HCTree.h"
#include "HCNode.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;
int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    return 0;
  }
  char myChar;
  string number;
  int m_int;
  vector<int> freqVector;
  ifstream in_stream;
  ofstream out_stream;
  in_stream.open(argv[1]);
  out_stream.open(argv[2]);
  for(int i=0; i < 256; ++i)
  {
    getline(in_stream, number);
    m_int = atoi(number.c_str());
    freqVector.push_back(m_int);
  } 
  HCTree myTree;
  myTree.build(freqVector);
  while(!in_stream.eof())
  {
    myChar = (unsigned char)myTree.decode(in_stream);
    if(myChar == 0)
    {
      break;
    }
    out_stream << myChar;    
  }
  in_stream.close();
  out_stream.close();
  return 0;
}
