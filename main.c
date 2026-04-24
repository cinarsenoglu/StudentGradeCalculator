#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50

typedef struct {
    int id;
    char name[NAME_LENGTH];
    float grade;
} Student;

void clearInputBuffer(void) {
    while (getchar() != '\n');
}

void showMenu(void) {
    printf("\n===== Student Grade Manager =====\n");
    printf("1. Add student\n");
    printf("2. List students\n");
    printf("3. Search student by ID\n");
    printf("4. Update student grade\n");
    printf("5. Delete student\n");
    printf("6. Save to file\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void addStudent(Student students[], int *studentCount) {
    if (*studentCount >= MAX_STUDENTS) {
        printf("Student list is full.\n");
        return;
    }

    Student newStudent;

    printf("\n--- Add Student ---\n");

    printf("Enter student ID: ");
    scanf("%d", &newStudent.id);

    printf("Enter student name: ");
    scanf(" %[^\n]", newStudent.name);

    printf("Enter student grade: ");
    scanf("%f", &newStudent.grade);

    students[*studentCount] = newStudent;
    (*studentCount)++;

    printf("Student added successfully.\n");
}

void listStudents(Student students[], int studentCount) {
    if (studentCount == 0) {
        printf("\nNo students found.\n");
        return;
    }

    printf("\n--- Student List ---\n");

    for (int i = 0; i < studentCount; i++) {
        printf("ID    : %d\n", students[i].id);
        printf("Name  : %s\n", students[i].name);
        printf("Grade : %.2f\n", students[i].grade);
        printf("-------------------\n");
    }
}

void searchStudent(Student students[], int studentCount) {
    int searchID;
    int found = 0;

    printf("\nEnter student ID: ");
    scanf("%d", &searchID);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchID) {
            printf("\nStudent Found:\n");
            printf("ID    : %d\n", students[i].id);
            printf("Name  : %s\n", students[i].name);
            printf("Grade : %.2f\n", students[i].grade);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

void updateGrade(Student students[], int studentCount) {
    int searchID;
    int found = 0;
    float newGrade;

    printf("\nEnter student ID: ");
    scanf("%d", &searchID);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchID) {
            printf("Current grade: %.2f\n", students[i].grade);

            printf("Enter new grade: ");
            scanf("%f", &newGrade);

            students[i].grade = newGrade;

            printf("Grade updated.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

void deleteStudent(Student students[], int *studentCount) {
    int searchID;
    int found = 0;

    printf("\nEnter student ID: ");
    scanf("%d", &searchID);

    for (int i = 0; i < *studentCount; i++) {
        if (students[i].id == searchID) {
            for (int j = i; j < *studentCount - 1; j++) {
                students[j] = students[j + 1];
            }

            (*studentCount)--;
            printf("Student deleted.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

void saveToFile(Student students[], int studentCount) {
    FILE *file = fopen("students.txt", "w");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%d %s %.2f\n",
                students[i].id,
                students[i].name,
                students[i].grade);
    }

    fclose(file);

    printf("Data saved successfully.\n");
}

int main(void) {
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    while (1) {
        showMenu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                addStudent(students, &studentCount);
                break;

            case 2:
                listStudents(students, studentCount);
                break;

            case 3:
                searchStudent(students, studentCount);
                break;

            case 4:
                updateGrade(students, studentCount);
                break;

            case 5:
                deleteStudent(students, &studentCount);
                break;

            case 6:
                saveToFile(students, studentCount);
                break;

            case 0:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}