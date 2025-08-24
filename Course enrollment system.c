#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int id;
    char name[50];
    struct Student *next;
} Student;

typedef struct Course {
    char courseName[50];
    Student *head;
    struct Course *next;
} Course;

Course *courseList = NULL;

// Create new course
Course* createCourse(char cname[]) {
    Course *c = (Course*)malloc(sizeof(Course));
    strcpy(c->courseName, cname);
    c->head = NULL;
    c->next = NULL;
    return c;
}

// Find course
Course* findCourse(char cname[]) {
    Course *temp = courseList;
    while (temp) {
        if (strcmp(temp->courseName, cname) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

// Add a new course
void addCourse(char cname[]) {
    if (findCourse(cname)) {
        printf("Course already exists!\n");
        return;
    }
    Course *newCourse = createCourse(cname);
    newCourse->next = courseList;
    courseList = newCourse;
    printf("Course %s added.\n", cname);
}

// Enroll student in a course
void enrollStudent(char cname[], int id, char name[]) {
    Course *c = findCourse(cname);
    if (!c) {
        printf("Course not found!\n");
        return;
    }
    Student *newS = (Student*)malloc(sizeof(Student));
    newS->id = id;
    strcpy(newS->name, name);
    newS->next = c->head;
    c->head = newS;
    printf("Student enrolled in %s.\n", cname);
}

// Drop student from course
void dropStudent(char cname[], int id) {
    Course *c = findCourse(cname);
    if (!c) { printf("Course not found!\n"); return; }

    Student *temp = c->head, *prev = NULL;
    while (temp) {
        if (temp->id == id) {
            if (prev) prev->next = temp->next;
            else c->head = temp->next;
            free(temp);
            printf("Student dropped from %s.\n", cname);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Student not found in %s.\n", cname);
}

// Display students in course
void displayCourse(char cname[]) {
    Course *c = findCourse(cname);
    if (!c) { printf("Course not found!\n"); return; }
    Student *temp = c->head;
    printf("Students in %s:\n", cname);
    while (temp) {
        printf("%d %s\n", temp->id, temp->name);
        temp = temp->next;
    }
}

// Count students
void countStudents(char cname[]) {
    Course *c = findCourse(cname);
    if (!c) { printf("Course not found!\n"); return; }
    int count = 0;
    Student *temp = c->head;
    while (temp) { count++; temp = temp->next; }
    printf("Total students in %s = %d\n", cname, count);
}

// Main Menu
int main() {
    int choice, id;
    char cname[50], name[50];

    while (1) {
        printf("\n--- Course Enrollment Management ---\n");
        printf("1. Add Course\n2. Enroll Student\n3. Drop Student\n4. Display Students\n5. Count Students\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter course name: ");
                scanf("%s", cname);
                addCourse(cname);
                break;
            case 2:
                printf("Enter course name: ");
                scanf("%s", cname);
                printf("Enter student ID and Name: ");
                scanf("%d %s", &id, name);
                enrollStudent(cname, id, name);
                break;
            case 3:
                printf("Enter course name: ");
                scanf("%s", cname);
                printf("Enter student ID: ");
                scanf("%d", &id);
                dropStudent(cname, id);
                break;
            case 4:
                printf("Enter course name: ");
                scanf("%s", cname);
                displayCourse(cname);
                break;
            case 5:
                printf("Enter course name: ");
                scanf("%s", cname);
                countStudents(cname);
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
