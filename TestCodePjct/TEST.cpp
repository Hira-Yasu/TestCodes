#include "TEST.h"
#include <stdio.h>
#include <time.h>//time
#include <stdlib.h>//string
#include <iostream>//cout

using namespace std;

//�Ăяo�����ŕԂ�l��������`��
template <class X>X func(X x, X bottom, X top){
  return max(bottom, min(top, x));
}
//�|�C���^�ɒ��ڒl��������`��
template <class X>X func(X* x, X bottom, X top){
  *x = max(bottom, min(top, *x));
}

template <class X>X GetRandom(X min, X max){
  static bool flag = false;
  if(!flag) {
    srand((unsigned int)time(NULL));
    flag = true;
  }
  return (X)min + (rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}
void GetTimes(){
  //MicrosoftDN����R�s�y
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
  cout << "�t�@�C��\" " << c << " \"�����݂��܂���B" << endl;
  cout << "ErrorCode " << err << endl;

  FILE* fs;
  char* err_c = "error_log.txt";
  fopen_s(&fs, err_c, "r+");//r+��p�A�G���[���o����w�Ő�������while���[�v�Ŗ߂��H
  fseek(fs, 0, SEEK_SET);//�t�@�C���̍ŏ��ɃZ�b�g�A�V�������̂قǏ��

  fprintf_s(fs, "%s\n", c);

  fclose(fs);

  return true;
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

long offset �ɓ����ʒu
//�t�@�C���ʒu�\���q�̒l��Ԃ��A���̂܂� fseek() �ɓ���邱�Ƃ��ł���B
long ftell( FILE *stream );

int wherece �ɓ����ʒu
SEEK_SET	�t�@�C���̎n��
SEEK_CUR	���̎��_�̃t�@�C���ʒu�\���q�̒l
SEEK_END	�t�@�C���̏I���

int i;
fwrite(&i, sizeof(int), 1, fp);
fread(&i, sizeof(int), 1, fp);
fprintf_s(fp, "output test\n");
*/

void test05(){
  bool a, b;
  a = 0; b = 1;

  for(int i = 0; i < 8; i++){
    if(4 <= i)a = b;
    if(a == b){
      cout << "true " << flush;
    }
    else{//if(a != b)
      cout << "false " << flush;
    }
    cout << "Disp" << endl;
  }
}
void test04(){

  FILE *fs;
  char* c = "TestFile//test04.txt";
  errno_t err = fopen_s(&fs, c, "w");//<-

  if(CheckError(err, c))return;
  //�G���[�`�F�b�N�A
  //r �t�H���_�����݂��Ȃ��Ƃ��A�t�@�C�������݂��Ȃ��Ƃ��G���[
  //���̂���2�̃G���[�������Ȃ񂾂�Ȃ��c�c
  //w �t�H���_�����݂��Ȃ��Ƃ��̂݃G���[�A�t�@�C���͂Ȃ��Ă���������
  //a �t�H���_�����݂��Ȃ��Ƃ��̂݃G���[�A�t�@�C���͂Ȃ��Ă���������

  fprintf_s(fs, "test05\n");//r�̎��͖���
  fclose(fs);
}
void test03(){
  cout << "test03" << endl;

  char m1[3][4] = {"abc", "def", "ghi"};
  printf("%s %s %s\n", m1[0], m1[1], m1[2]);
  printf("%d\n", sizeof(m1));
  char* m2 = "abcdefghijkl";
  printf("%s\n", m2);
  printf("%d\n", sizeof(m2));//char*���w���A�h���X4byte
}
void test02(){
  FILE *fs;
  fopen_s(&fs, "TestFile//test02.txt", "wb");
  char c = 0;
  for(int i = 0; i < 256 * 256; i++){//65536byte�̃����_���o�C�i���t�@�C���̏����o��
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
  //fprintf_s(fpa, "%d", ftell(fpa));//�ǂ����0���o��
  //fprintf_s(fpb, "%d", ftell(fpb));//�V�[�N�ʒu��+1����Ă���B
  char c = 0;
  int j;
  for(int i = 0; i < 256; i++){
    j = GetRandom(0x00, 0xFF);
    c = (char)j;
    fwrite(&c, 1, 1, fpa);
    fwrite(&j, 1, 1, fpb);
    //�S�������t�@�C���������B

    //fprintf(fpb, "%x", j);
    //j�ɓ��͂���Ă��鐔����c�̃o�C�i���ƈ�v����A�������̂Ƃ��딽�]�͂��Ă��Ȃ�
    //���A���ׂ��Ƃ���printf�ł͖��������͏o�͂���Ȃ��i�������݂��炳��Ȃ��j
  }
  fclose(fpa);
  fclose(fpb);
}