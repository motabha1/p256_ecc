#include "../src/utility.h"
#include "../src/field_arithmetic.h"
#include "field_arithmetic_test.h"
#include "../src/ec_arithmetic.h"

#include <iostream>
using namespace std;

void test_add(int_256 a, int_256 b, int_256 c)
{
	show_number(a, "a = ");
	show_number(b, "b = ");
	int_256 d = int_add(a, b);
	show_number(d, "d = ");
	show_number(c, "c = ");
	if (is_equal(c, d))
	{
		cout << "ADDITION TEST SUCCESS!\n";
	}
	else
	{
		cout << "ADDITION TEST FAILED!\n";
	}
}

void test_sub(int_256 a, int_256 b, int_256 c)
{
	int_256 d = sub(a, b);
	if (is_equal(c, d))
	{
		cout << "SUBTRACTION TEST SUCCESS!\n";
	}
	else
	{
		cout << "SUBTRACTION TEST FAILED!\n";
	}
}

void test_mul(int_256 a, int_256 b, int_256 c)
{
	int_256 d = mul(a, b);
	if (is_equal(c, d))
	{
		cout << "MULTIPLICATION TEST SUCCESS!\n";
	}
	else
	{
		cout << "MULTIPLICATION TEST FAILED!\n";
	}
}

void test_inverse(int_256 a)
{
	int_256 aa = exp(a, P256_2);
	if (is_equal(mul(aa, a), ONE))
	{
		cout << "INVERSE TEST SUCCESS!\n";
	}
	else
	{
		int_256 gg = mul(aa, a);
		for (int i = 0; i < gg.size; i++)
			cout << gg.x[i] << " ";
		cout << "INVERSE TEST FAILED!\n";
	}
}

void test_field()
{
	int_256 alice_priv = {{ 3344903487,2575534979,1018405731,2333777693,
						   3045066606,3196691482,3057193541,1394370893}, 10};

	int_256 bob_priv = {{ 2429904316, 2913800441, 229002501, 2924250216,
 					765149036, 2687782714, 809747822, 1323719054}, 10};

	curve_pt G;
	G.X = Gx; G.Y = Gy;

	curve_pt alice_pub = scalar_mul(G, alice_priv);
	curve_pt bob_pub = scalar_mul(G, bob_priv);

	curve_pt aaa = scalar_mul(alice_pub, bob_priv);
	curve_pt bbb = scalar_mul(bob_pub, alice_priv);

	if(pt_equal(aaa, bbb)){
		cout << "KEYS ARE SUCCESSFULLY EXCHANGED!!\n";
	}
	else{
		cout << "SAMAJ!\n";
	}
}
