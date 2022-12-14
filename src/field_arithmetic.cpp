#include <iostream>
#include "utility.h"
#include "field_arithmetic.h"

using namespace std;

int_256 s1, s2, s3, s4, s5, s6, s7, s8, s9;

/**
 * @brief This is a utility function that simply prints the 
 * 256-bit number in base 2^32 as a collection of 8 numbers
 * @param gg 
 * @param str 
 */
void show_number(int_256 gg, const char *str)
{
    cout << str;
    for (int i = 0; i < gg.size; i++)
        cout << gg.x[i] << " ";
    cout << endl;
}

/**
 * @brief This utility function simply converts a 256-bit number to a 512-bit number
 * 
 * @param a 
 * @return int_512 
 */
int_512 convert256(int_256 a)
{
    int_512 ans;
    int i = 0;
    while (i < a.size)
    {
        ans.x[i] = a.x[i];
        i++;
    }
    while (i < ans.size)
    {
        ans.x[i] = 0;
        i++;
    }
    return ans;
}

/**
 * @brief This initialization function is necessary for performing fast-reduction
 * Since the prime can be written as sum or difference of powers of 2, we have a reduction
 * algorithm available that works fast for machines with wordsize 32
 * @param a 
 */
void initialize(int_512 a)
{
    s1 = {a.x[0], a.x[1], a.x[2], a.x[3], a.x[4], a.x[5], a.x[6], a.x[7]};
    s2 = {0, 0, 0, a.x[11], a.x[12], a.x[13], a.x[14], a.x[15]};
    s3 = {0, 0, 0, a.x[12], a.x[13], a.x[14], a.x[15], 0};
    s4 = {a.x[8], a.x[9], a.x[10], 0, 0, 0, a.x[14], a.x[15]};
    s5 = {a.x[9], a.x[10], a.x[11], a.x[13], a.x[14], a.x[15], a.x[13], a.x[8]};
    s6 = {a.x[11], a.x[12], a.x[13], 0, 0, 0, a.x[8], a.x[10]};
    s7 = {a.x[12], a.x[13], a.x[14], a.x[15], 0, 0, a.x[9], a.x[11]};
    s8 = {a.x[13], a.x[14], a.x[15], a.x[8], a.x[9], a.x[10], 0, a.x[12]};
    s9 = {a.x[14], a.x[15], 0, a.x[9], a.x[10], a.x[11], 0, a.x[13]};
}

/**
 * @brief Utility function for subtraction
 * 
 * @param a 
 * @return int_256 
 */
int_256 twos_complement(int_256 a)
{
    return int_add(ONE, flip_bits(a));
}

/**
 * @brief This is field addition in F_p where p = P256
 * @param a 
 * @param b 
 * @return int_256 
 */
int_256 add(int_256 a, int_256 b)
{
    int_256 c = int_add(a, b);
    if (is_greater(c, P256))
    {
        return sub(c, P256);
    }
    return c;
}

/**
 * @brief This is simple addition of two 256-bit integers
 * 
 * @param a 
 * @param b 
 * @return int_256 
 */
int_256 int_add(int_256 a, int_256 b)
{
    ull c = 0;
    int sz = a.size;
    int_256 res;
    memset(res.x, 0, sizeof(res.x));
    for (int i = 0; i < sz; i++)
    {
        ull tmp = a.x[i] + b.x[i] + c;
        c = (tmp >= TWO_32);
        res.x[i] = tmp & 0xffffffff;
    }
    return res;
}

/**
 * @brief a - b is simply computed as a + (~b)
 * where ~b is the two's complement of b
 * If the answer turns out to be negative i.e. a < b, we add P256 to the result
 * @param a 
 * @param b 
 * @return int_256 
 */
int_256 sub(int_256 a, int_256 b)
{
    int_256 c = int_add(a, twos_complement(b));
    if (c.x[9] & 0x8000000)
    {
        c = int_add(c, P256);
    }
    return c;
}

/**
 * @brief School book multiplication
 * This is O(n^2) time algorithm and in the future versions it will be updated to Karatsuba
 * @param a 
 * @param b 
 * @return int_256 
 */
int_256 mul(int_256 a, int_256 b)
{
    int_512 res;
    memset(res.x, 0, sizeof(res.x));
    for (int i = 0; i < 8; i++)
    {
        ull u = 0, v = 0;
        for (int j = 0; j < 8; j++)
        {
            ull tmp = res.x[i + j] + a.x[i] * b.x[j] + u;
            u = tmp >> 32;
            v = tmp & 0xffffffff;
            res.x[i + j] = v;
        }
        res.x[i + 8] = u;
    }
    return mod(res);
}

/**
 * @brief For a given 256 bit integer exponent t and base a
 * this function computes a^t mod p256
 * This is simple binary exponentation
 * @param a 
 * @param t 
 * @return int_256 
 */
int_256 exp(int_256 a, int_256 t)
{
    int_256 res = ONE, tmp = a;
    for (int i = 0; i < 8; i++)
    {
        ull g = t.x[i];
        int itr = 32;
        while (itr--)
        {
            if (g & 1)
                res = mul(res, tmp);
            g = g >> 1;
            tmp = mul(tmp, tmp);
        }
    }
    return res;
}

/**
 * @brief Fast reduction algorithm
 * More about this algorithm can be found at:
 * "Darrel Hankerson, Alfred J. Menezes, and Scott Vanstone. 2010. 
 * Guide to Elliptic Curve Cryptography (1st. ed.). Springer Publishing Company, Incorporated"
 * @param a 
 * @return int_256 
 */
int_256 mod(int_512 a)
{
    initialize(a);
    int_256 tmp = add(s1, s2);
    tmp = add(s3, add(tmp, s2));
    tmp = add(s4, add(tmp, s3));
    tmp = add(tmp, s5);
    tmp = sub(sub(tmp, s6), s7);
    tmp = sub(sub(tmp, s8), s9);
    return tmp;
}
