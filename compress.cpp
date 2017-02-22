//Name: Phillip Jo, San Kang
//Date: 02/22/2017/Wed
//Overview: This is to compress a file using bitwise I/O
//Assignment: PA3

#include "BitOutputStream.h"
#include "HCTree.h"
#include "HCNode.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int main(int argc, char* argv[])
{
  int totalBits = 0;
  int totalBytes = 0;
  int currentBytes = 0;
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
  in_stream.open(argv[1], ios_base::binary);
  if(in_stream.fail())
  {
    cout << "File open fail......" << endl;
    return 0;
  }
  unsigned char myChar;
  if((in_stream.peek() == ifstream::traits_type::eof()))
  {
    out_stream.open(argv[2]);
    out_stream << totalBytes << endl;
    out_stream << totalBits << endl;
    return 0;
  }
  while(1)
  {
    myChar = (unsigned char)in_stream.get();
    if(in_stream.eof())
    {
      break;
    }
    ++totalBytes;
    ++freqVector[(unsigned int)myChar];
  }
  myTree.build(freqVector);
  in_stream.close();
  in_stream.open(argv[1], ios_base::binary);
  out_stream.open(argv[2]);
  BitOutputStream bitOut(out_stream);
  totalBits = myTree.getNumOfBit();
  out_stream << totalBytes << endl;
  out_stream << totalBits << endl;
  HCNode* rootPtr = myTree.getRoot();
  myTree.sendToTheFile(rootPtr, bitOut);
  bitOut.flush();
  myTree.sendSymbolToTheFile(rootPtr, out_stream);
  while(currentBytes != totalBytes)
  {
    myChar = (unsigned char)in_stream.get();
    if(in_stream.eof())
    {
      break;
    }
    myTree.encode(myChar, bitOut);
    ++currentBytes; 
  }
  bitOut.flush();
  in_stream.close();
  out_stream.close();  
  return 0;
}
