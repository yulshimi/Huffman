//Name: Phillip Jo, San Kang
//Date: 02/22/2017/Wed
//Overview: This is the header file of "BitInputStream.cpp"
//Assignment#: PA3

#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H
#include <fstream>
#include <iostream>
using namespace std;
class BitInputStream
{
public:
  BitInputStream(istream& is);
  void fill();
  int readBit();
private:
  char buf;
  int nbits;
  istream& in;
};
#endif
