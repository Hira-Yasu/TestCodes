#include <iostream>
#include <time.h>
#include "TEST00.h"

using namespace std;

TEST00::TEST00(){}
TEST00::~TEST00(){}
/*
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
*/
void TEST00::CopyCode(){

  //MicrosoftDN����R�s�y

  struct tm newtime;
  __time64_t long_time;

  char am_pm[] = "AM";
  char timebuf[26];

  errno_t err;//�G���[

  // Get time as 64-bit integer.
  _time64(&long_time);
  // Convert to local time.
  //err = _localtime64_s(&newtime, &long_time);//�^�C���]�[��
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