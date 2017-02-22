#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H
#include <fstream>
#include <iostream>
using namespace std;
class BitOutputStream
{
public:
  BitOutputStream(ostream& os);
  void flush();
  void writeBit(unsigned int bit);
  unsigned char getBuf() const;
private:
  unsigned char buf;
  int nbits;
  ostream& out;
};
#endif 
