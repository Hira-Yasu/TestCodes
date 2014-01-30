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
Mode  ����                    �t�@�C��������Ƃ�         �t�@�C�����Ȃ��Ƃ�
"r"   �ǂݏo����p            ����                       �G���[�iNULL�ԋp�j
"r+"  �ǂݍ��݂Ə�������      ����                       �G���[�iNULL�ԋp�j
"w"   �������ݐ�p            �T�C�Y��0�ɂ���i�㏑���j	 �V�K�쐬
"w+"  �������݂Ɠǂݍ���      �T�C�Y��0�ɂ���i�㏑���j	 �V�K�쐬
"a"   �ǉ��������ݐ�p        �Ō�ɒǉ�����             �V�K�쐬
"a+"  �ǂݍ��݂ƒǉ���������  �Ō�ɒǉ�����           	 �V�K�쐬

0x21(0x20) ~ 0x7E(0x7F) ACKII�̃e�L�X�g�\������镶��

int fseek( FILE *stream, long offset, int whence );
�o�C�i�����[�h�ƃe�L�X�g���[�h�ŏ������Ⴄ�炵���̂Œ���
int wherece �ɓ����ʒu
SEEK_SET	�t�@�C���̎n��
SEEK_CUR	���̎��_�̃t�@�C���ʒu�\���q�̒l
SEEK_END	�t�@�C���̏I���

�t�@�C���ʒu�\���q�̒l��Ԃ��A���̂܂� fseek() �ɓ���邱�Ƃ��ł���B
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

  //�����Ŏ����ɃG�f�B�^�����B
  //�e�L�X�g�̒��o�⏑�����݁A�Í�������
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

  //65536byte�̃����_���o�C�i���t�@�C���̏����o��
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
  //fprintf_s(fpa, "%d", ftell(fpa));//�ǂ����0���o��
  //fprintf_s(fpb, "%d", ftell(fpb));//�V�[�N�ʒu��+1����Ă���B

  char c = 0;
  int j;
  for(int i = 0; i<256; i++){
    j = GetRandom(0x00, 0xFF);
    c = (char)j;
    fwrite(&c, 1, 1, fpa);
    fwrite(&j, 1, 1, fpb);
    //�S�������t�@�C���������B

    //fprintf(fpb, "%x", j);
    //j�ɓ��͂���Ă��鐔����c�̃o�C�i���ƈ�v����A�������̂Ƃ��딽�]�͂��Ă��Ȃ�
    //���A���ׂ��Ƃ���printf�ł͖��������͏o�͂���Ȃ��i�������݂��炳��Ȃ��j
  }

  //fprintf_s(fpa, "%d", ftell(fpa));
  //fprintf_s(fpb, "%d", ftell(fpb));
  //fwrite�œ���
  //����ł������Ă�
  //�Ō�ɏo�͂����ʒu+1


  fclose(fpa);
  fclose(fpb);
}

void GetTimes(){

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
