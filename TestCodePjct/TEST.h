#pragma once
#include <errno.h>

template <class X>X func(X x, X bottom, X top);
template <class X>X func(X* x, X bottom, X top);
template <class X>X GetRandom(X min, X max);
void GetTimes();
void WriteTime();
bool CheckError(errno_t, char*);

//���ݒT��
void test09();
//�o�u��
void test08();
//thread�̃e�X�g
void test07();
//test05�𐻍쒆�̂ɍ��킹���R�[�h
void test06();
//��Ԑ��ڂ̃v���g�^�C�v
void test05();
void test04();
void test03();
//65536byte�̃����_���o�C�i���t�@�C���̏����o��
void test02();
void test01();
void test00();