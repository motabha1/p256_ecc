#include "utility.h"

int_256 ONE = {
    {0x00000001, 0x00000000, 0x00000000, 0x00000000,
     0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    10};

int_256 TWO = {
    {0x00000002, 0x00000000, 0x00000000, 0x00000000,
     0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    10};

int_256 THREE = {
    {0x00000003, 0x00000000, 0x00000000, 0x00000000,
     0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    10};

int_256 P256 = {
    {0xffffffff, 0xffffffff, 0xffffffff, 0x00000000,
     0x00000000, 0x00000000, 0x00000001, 0xffffffff, 0x00000000, 0x00000000},
    10};

int_256 P256_2 = {
    {0xfffffffd, 0xffffffff, 0xffffffff, 0x00000000,
     0x00000000, 0x00000000, 0x00000001, 0xffffffff, 0x00000000, 0x00000000},
    10};

int_256 A = {
    {0xfffffffc, 0xffffffff, 0xffffffff, 0x00000000,
     0x00000000, 0x00000000, 0x00000001, 0xffffffff, 0x00000000, 0x00000000},
    10};

int_256 INF = {
    {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
     0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff},
    10};

int_256 Gx = {
    {0xD898C296, 0xF4A13945, 0x2DEB33A0, 0x77037D81,
     0x63A440F2, 0xF8BCE6E5, 0xE12C4247, 0x6B17D1F2, 0x00000000, 0x00000000},
    10};

int_256 Gy = {
    {0x37BF51F5, 0xCBB64068, 0x6B315ECE, 0x2BCE3357,
     0x7C0F9E16, 0x8EE7EB4A, 0xFE1A7F9B, 0x4FE342E2, 0x00000000, 0x00000000},
    10};

int_256 PROD = {
    {0xface98be, 0xf713ebbb, 0xc6a08622, 0xd183e554,
     0x513a6b2b, 0x33565064, 0x6dd3c719, 0x823cd15f},
    10};

int_256 PROD2 = {
    {0x21c3ed91, 0xbedd2cfc, 0xa412b5e0,
     0x498a9022, 0x979369fe, 0x82149139, 0x50f47bad, 0x55df5d58},
    10};

int_256 flip_bits(int_256 a)
{
    int sz = a.size;
    for (int i = 0; i < sz; i++)
    {
        a.x[i] = a.x[i] ^ FLIP;
    }
    return a;
}

bool is_greater(int_256 a, int_256 b)
{
    int sz = a.size;
    for (int i = sz - 1; i >= 0; i--)
    {
        if (a.x[i] - b.x[i] > 0)
            return true;
        else if (a.x[i] - b.x[i] < 0)
            return false;
        else
            continue;
    }
    return true;
}

bool is_equal(int_256 a, int_256 b)
{
    int sz = a.size;
    for (int i = sz - 1; i >= 0; i--)
    {
        if (a.x[i] != b.x[i])
            return false;
    }
    return true;
}

int get_ith_bit(int a, int i)
{
    return (a >> i) & 1;
}
