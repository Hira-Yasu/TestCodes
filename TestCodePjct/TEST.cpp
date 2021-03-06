#include "TEST.h"
#include <stdio.h>
#include <time.h>//time
#include <stdlib.h>//string
#include <iostream>//cout
#include <thread>

using namespace std;

//呼び出し元で返り値を代入する形式
template <class X>X func(X x, X bottom, X top){
  return max(bottom, min(top, x));
}
//ポインタに直接値を代入する形式（オーバーロード
template <class X>X func(X* x, X bottom, X top){
  *x = max(bottom, min(top, *x));
}

template <class X>X GetRandom(X min, X max){
  static bool flag = false;
  if(!flag) {
    srand((unsigned int)time(NULL));
    flag = true;
  }
  return (X)min + (X)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}
void GetTimes(){
  //MicrosoftDNからコピペ
  struct tm newtime;
  __time64_t long_time;
  char am_pm[] = "AM";
  char timebuf[26];
  errno_t err;
  _time64(&long_time);
  if(err = _localtime64_s(&newtime, &long_time)){
    printf("Invalid argument to _localtime64_s.");
    exit(1);
  }
  if(newtime.tm_hour == 0)
    newtime.tm_hour = 12;
  else{
    if(newtime.tm_hour > 12)
      strcpy_s(am_pm, sizeof(am_pm), "PM");
    else{
      newtime.tm_hour -= 12;
    }
  }
  if(err = asctime_s(timebuf, 26, &newtime)){
    printf("Invalid argument to asctime_s.");
    exit(1);
  }
  printf("timebuf[%.19s] am_pm[%s]\n", timebuf, am_pm);
}
void WriteTime(char* c){
  struct tm newtime;
  __time64_t long_time;
  char am_pm[] = "AM";
  char timebuf[26];
  //errno_t err;
  _time64(&long_time);
  _localtime64_s(&newtime, &long_time);
  if(newtime.tm_hour == 0)
    newtime.tm_hour = 12;
  else{
    if(newtime.tm_hour > 12)
      strcpy_s(am_pm, sizeof(am_pm), "PM");
    else
      newtime.tm_hour -= 12;
  }
  asctime_s(timebuf, 26, &newtime);
  FILE *fp;
  fopen_s(&fp, c, "r+");
  fprintf_s(fp, "%.19s %s\n", timebuf, am_pm);
  fclose(fp);
}
bool CheckError(errno_t err, char* c){
  if(NULL == err)return NULL;
  //else
  cout << "Error" << endl;
  cout << "ファイル\" " << c << " \"が存在しません。" << endl;
  cout << "ErrorCode " << err << endl;

  FILE* fs;
  char* err_c = "error_log.txt";
  fopen_s(&fs, err_c, "r+");//r+専用、エラーが出たらwで生成してwhileループで戻す？
  fseek(fs, 0, SEEK_SET);//ファイルの最初にセット、新しいものほど上に

  fprintf_s(fs, "%s\n", c);

  fclose(fs);

  return true;
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

long offset に入る基準位置
//ファイル位置表示子の値を返す、そのまま fseek() に入れることができる。
long ftell( FILE *stream );

int wherece に入る基準位置
SEEK_SET	ファイルの始め
SEEK_CUR	その時点のファイル位置表示子の値
SEEK_END	ファイルの終わり

int i;
fwrite(&i, sizeof(int), 1, fp);
fread(&i, sizeof(int), 1, fp);
fprintf_s(fp, "output test\n");
*/

void test09(){
  const int max = 64;
  bool a[max];
  int c = 0;
  for(int i = 0; i < max; i++){
    a[i] = (bool)(GetRandom(0, 1) % 2);
    cout << a[i] << flush;
  }
  cout << " Initial" << endl;

  for(int i = 0; i < max - 1; i++)
  {
    if(0 == a[i]){
      for(int j = i; j < 64; j++){
        if(1 == a[j]){
          a[i] = a[i] ^ true;
          a[j] = a[j] ^ true;
          for(int j = 0; j < max; j++){ cout << a[j] << flush; }
          //最後に入れ替えた個数(i)が要素数になる
          //cは入れ替えた回数
          cout << ' ' << i << ' ' << ++c << endl;
          break;
        }

      }
    }
  }
  cout << "バブル sort end" << endl;
}

void test08(){
  const int max = 64;
  bool a[max];
  int c = 0;
  int z = 0;
  for(int i = 0; i < max; i++){
    a[i] = (bool)(GetRandom(0, 1) % 2);
    cout << a[i] << flush;
  }
  cout << " Initial" << endl;


  for(int i = 0; i < max; i++)  //max-1でも計算可能、だが要素数が変わる
  {
    if(1 == a[i])z++;//要素数
    else
    {//if(0 == a[i]){
      for(int j = max - 1; j > i; j--)
      {
        if(1 == a[j])
        {

          z++;//要素数
          c++;//計算回数

          a[i] = a[i] ^ true;
          a[j] = a[j] ^ true;

          for(int j = 0; j < max; j++){ cout << a[j] << flush; }
          cout << ' ' << endl;

          break;
        }
      }
    }
  }
  cout << "member=" << z << ' ' << "count=" << c << " 交互バブル " << endl;
  cout << "sort end" << endl;

}

void threadA(){
  for(int i = 0; i < 4; i++){
    cout << "A" << endl;
  }
}
void threadB(){
  for(int i = 0; i < 4; i++){
    cout << "B" << endl;
  }
}
void test07(){
  thread th1(threadA);
  thread th2(threadB);
  th1.join();
  th2.join();

  unsigned int i = thread::hardware_concurrency();
  cout << i << endl;

}
void test06(){
  bool fade = false;
  bool a, b;
  a = true;
  b = false;
  int fadecount = 0;

  for(int i = 0; i < 12; i++){//ループ


    if(a != b){
      cout << "[a!b]" << flush;
      if(!fade){
        fade = true;
      }
    }
    else cout << "[a=b]" << flush;

    //fadeがtrueになった時点でUpdateは実行させないためUpdateはここに置く
    if(!fade){
      cout << "[Update]" << flush;
    }
    else cout << "[fade]" << flush;

    cout << "[Disp]" << endl;

    if(fade){//フェード処理
      fadecount++;
      if(fadecount == 4)a = b;
      else if(fadecount == 8){
        fade = false;
        fadecount = 0;
      }
    }
  }
}
void test05(){
  bool fade = false;
  bool a, b;
  a = true;
  b = false;
  int fadecount = 0;

  for(int i = 0; i < 12; i++){

    if(a != b){//^
      //cout << "[a!b]" << flush;
      if(!fade)fade = true;
    }
    //else cout << "[a=b]" << flush;

    if(!fade){
      cout << "[Update]" << flush;
    }

    cout << "[Disp]" << endl;

    if(fade){
      cout << "[fade]" << flush;
      fadecount++;

      //フェードアウトが完了した時点でシステムを推移させる
      if(fadecount == 4)a = b;

      //フェードインが完了したらフェードフラグを解除
      else if(fadecount == 8){
        fade = false;
        fadecount = 0;
      }
    }
  }
}
void test04(){
  FILE *fs;
  char* c = "TestFile//test04.txt";
  errno_t err = fopen_s(&fs, c, "w");//<-
  if(CheckError(err, c))return;
  //エラーチェック、
  //r フォルダが存在しないとき、ファイルが存在しないときエラー
  //↑のこの2つのエラーが同じなんだよなぁ……
  //w フォルダが存在しないときのみエラー、ファイルはなくても生成する
  //a フォルダが存在しないときのみエラー、ファイルはなくても生成する
  fprintf_s(fs, "test05\n");//rの時は無視
  fclose(fs);
}
void test03(){
  cout << "test03" << endl;
  char m1[3][4] = {"abc", "def", "ghi"};
  printf("%s %s %s\n", m1[0], m1[1], m1[2]);
  printf("%d\n", sizeof(m1));
  char* m2 = "abcdefghijkl";
  printf("%s\n", m2);
  printf("%d\n", sizeof(m2));//char*が指すアドレス4byte
}
void test02(){
  FILE *fs;
  fopen_s(&fs, "TestFile//test02.txt", "wb");
  char c = 0;
  for(int i = 0; i < 256 * 256; i++){
    c = GetRandom(0x00, 0xFF);
    fwrite(&c, sizeof(c), 1, fs);
  }
  fclose(fs);
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
  for(int i = 0; i < 256; i++){
    j = GetRandom(0x00, 0xFF);
    c = (char)j;
    fwrite(&c, 1, 1, fpa);
    fwrite(&j, 1, 1, fpb);
    //全く同じファイルが作られる。

    //fprintf(fpb, "%x", j);
    //jに入力されている数字はcのバイナリと一致する、いあｍのところ反転はしていない
    //が、調べたところprintfでは無効文字は出力されない（書き込みすらされない）
  }
  fclose(fpa);
  fclose(fpb);
}