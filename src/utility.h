/**
 * @file utility.h
 * @author Rachit Parikh 
 * @brief 
 * @version 0.1
 * @date 2022-11-19
 * 
 */

#pragma once

#include<vector>
#include<cstring>
#define ull unsigned long long
#define ll long long
#define W 64
#define TWO_32 1ULL<<32
#define FLIP 0xffffffff

typedef struct{
    ull x[10];
    int size = 10;
} int_256;

typedef struct{
    ull x[21];
    int size = 21;
} int_512;

typedef struct{
    int_256 X;
    int_256 Y;
} curve_pt;

extern int_256 ONE; 

extern int_256 TWO;

extern int_256 THREE;

extern int_256 P256; 

extern int_256 P256_2; 

extern int_256 A; 

extern int_256 INF; 

extern int_256 Gx; 

extern int_256 Gy; 

extern int_256 PROD;

extern int_256 PROD2;

int_256 flip_bits(int_256 a);

bool is_greater(int_256 a, int_256 b);

bool is_equal(int_256 a, int_256 b);

int get_ith_bit(int a, int i);
