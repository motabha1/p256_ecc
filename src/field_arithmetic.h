#pragma once


extern int_256 s1, s2, s3, s4, s5, s6, s7, s8, s9;

int_256 twos_complement(int_256 a);

int_256 add(int_256 a, int_256 b);

int_256 sub(int_256 a, int_256 b);

int_256 mul(int_256 a, int_256 b);

int_256 exp(int_256 a, int_256 t);

int_256 mod(int_512 a);

int_256 int_add(int_256 a, int_256 b);

void initialize(int_512 a);
void show_number(int_256 gg, const char* str);
int_512 convert256(int_256 a);
