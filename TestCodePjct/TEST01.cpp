#include "TEST01.h"
#include <stdio.h>

TEST01::TEST01(){
}
TEST01::~TEST01(){
}

void TEST01::OutputFile(){
  FILE* fp;
  fopen_s(&fp, "TestFile//FILE.txt", "w");
  fprintf_s(fp, "output test\n");
  fclose(fp);
}
void TEST01::InputFile(){
}