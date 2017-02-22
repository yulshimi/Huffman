#include <fstream>
#include <iostream>
using namespace std;
int main ()
{
  ifstream in_stream;
  in_stream.open("empty", ios_base::binary);
  //in_stream.get();
  if((in_stream.peek() == ifstream::traits_type::eof()))
  {
    cout << "Empty File!" << endl;
  }
  return 0;
}
