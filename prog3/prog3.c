// Write a function to print the bits in an integer.
// Write a function to count no of 1 bits in an integer.
// Understand little endian and big endian.
// Understand bits in a negative integer.
// Understand bits in a floating point number.
// Understand bints in a negative floating point number.
#include <stdio.h>

void print_bits(unsigned int n) {
    for (int i = 31; i >= 0; i--) {
        int bit = (n >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}
void count_one(unsigned int n)
{
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    printf("Number of 1 bits: %d\n", count);
}

// Example usage
int main() {
    print_bits(13);   // prints 00000000000000000000000000001101
    count_one(13);    // prints Number of 1 bits: 3
    return 0;
}