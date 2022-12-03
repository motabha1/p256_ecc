#include "./src/ec_arithmetic.h"
#include "./test/field_arithmetic_test.h"
#include <iostream>
using namespace std;

int main() {
	int_256 alice_priv = {{ 3344903487,2575534979,1018405731,2333777693,
						   3045066606,3196691482,3057193541,1394370893}, 10};

	int_256 bob_priv = {{ 2429904316, 2913800441, 229002501, 2924250216,
 					765149036, 2687782714, 809747822, 1323719054}, 10};
					
	test_field(alice_priv, bob_priv);
}
