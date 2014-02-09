#pragma once
#include <errno.h>

template <class X>X func(X x, X bottom, X top);
template <class X>X func(X* x, X bottom, X top);
template <class X>X GetRandom(X min, X max);
void GetTimes();
void WriteTime();
bool CheckError(errno_t, char*);

void test05();
void test04();
void test03();
void test02();
void test01();
void test00();