#include "TEST01.h"
#include <stdio.h>
#include <time.h>//time
#include <stdlib.h>//string
#include <iostream>//cout

using namespace std;

int GetRandom(int min, int max){
  static int flag;
  if(flag==0) {//[]
    srand((unsigned int)time(NULL));
    flag = 1;
  }
  return min+(int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

/*
Mode  動作                    ファイルがあるとき         ファイルがないとき
"r"   読み出し専用            正常                       エラー（NULL返却）
"r+"  読み込みと書き込み      正常                       エラー（NULL返却）
"w"   書き込み専用            サイズを0にする（上書き）	 新規作成
"w+"  書き込みと読み込み      サイズを0にする（上書き）	 新規作成
"a"   追加書き込み専用        最後に追加する             新規作成
"a+"  読み込みと追加書き込み  最後に追加する           	 新規作成

0x21(0x20) ~ 0x7E(0x7F) ACKIIのテキスト表示される文字

int fseek( FILE *stream, long offset, int whence );
バイナリモードとテキストモードで処理が違うらしいので注意
int wherece に入る基準位置
SEEK_SET	ファイルの始め
SEEK_CUR	その時点のファイル位置表示子の値
SEEK_END	ファイルの終わり

ファイル位置表示子の値を返す、そのまま fseek() に入れることができる。
long ftell( FILE *stream );

int i;
fwrite(&i, sizeof(int), 1, fp);
fread(&i, sizeof(int), 1, fp);
fprintf_s(fp, "output test\n");
*/

void test04(char *c){

  FILE *fs;
  fopen_s(&fs, c, "w");

  fprintf_s(fs, "test04\n");

  fclose(fs);

}
void test03(){

  cout << "test" << endl;

  //ここで試しにエディタを作る。
  //テキストの抽出や書き込み、暗号化等等
}
void test02(){
  FILE *fs;
  fopen_s(&fs, "TestFile//map.dat", "wb");

  char c = 0;
  for(int i=0; i<256*256; i++){
    c = (char)GetRandom(0x00, 0xFF);
    fwrite(&c, sizeof(c), 1, fs);
  }
  fclose(fs);

  //65536byteのランダムバイナリファイルの書き出し
}

void test01(){
  FILE *fpa;
  fopen_s(&fpa, "TestFile//String00.txt", "w");
  char c[4];
  //c[0] = 0xFF;
  c[0] = c[1] = c[2] = c[3] = 0;
  fprintf_s(fpa, "%c\n", c[0]);

  fclose(fpa);
}

void test00(){
  FILE* fpa;
  FILE* fpb;
  fopen_s(&fpa, "TestFile//Binary0.txt", "wb");
  fopen_s(&fpb, "TestFile//Binary1.txt", "wb");
  //fprintf_s(fpa, "%d", ftell(fpa));//どちらも0が出力
  //fprintf_s(fpb, "%d", ftell(fpb));//シーク位置は+1されている。

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

  //fprintf_s(fpa, "%d", ftell(fpa));
  //fprintf_s(fpb, "%d", ftell(fpb));
  //fwriteで動く
  //これでも動いてる
  //最後に出力した位置+1


  fclose(fpa);
  fclose(fpb);
}

void GetTimes(){

  //MicrosoftDNからコピペ

  struct tm newtime;
  __time64_t long_time;

  char am_pm[] = "AM";
  char timebuf[26];

  errno_t err;//エラー

  // Get time as 64-bit integer.
  _time64(&long_time);
  // Convert to local time.
  //err = _localtime64_s(&newtime, &long_time);//タイムゾーン
  if(err = _localtime64_s(&newtime, &long_time)){
    printf("Invalid argument to _localtime64_s.");
    exit(1);
  }

  if(newtime.tm_hour==0)// Set hour to 12 if midnight.
    newtime.tm_hour = 12;
  else{
    if(newtime.tm_hour>12)
      strcpy_s(am_pm, sizeof(am_pm), "PM");// Set up extension.
    else// if(newtime.tm_hour>12){// Convert from 24-hour
      newtime.tm_hour -= 12;// to 12-hour clock.
  }

  //asctime_s() Convert to an ASCII representation. 
  //err = asctime_s(timebuf, 26, &newtime);
  if(err = asctime_s(timebuf, 26, &newtime)){
    printf("Invalid argument to asctime_s.");
    exit(1);
  }

  printf("timebuf[%.19s] am_pm[%s]\n", timebuf, am_pm);
}
