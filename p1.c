#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for Student
typedef struct Student {
    int student_id;
    char name[50];
    int age;
    int grades[3];
    int marks[5];  // Marks array
    char phone[15];  // Phone number
    char email[50];  // Email address
    char address[100];  // Address
    char enrollment_date[11];  // Enrollment date in YYYY-MM-DD format
    char courses[5][30];  // Courses array (up to 5 courses)
    struct Student* next;
} Student;

// Define a structure for the linked list
typedef struct {
    Student* head;
} StudentManagementSystemLinkedList;

// Function to create a new student
Student* create_student(int id, char* name, int age, int grades[], int marks[], char* phone, char* email, char* address, char* enrollment_date, char courses[][30]) {
    Student* new_student = (Student*)malloc(sizeof(Student));
    new_student->student_id = id;
    strcpy(new_student->name, name);
    new_student->age = age;
    for (int i = 0; i < 3; i++) {
        new_student->grades[i] = grades[i];
    }
    for (int i = 0; i < 5; i++) {
        new_student->marks[i] = marks[i];
    }
    strcpy(new_student->phone, phone);
    strcpy(new_student->email, email);
    strcpy(new_student->address, address);
    strcpy(new_student->enrollment_date, enrollment_date);
    for (int i = 0; i < 5; i++) {
        strcpy(new_student->courses[i], courses[i]);
    }
    new_student->next = NULL;
    return new_student;
}

// Function to add a student in order based on student_id
void add_student(StudentManagementSystemLinkedList* sms, int id, char* name, int age, int grades[], int marks[], char* phone, char* email, char* address, char* enrollment_date, char courses[][30]) {
    Student* new_student = create_student(id, name, age, grades, marks, phone, email, address, enrollment_date, courses);
    if (sms->head == NULL || sms->head->student_id > id) {
        new_student->next = sms->head;
        sms->head = new_student;
    } else {
        Student* current = sms->head;
        while (current->next != NULL && current->next->student_id < id) {
            current = current->next;
        }
        new_student->next = current->next;
        current->next = new_student;
    }
    printf("Student %s added.\n", name);
}

// Function to remove a student by ID
void remove_student(StudentManagementSystemLinkedList* sms, int id) {
    Student* temp = sms->head;
    Student* prev = NULL;

    if (temp != NULL && temp->student_id == id) {
        sms->head = temp->next;
        free(temp);
        printf("Student %d removed.\n", id);
        return;
    }

    while (temp != NULL && temp->student_id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student %d not found.\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Student %d removed.\n", id);
}

// Function to search for a student by ID
Student* search_student(StudentManagementSystemLinkedList* sms, int id) {
    Student* current = sms->head;
    while (current != NULL) {
        if (current->student_id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to update a student's information
void update_student(StudentManagementSystemLinkedList* sms, int id, char* name, int age, int grades[], int marks[], char* phone, char* email, char* address, char* enrollment_date, char courses[][30]) {
    Student* student = search_student(sms, id);
    if (student) {
        strcpy(student->name, name);
        student->age = age;
        for (int i = 0; i < 3; i++) {
            student->grades[i] = grades[i];
        }
        for (int i = 0; i < 5; i++) {
            student->marks[i] = marks[i];
        }
        strcpy(student->phone, phone);
        strcpy(student->email, email);
        strcpy(student->address, address);
        strcpy(student->enrollment_date, enrollment_date);
        for (int i = 0; i < 5; i++) {
            strcpy(student->courses[i], courses[i]);
        }
        printf("Student %d updated.\n", id);
    } else {
        printf("Student %d not found.\n", id);
    }
}

// Function to display all students
void display_students(StudentManagementSystemLinkedList* sms) {
    Student* current = sms->head;
    while (current != NULL) {
        printf("ID: %d, Name: %s, Age: %d, Grades: %d, %d, %d, Marks: %d, %d, %d, %d, %d\n", 
               current->student_id, current->name, current->age, 
               current->grades[0], current->grades[1], current->grades[2],
               current->marks[0], current->marks[1], current->marks[2], current->marks[3], current->marks[4]);
        printf("Phone: %s, Email: %s, Address: %s, Enrollment Date: %s\n", 
               current->phone, current->email, current->address, current->enrollment_date);
        printf("Courses: %s, %s, %s, %s, %s\n", 
               current->courses[0], current->courses[1], current->courses[2], current->courses[3], current->courses[4]);
        current = current->next;
    }
}

// Function to calculate the average grade of all students
void calculate_average_grade(StudentManagementSystemLinkedList* sms) {
    Student* current = sms->head;
    int total_students = 0;
    int total_grades[3] = {0, 0, 0};

    while (current != NULL) {
        for (int i = 0; i < 3; i++) {
            total_grades[i] += current->grades[i];
        }
        total_students++;
        current = current->next;
    }

    if (total_students > 0) {
        printf("Average Grades: %.2f, %.2f, %.2f\n", 
               (float)total_grades[0] / total_students, 
               (float)total_grades[1] / total_students, 
               (float)total_grades[2] / total_students);
    } else {
        printf("No students available to calculate average.\n");
    }
}

// Function to get input from the user and perform actions based on the menu
void menu(StudentManagementSystemLinkedList* sms) {
    int choice, id, age, grades[3], marks[5];
    char name[50], phone[15], email[50], address[100], enrollment_date[11], courses[5][30];

    while (1) {
        printf("\nStudent Management System Menu:\n");
        printf("1. Add Student\n");
        printf("2. Remove Student\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Display Students\n");
        printf("6. Calculate Average Grades\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                scanf("%d", &id);
                printf("Enter Student Name: ");
                scanf("%s", name);
                printf("Enter Student Age: ");
                scanf("%d", &age);
                printf("Enter Student Grades (3 grades): ");
                for (int i = 0; i < 3; i++) {
                    scanf("%d", &grades[i]);
                }
                printf("Enter Student Marks (5 marks): ");
                for (int i = 0; i < 5; i++) {
                    scanf("%d", &marks[i]);
                }
                printf("Enter Student Phone: ");
                scanf("%s", phone);
                printf("Enter Student Email: ");
                scanf("%s", email);
                printf("Enter Student Address: ");
                scanf(" %[^\n]%*c", address); // To read the full address including spaces
                printf("Enter Enrollment Date (YYYY-MM-DD): ");
                scanf("%s", enrollment_date);
                printf("Enter Student Courses (up to 5 courses): ");
                for (int i = 0; i < 5; i++) {
                    scanf("%s", courses[i]);
                }
                add_student(sms, id, name, age, grades, marks, phone, email, address, enrollment_date, courses);
                break;
            case 2:
                printf("Enter Student ID to remove: ");
                scanf("%d", &id);
                remove_student(sms, id);
                break;
            case 3:
                printf("Enter Student ID to search: ");
                scanf("%d", &id);
                Student* student = search_student(sms, id);
                if (student) {
                    printf("Found Student: ID: %d, Name: %s, Age: %d, Grades: %d, %d, %d, Marks: %d, %d, %d, %d, %d\n", 
                           student->student_id, student->name, student->age, 
                           student->grades[0], student->grades[1], student->grades[2],
                           student->marks[0], student->marks[1], student->marks[2], student->marks[3], student->marks[4]);
                    printf("Phone: %s, Email: %s, Address: %s, Enrollment Date: %s\n", 
                           student->phone, student->email, student->address, student->enrollment_date);
                    printf("Courses: %s, %s, %s, %s, %s\n", 
                           student->courses[0], student->courses[1], student->courses[2], student->courses[3], student->courses[4]);
                } else {
                    printf("Student not found.\n");
                }
                break;
            case 4:
                printf("Enter Student ID to update: ");
                scanf("%d", &id);
                printf("Enter New Student Name: ");
                scanf("%s", name);
                printf("Enter New Student Age: ");
                scanf("%d", &age);
                printf("Enter New Student Grades (3 grades): ");
                for (int i = 0; i < 3; i++) {
                    scanf("%d", &grades[i]);
                }
                printf("Enter New Student Marks (5 marks): ");
                for (int i = 0; i < 5; i++) {
                    scanf("%d", &marks[i]);
                }
                printf("Enter New Student Phone: ");
                scanf("%s", phone);
                printf("Enter New Student Email: ");
                scanf("%s", email);
                printf("Enter New Student Address: ");
                scanf(" %[^\n]%*c", address); // To read the full address including spaces
                printf("Enter New Enrollment Date (YYYY-MM-DD): ");
                scanf("%s", enrollment_date);
                printf("Enter New Student Courses (up to 5 courses): ");
                for (int i = 0; i < 5; i++) {
                    scanf("%s", courses[i]);
                }
                update_student(sms, id, name, age, grades, marks, phone, email, address, enrollment_date, courses);
                break;
            case 5:
                display_students(sms);
                break;
            case 6:
                calculate_average_grade(sms);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Main function
int main() {
    StudentManagementSystemLinkedList sms = { .head = NULL };
    menu(&sms);
    return 0;
}
