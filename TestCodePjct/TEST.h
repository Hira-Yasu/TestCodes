#pragma once
#include <errno.h>

template <class X>X func(X x, X bottom, X top);
template <class X>X func(X* x, X bottom, X top);
template <class X>X GetRandom(X min, X max);
void GetTimes();
void WriteTime();
bool CheckError(errno_t, char*);

//交互探索
void test09();
//バブル
void test08();
//threadのテスト
void test07();
//test05を製作中のに合わせたコード
void test06();
//状態推移のプロトタイプ
void test05();
void test04();
void test03();
//65536byteのランダムバイナリファイルの書き出し
void test02();
void test01();
void test00();