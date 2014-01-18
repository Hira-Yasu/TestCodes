#include "TEST01.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int GetRandom(int min, int max){
  static int flag;
  if(flag==0) {
    srand((unsigned int)time(NULL));
    flag = 1;
  }
  return min+(int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

TEST01::TEST01(){}
TEST01::~TEST01(){}
void TEST01::OutputFile(){
  /*
  Mode  動作                    ファイルがあるとき         ファイルがないとき
  "r"   読み出し専用            正常                       エラー（NULL返却）
  "r+"  読み込みと書き込み      正常                       エラー（NULL返却）
  "w"   書き込み専用            サイズを0にする（上書き）	 新規作成
  "w+"  書き込みと読み込み      サイズを0にする（上書き）	 新規作成
  "a"   追加書き込み専用        最後に追加する             新規作成
  "a+"  読み込みと追加書き込み  最後に追加する           	 新規作成

  0x21(0x20) ~ 0x7E(0x7F) ACKIIのテキスト表示される文字
  int fseek(
  FILE *stream,
  long offset,
  int whence
  );
  int wherece に入る基準位置
  SEEK_SET	ファイルの始め
  SEEK_CUR	その時点のファイル位置表示子の値
  SEEK_END	ファイルの終わり

  ファイル位置表示子の値を返す、そのまま fseek() に入れることができる。
  long ftell(
  FILE *stream
  );
  int i = 0xFFFFEEEE;
  fwrite(&i, sizeof(int), 1, fp);
  fread(&i, sizeof(int), 1, fp);
  fprintf_s(fp, "output test\n");
  */
  FILE* fpa;
  FILE* fpb;
  fopen_s(&fpa, "TestFile//Binary0.txt", "wb");
  fopen_s(&fpb, "TestFile//Binary1.txt", "wb");
  char c = 0;
  int j;
  for(int i = 0; i<256; i++){
    j = GetRandom(0x00, 0xFF);
    c = (char)j;
    fwrite(&c, 1, 1, fpa);
    fwrite(&j, 1, 1, fpb);
    //全く同じファイルが作られる。

    //fprintf(fpb, "%x", j);
    //jに入力されている数字はcのバイナリと一致する、いあｍのところ反転はしていない
    //が、調べたところprintfでは無効文字は出力されない（書き込みすらされない）
  }
  fprintf_s(fpa, "%d", ftell(fpa));
  fprintf_s(fpb, "%d", ftell(fpb));

  fclose(fpa);
  fclose(fpb);

}
void TEST01::InputFile(){}
