#include "BitInputStream.h"
BitInputStream::BitInputStream(istream& is) : in(is)
{
  buf = 0;
  nbits = 8;
}

void BitInputStream::fill()
{
  buf = in.get();
  nbits = 0;
}

int BitInputStream::readBit()
{
  if(nbits == 8)
  {
    fill();
  }
  unsigned int tempChar = 0;
  tempChar = (buf >> (7-nbits)) & 1;
  ++nbits;
  return tempChar;
}

