#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main ()
{
  string file_name = "";
  ifstream in_stream;
  ofstream out_stream;
  out_stream.open("outText.txt");
  in_stream.open("myText.txt");
  char myChar;
  getline(in_stream, file_name);
  cout << file_name << endl;
  while(!in_stream.eof())
  {
    in_stream >> myChar;
    cout << myChar << endl;
  }
  in_stream.close();
  out_stream.close();
  return 0;
}
