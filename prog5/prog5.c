// union decision {
// unsigned char flags;
// struct field {
// int your_choice:1; /* tobe computed */
// int your_mothers_choice:1;
// int your_fathers_choice:1;
// int socially_acceptable:1;
// int financially_viable:1;
// int do_you_aptitude:1;
// int do_you_likeit:1;
// int decision:1; /* to be computed */
// };

// union decision input();
// /* Write an expression that closely matches how you make decision */
// void make_decision(union decision *d);
// /* Print a nice narrative*/
// void print_decsion(union decision d);
// /* think of an interesting use for flags and printt an interpretaion based on the number stored in flags */
// void print_conclusion_based_on_flags( union decision d);
#include <stdio.h>

union decision {
    unsigned char flags;
    struct {
        unsigned char your_choice:1;         /* to be computed */
        unsigned char your_mothers_choice:1;
        unsigned char your_fathers_choice:1;
        unsigned char socially_acceptable:1;
        unsigned char financially_viable:1;
        unsigned char do_you_aptitude:1;
        unsigned char do_you_likeit:1;
        unsigned char decision:1;            /* to be computed */
    } field;
};

/* Function Prototypes */
union decision input();
void make_decision(union decision *d);
void print_decision(union decision d);
void print_conclusion_based_on_flags(union decision d);

int main() {
    printf("--- The Life Path Algorithm ---\n");
    
    // 1. Gather data
    union decision my_life_choice = input();
    
    // 2. Compute the unknowns
    make_decision(&my_life_choice);
    
    // 3. Print the narrative
    print_decision(my_life_choice);
    
    // 4. Interpret the raw byte data
    print_conclusion_based_on_flags(my_life_choice);
    
    return 0;
}

union decision input() {
    union decision d;
    d.flags = 0; // Initialize all bits to 0 to prevent garbage memory
    int temp;

    printf("\nAnswer the following with 1 (Yes) or 0 (No):\n");
    
    printf("Does your mother approve? ");
    scanf("%d", &temp); d.field.your_mothers_choice = temp;
    
    printf("Does your father approve? ");
    scanf("%d", &temp); d.field.your_fathers_choice = temp;
    
    printf("Is it socially acceptable? ");
    scanf("%d", &temp); d.field.socially_acceptable = temp;
    
    printf("Is it financially viable? ");
    scanf("%d", &temp); d.field.financially_viable = temp;
    
    printf("Do you have the aptitude for it? ");
    scanf("%d", &temp); d.field.do_you_aptitude = temp;
    
    printf("Do you actually like it? ");
    scanf("%d", &temp); d.field.do_you_likeit = temp;
    
    return d;
}

void make_decision(union decision *d) {
    /* * EXPRESSION 1: 'your_choice' 
     * It is truly your choice ONLY if you like it AND you are good at it. 
     */
    d->field.your_choice = (d->field.do_you_likeit & d->field.do_you_aptitude);

    /* * EXPRESSION 2: 'decision' 
     * You will do it IF it's financially viable AND 
     * (It is your choice OR both your parents are forcing you into it)
     */
    d->field.decision = d->field.financially_viable & 
                        (d->field.your_choice | 
                        (d->field.your_mothers_choice & d->field.your_fathers_choice));
}

void print_decision(union decision d) {
    printf("\n=== THE NARRATIVE ===\n");
    printf("You stand at a crossroads in life. ");
    
    if (d.field.your_choice) {
        printf("Your heart and skills are perfectly aligned; this is what you want. ");
    } else {
        printf("Deep down, you know this isn't your true calling. ");
    }

    if (d.field.your_mothers_choice && d.field.your_fathers_choice) {
        printf("Your parents are absolutely thrilled with the prospect. ");
    } else if (d.field.your_mothers_choice || d.field.your_fathers_choice) {
        printf("Your parents are split; Thanksgiving dinners might be awkward. ");
    } else {
        printf("Your parents think you've lost your mind. ");
    }

    if (!d.field.socially_acceptable) {
        printf("Society might judge you, but you're a rebel. ");
    }

    printf("\n\nFINAL VERDICT: ");
    if (d.field.decision) {
        printf("Taking everything into account, you decide to GO FOR IT!\n");
    } else {
        printf("After a harsh reality check, you decide to WALK AWAY.\n");
    }
}

void print_conclusion_based_on_flags(union decision d) {
    printf("\n=== THE BIT-LEVEL ORACLE ===\n");
    
    /* * By looking at the 8-bit 'flags' variable, we evaluate the entire state 
     * of the union as a single integer (ranging from 0 to 255).
     * Note: Exact integer values depend on your machine's Endianness!
     */
    printf("Your life choices resulted in a raw memory byte of: %d (Hex: 0x%X)\n", d.flags, d.flags);
    
    if (d.flags == 255) { // 0xFF
        printf("Oracle says: Maximum Entropy! Every single bit is flipped to 1. The universe is perfectly aligned. Go buy a lottery ticket.\n");
    } else if (d.flags == 0) {
        printf("Oracle says: Absolute Zero. Nothing aligns. Do not touch this idea with a ten-foot pole.\n");
    } else if (d.flags > 127) {
        // If the highest-order bit is flipped, the number is > 127.
        printf("Oracle says: A heavy numerical weight. There's a lot of pressure riding on this.\n");
    } else if (d.flags % 2 != 0) {
        printf("Oracle says: An odd-numbered byte. This path is eccentric and unconventional. Embrace the chaos.\n");
    } else {
        printf("Oracle says: A moderate, even-numbered score. This is standard adulting: a calculated compromise.\n");
    }
    printf("============================\n");
}