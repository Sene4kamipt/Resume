#include <limits.h>
#include <stdint.h>

#ifndef ITYPE
#define ITYPE uint64_t
#endif


extern void sum(ITYPE first, ITYPE second, ITYPE *res, int *CF){
	ITYPE answer = 0;
	uint_fast8_t overflow = 0;
	for (uint_fast8_t i = 0; i < CHAR_BIT * sizeof(ITYPE); ++i) {
		uint_fast8_t bit_1 = (first >> i)%2;
		uint_fast8_t bit_2 = (second >> i)%2;
		answer ^= (1ll&(bit_1 ^ bit_2 ^ overflow)) << i;
		overflow = (overflow & bit_1) | (overflow & bit_2) | (bit_1 & bit_2);
	}
	*res = answer;
	*CF = overflow;
}

