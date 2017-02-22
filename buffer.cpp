#include <iostream>
#include <fstream>
using namespace std;
int main ()
{
  ofstream out_stream;
  out_stream.open("my_buffer.txt");
  for(int i=0; i < 100; ++i)
  {
    out_stream << i;
    out_stream.flush();
  }
  out_stream.close();
  return 0;
}
