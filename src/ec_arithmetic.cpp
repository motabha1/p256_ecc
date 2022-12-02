/**
 * @file ec_arithmetic.cpp
 * @author Rachit Parikh (prachit@me.iitr.ac.in)
 * @brief 
 * @version 0.1
 * @date 2022-12-03
 * 
 */

#include "ec_arithmetic.h"

bool pt_equal(curve_pt p, curve_pt q){
    return is_equal(p.X, q.X) && is_equal(p.Y, q.Y);
}

curve_pt add(curve_pt p, curve_pt q)
{
    int_256 lambda;
    curve_pt res;
    if (is_equal(p.X, INF) && is_equal(p.Y, INF))
    {
        return q;
    }
    else if (is_equal(q.X, INF) && is_equal(q.Y, INF))
    {
        return p;
    }
    else if (is_equal(p.X, q.X) && is_equal(p.Y, q.Y))
    {
        lambda = mul(p.X, p.X);
        int_256 tmp = add(lambda, add(lambda, lambda));
        int_256 inv = add(p.Y, p.Y);
        tmp = add(tmp, A);
        lambda = mul(tmp, exp(inv, P256_2));
    }
    else
    {
        lambda = sub(q.Y, p.Y);
        int_256 inv = sub(q.X, p.X);
        lambda = mul(lambda, exp(inv, P256_2));
    }
    res.X = sub(mul(lambda, lambda), p.X);
    res.X = sub(res.X, q.X);
    res.Y = sub(p.X, res.X);
    res.Y = mul(res.Y, lambda);
    res.Y = sub(res.Y, p.Y);
    return res;
}

curve_pt scalar_mul(curve_pt p, int_256 alpha)
{
    curve_pt q = p, res;
    res.X = INF;
    res.Y = INF;
    for (int i = 0; i < 8; i++)
    {
        ull g = alpha.x[i];
        int itr = 32;
        while (itr--)
        {
            if (g & 1)
                res = add(res, q);
            g = g >> 1;
            q = add(q, q);
        }
    }
    return res;
}