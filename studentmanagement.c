#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

void addStudent(FILE *fp) {
    Student s;
    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Student Name: ");
    getchar(); // clear newline
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0; // remove newline
    printf("Enter Student Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, fp);
    printf("Student added successfully.\n");
}

void displayStudents(FILE *fp) {
    Student s;
    rewind(fp); // reset to start
    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
    }
}

void searchStudent(FILE *fp, int searchId) {
    Student s;
    int found = 0;
    rewind(fp);
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == searchId) {
            printf("Student Found:\n");
            printf("ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student with ID %d not found.\n", searchId);
    }
}

int main() {
    FILE *fp = fopen("students.dat", "ab+");
    if (!fp) {
        perror("Unable to open file");
        return 1;
    }

    int choice, id;
    do {
        printf("\n--- Student Management ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(fp);
                break;
            case 2:
                displayStudents(fp);
                break;
            case 3:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                searchStudent(fp, id);
                break;
            case 4:
                fclose(fp);
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
