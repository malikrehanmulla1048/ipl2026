// Design and test a structure bitfields.
// Bitfield a;
// a.firstbit = 1;
#include <stdio.h>

struct BitField {
    unsigned int firstbit : 1;
    unsigned int secondbit : 1;
    unsigned int thirdbit : 1;
};

int main() {
    struct BitField a;
    a.firstbit = 1;
    a.secondbit = 0;
    a.thirdbit = 1;
    printf("First bit: %u\n", a.firstbit);
    printf("Second bit: %u\n", a.secondbit);
    printf("Third bit: %u\n", a.thirdbit);
    return 0;
}