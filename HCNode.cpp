//Name: Phillip Jo, San Kang
//Date: 02/22/2017/Wed
//Overview: This is to make priority_queue pop an item which has a lower frequency first
//Assignment#: PA3

#include "HCNode.h"
using namespace std;

bool HCNode::operator<(const HCNode& other)
{
  if(count != other.count)
  {
    return count > other.count;
  }
  return symbol < other.symbol;
}
