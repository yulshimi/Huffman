//Name: Phillip Jo, San Kang
//Date: 02/22/2017/Wed
//Overview: This is the implementation of "BitOutputStream.h"
//Assignment#: PA3

#include "BitOutputStream.h"
BitOutputStream::BitOutputStream(ostream& os) : out(os), buf(0), nbits(0)
{
}

void BitOutputStream::flush()
{
  out.put(buf);
  out.flush();
  buf = 0;
  nbits = 0;
}

void BitOutputStream::writeBit(unsigned int bit)
{
  if(nbits == 8)
  {
    flush();
  }
  int n = 7 - nbits;
  buf = buf&~(1 << n) | (bit << n);
  ++nbits;
}

unsigned char BitOutputStream::getBuf() const
{
  return buf;
}

