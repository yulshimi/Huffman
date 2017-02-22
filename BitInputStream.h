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
