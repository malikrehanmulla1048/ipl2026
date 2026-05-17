// Write a program that stores array of structures in ascii format in a file.
// Write a function to create an array of seek positions of the beginning of the each record(structure) in the file
// Write a function to display the record given the position.
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Student {
    int roll;
    char name[50];
    float marks;
};

void writeRecords(const char *filename, struct Student s[], int n) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %s %.2f\n", s[i].roll, s[i].name, s[i].marks);
    }

    fclose(fp);
}

int createSeekPositions(const char *filename, long pos[]) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file for reading.\n");
        return 0;
    }

    int count = 0;

    while (1) {
        pos[count] = ftell(fp);   // beginning of current record

        int roll;
        char name[50];
        float marks;

        if (fscanf(fp, "%d %49s %f", &roll, name, &marks) != 3) {
            break;
        }

        count++;
    }

    fclose(fp);
    return count;
}

void displayRecord(const char *filename, long position) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fseek(fp, position, SEEK_SET);

    struct Student s;
    if (fscanf(fp, "%d %49s %f", &s.roll, s.name, &s.marks) == 3) {
        printf("\nRecord found at position %ld\n", position);
        printf("Roll  : %d\n", s.roll);
        printf("Name  : %s\n", s.name);
        printf("Marks : %.2f\n", s.marks);
    } else {
        printf("Invalid record position.\n");
    }

    fclose(fp);
}

int main() {
    struct Student s[5] = {
        {101, "Aman", 85.5},
        {102, "Riya", 90.0},
        {103, "Kiran", 78.5},
        {104, "Neha", 88.0},
        {105, "Arjun", 92.5}
    };

    long positions[MAX];
    int n = 5;

    writeRecords("student.txt", s, n);

    int totalRecords = createSeekPositions("student.txt", positions);

    printf("Seek positions of records:\n");
    for (int i = 0; i < totalRecords; i++) {
        printf("Record %d starts at byte position %ld\n", i + 1, positions[i]);
    }

    int recordNumber;
    printf("\nEnter record number to display: ");
    scanf("%d", &recordNumber);

    if (recordNumber >= 1 && recordNumber <= totalRecords) {
        displayRecord("student.txt", positions[recordNumber - 1]);
    } else {
        printf("Invalid record number.\n");
    }

    return 0;
}