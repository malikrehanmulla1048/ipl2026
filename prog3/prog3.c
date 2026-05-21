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

// Example usage
int main() {
    print_bits(13);   // prints 00000000000000000000000000001101
    return 0;
}