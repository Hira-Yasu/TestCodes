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
  Mode  ����                    �t�@�C��������Ƃ�         �t�@�C�����Ȃ��Ƃ�
  "r"   �ǂݏo����p            ����                       �G���[�iNULL�ԋp�j
  "r+"  �ǂݍ��݂Ə�������      ����                       �G���[�iNULL�ԋp�j
  "w"   �������ݐ�p            �T�C�Y��0�ɂ���i�㏑���j	 �V�K�쐬
  "w+"  �������݂Ɠǂݍ���      �T�C�Y��0�ɂ���i�㏑���j	 �V�K�쐬
  "a"   �ǉ��������ݐ�p        �Ō�ɒǉ�����             �V�K�쐬
  "a+"  �ǂݍ��݂ƒǉ���������  �Ō�ɒǉ�����           	 �V�K�쐬

  0x21(0x20) ~ 0x7E(0x7F) ACKII�̃e�L�X�g�\������镶��
  int fseek(
  FILE *stream,
  long offset,
  int whence
  );
  int wherece �ɓ����ʒu
  SEEK_SET	�t�@�C���̎n��
  SEEK_CUR	���̎��_�̃t�@�C���ʒu�\���q�̒l
  SEEK_END	�t�@�C���̏I���

  �t�@�C���ʒu�\���q�̒l��Ԃ��A���̂܂� fseek() �ɓ���邱�Ƃ��ł���B
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
    //�S�������t�@�C���������B

    //fprintf(fpb, "%x", j);
    //j�ɓ��͂���Ă��鐔����c�̃o�C�i���ƈ�v����A�������̂Ƃ��딽�]�͂��Ă��Ȃ�
    //���A���ׂ��Ƃ���printf�ł͖��������͏o�͂���Ȃ��i�������݂��炳��Ȃ��j
  }
  fprintf_s(fpa, "%d", ftell(fpa));
  fprintf_s(fpb, "%d", ftell(fpb));

  fclose(fpa);
  fclose(fpb);

}
void TEST01::InputFile(){}
