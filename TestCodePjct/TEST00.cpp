#include <iostream>
#include <time.h>
#include "TEST00.h"

using namespace std;

TEST00::TEST00(){}
TEST00::~TEST00(){}
void TEST00::now_days(){
  cout<<"���t��\�����܂��B"<<endl;

  time_t now = time(NULL);
  struct tm *pnow = localtime_s(pnow, &now);//�G���[
  printf("%2d:%2d:%2d \n", pnow->tm_year+1900, pnow->tm_mon+1, pnow->tm_mday);

  cout
    <<pnow->tm_year+1900<<"�N"
    <<pnow->tm_mon+1<<"��"
    <<pnow->tm_mday<<"��"<<endl;

}
void TEST00::now_times(){
  cout<<"\n���ݎ�����\�����܂��B"<<endl;

  time_t now = time(NULL);
  struct tm *pnow = localtime_s(pnow, &now);//�������G���[
  printf("%d:%d:%d\n", pnow->tm_hour, pnow->tm_min, pnow->tm_sec);

  cout
    <<pnow->tm_hour<<"��"
    <<pnow->tm_min<<"��"
    <<pnow->tm_sec<<"�b"<<endl;

}
