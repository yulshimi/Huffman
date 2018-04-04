//Name: Phillip Jo, San Kang
//Date: 02/22/2017/Wed
//Overview: This is to uncompress a file using bitwise I/O
//Assignment#: PA3

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
  unsigned char myChar;
  int totalBits;
  int totalBytes= 0;
  int currentBytes = 0;
  ifstream in_stream;
  ofstream out_stream;
  in_stream.open(argv[1], ios::binary);
  out_stream.open(argv[2], ios::binary);
  BitInputStream bitIn(in_stream);
  in_stream >> totalBytes;
  if(totalBytes == 0)
  {
    return 0;
  }
  in_stream >> totalBits;
  char g_char = in_stream.get();
  HCTree myTree;
  myTree.build(totalBits, bitIn);
  myTree.writeSymbol(myTree.getRoot(), in_stream);
  myTree.treeTest(myTree.getRoot());
  bitIn.fill();
  while(totalBytes != currentBytes)
  {
    myChar = (unsigned char)myTree.decode(bitIn);
    out_stream.put(myChar);
    ++currentBytes;    
  }
  in_stream.close();
  out_stream.close();
  return 0;
}
