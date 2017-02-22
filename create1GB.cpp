#include <fstream>
using namespace std;
int main ()
{
  ofstream out_stream;
  out_stream.open("1GB.txt");
  for(int i=0; i < 100000; ++i)
  {
    out_stream << "aannnnmmmr";
  }
  return 0;
}
