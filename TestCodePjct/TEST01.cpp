#include "TEST01.h"
#include <stdio.h>

TEST01::TEST01(){}
TEST01::~TEST01(){}

  void TEST01::OutputFile(){
    FILE* fp;
    fopen_s(&fp, "FILE.file", "w");
    fprintf_s(fp, "テキスト\n");
    fclose(fp);
  }
  void TEST01::InputFile(){
  }