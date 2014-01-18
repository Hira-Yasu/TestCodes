#include <iostream>
#include "TEST00.h"
#include "TEST01.h"

using namespace std;

TEST00 *test00;
TEST01 *test01;
void Constructor(){
  test00 = new TEST00;
  test01 = new TEST01;
}
void Destructor(){
  delete test00;
  delete test01;
}

int main() {
  Constructor();
  cout<<"Hello World"<<endl;

  test01->OutputFile();

  cout<<"End Prcs"<<endl;
  getchar();
  Destructor();
  return 0;
}
