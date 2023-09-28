/*
 * primesieve
 *
 * Prints out a list of prime numbers using the Sieve of Eratosthenes.
 * 
 * Luke McCarthy 2023-09-28
 */

#include <stdio.h>

#define IS_BIT_SET(arr, bit) \
    (((arr)[(bit) / (sizeof((arr)[0]) * 8)] & (1 << ((bit) % (sizeof((arr)[0]) * 8)))) != 0)

#define BIT_SET(arr, bit)                                                               \
    do {                                                                                \
        (arr)[(bit) / (sizeof((arr)[0]) * 8)] |= 1 << ((bit) % (sizeof((arr)[0]) * 8)); \
    } while (0)

int main()
{
    static unsigned int bits[32 * 1024] = {0};
    const int num_bits = sizeof(bits) * 8;

    printf("prime #0 is 2\n");
    int prime_index = 0;
    for (int i = 0; i < num_bits; i++) {
        if (!IS_BIT_SET(bits, i)) {
            prime_index++;
            int prime = i + i + 3;
            for (int j = i + prime; j < num_bits; j += prime) {
                BIT_SET(bits, j);
            }
            printf("prime #%d is %d\n", prime_index, prime);
        }
    }
    return 0;
}
