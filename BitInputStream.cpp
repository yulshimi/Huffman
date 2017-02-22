//Name: Phillip Jo, San Kang
//Date: 02/22/2017/Wed
//Overview: This program is the implementation of "BitInputStream.h"
//Assignment#: PA3

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

