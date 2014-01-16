#include <iostream>
#include <time.h>
#include "TEST00.h"

using namespace std;

TEST00::TEST00(){}
TEST00::~TEST00(){}
void TEST00::now_days(){
  cout<<"日付を表示します。"<<endl;

  time_t now = time(NULL);
  struct tm *pnow = localtime_s(pnow, &now);//エラー
  printf("%2d:%2d:%2d \n", pnow->tm_year+1900, pnow->tm_mon+1, pnow->tm_mday);

  cout
    <<pnow->tm_year+1900<<"年"
    <<pnow->tm_mon+1<<"月"
    <<pnow->tm_mday<<"日"<<endl;

}
void TEST00::now_times(){
  cout<<"\n現在時刻を表示します。"<<endl;

  time_t now = time(NULL);
  struct tm *pnow = localtime_s(pnow, &now);//同じくエラー
  printf("%d:%d:%d\n", pnow->tm_hour, pnow->tm_min, pnow->tm_sec);

  cout
    <<pnow->tm_hour<<"時"
    <<pnow->tm_min<<"分"
    <<pnow->tm_sec<<"秒"<<endl;

}
