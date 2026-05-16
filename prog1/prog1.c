// The advantage of storing array of structures as binary files is that we can use fseek to go to specific record and get the record.
// Write a program to store n records in binary file.
// Write a function to get mth record and display.
// Use fseek
// Write a function to delete a record.
// Deleting a record requires thinking.
#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll;
    char name[30];
    float marks;
};

void storeRecords(const char *filename, int n);
void displayMthRecord(const char *filename, int m);
void deleteRecord(const char *filename, int delRoll);
void displayAll(const char *filename);

int main() {
    const char *filename = "students.dat";
    int n, m, delRoll, choice;

    printf("Enter number of records: ");
    scanf("%d", &n);

    storeRecords(filename, n);

    do {
        printf("\n--- MENU ---\n");
        printf("1. Display mth record\n");
        printf("2. Delete a record by roll number\n");
        printf("3. Display all records\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter m: ");
                scanf("%d", &m);
                displayMthRecord(filename, m);
                break;

            case 2:
                printf("Enter roll number to delete: ");
                scanf("%d", &delRoll);
                deleteRecord(filename, delRoll);
                break;

            case 3:
                displayAll(filename);
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}

void storeRecords(const char *filename, int n) {
    FILE *fp;
    struct Student s;
    int i;

    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    for (i = 0; i < n; i++) {
        printf("\nEnter details for record %d\n", i + 1);
        printf("Roll: ");
        scanf("%d", &s.roll);
        printf("Name: ");
        scanf("%s", s.name);
        printf("Marks: ");
        scanf("%f", &s.marks);

        fwrite(&s, sizeof(struct Student), 1, fp);
    }

    fclose(fp);
    printf("\nRecords stored successfully.\n");
}

void displayMthRecord(const char *filename, int m) {
    FILE *fp;
    struct Student s;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    if (fseek(fp, (m - 1) * sizeof(struct Student), SEEK_SET) != 0) {
        printf("Invalid record position.\n");
        fclose(fp);
        return;
    }

    if (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        printf("\nRecord %d:\n", m);
        printf("Roll  : %d\n", s.roll);
        printf("Name  : %s\n", s.name);
        printf("Marks : %.2f\n", s.marks);
    } else {
        printf("Record does not exist.\n");
    }

    fclose(fp);
}

void deleteRecord(const char *filename, int delRoll) {
    FILE *fp, *temp;
    struct Student s;
    int found = 0;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.roll == delRoll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove(filename);
        rename("temp.dat", filename);
        printf("Record with roll %d deleted successfully.\n", delRoll);
    } else {
        remove("temp.dat");
        printf("Record not found.\n");
    }
}

void displayAll(const char *filename) {
    FILE *fp;
    struct Student s;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nAll Records:\n");
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        printf("Roll: %d, Name: %s, Marks: %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
}