#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    char surname[50];
    int age;
} Student;

int do_order(char choice, Student **students, int *count, int *capacity);
void showUsers(Student *students, int count);
void updateUser(Student *students, int count);
void deleteUser(Student *students, int *count);

int findIndexById(Student *students, int count, int id);
char input(void);
int input_checker(char choice);
void clearInputBuffer(void);

char input(void) {
    char order[10];

    printf("Enter a number between 1 and 5 for the desired operation:\n"
           "1--Add user\n"
           "2--Delete user\n"
           "3--Show users\n"
           "4--Update selected user\n"
           "5--Exit program\n"
           "Choice: ");

    if (fgets(order, sizeof(order), stdin) != NULL) {
        return order[0];
    }

    return '\0';
}
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int findIndexById(Student *students, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

void deleteUser(Student *students, int *count){
    if (*count == 0)
    {
        printf("Silinecek her hansi student yoxdu\n");
        return;
    }
    int id ;
    printf("Silinecek sagirdin id daxil edin\n");
    scanf("%d", &id);
    clearInputBuffer();

    int index = findIndexById(students, *count, id);
    if (index == -1)
    {
        printf("bu id de bir sagird yoxdur\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) {
    students[i] = students[i + 1];
    }

    (*count)--;
    printf("sagird silindi'\n");
}

int input_checker(char choice) {
    if (choice < '1' || choice > '5') {
        printf("Wrong input! Please try again.\n\n");
        return 0;
    }
    return 1;
}

void updateUser(Student *students, int count){
    if (count == 0)
    {
        printf("there has no any users");
        return;
    }

    int id;
    printf("Yenilenecek istifadecinin ID-sini daxil edin: ");
    scanf("%d", &id);
    clearInputBuffer();

    int index = findIndexById(students, count, id);
    if (index == -1)
    {
        printf("bu id de bir sagird yoxdur\n");
        return;
    }

    printf("Yeni Ad: ");
    scanf("%s", students[index].name);
    printf("Yeni Soyad: ");
    scanf("%s", students[index].surname);
    printf("Yeni Yas: ");
    scanf("%d", &students[index].age);
    clearInputBuffer();

    printf("Yenilendi!\n");
    
    
    
}

void showUsers(Student *students, int count){
    if (count == 0)
    {
        printf("her hasni istifadeci yoxdur");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        printf("ID: %d | Ad: %s | Soyad: %s | Yas: %d\n",
        students[i].id,
        students[i].name,
        students[i].surname,
        students[i].age);
    }
    
}

void addUser(Student **students, int *count, int *capacity) {
    if (*count == *capacity)
    {
        int newCapacity = (*capacity == 0)? 4 : (*capacity)*2;
        Student *tmp = realloc(*students, newCapacity * sizeof(Student));
        *students = tmp;
        *capacity = newCapacity;
    }
    
    Student s;
    printf("ID: ");
    scanf("%d", &s.id);
    clearInputBuffer();

    if (findIndexById(*students,*count,s.id) != -1)
    {
        printf("istifadeciler eyni ada sahib ola bilmez\n");
        return; 
    }
    

    printf("Ad: ");
    scanf("%s", s.name);
    printf("Soyad: ");
    scanf("%s", s.surname);
    printf("Yas: ");
    scanf("%d", &s.age);
    clearInputBuffer();

    (*students)[*count] = s;
    (*count)++;

    printf("Student added!!!\n");
}
int do_order(char choice, Student **students, int *count, int *capacity) {
    if (choice == '5') {
        printf("You exit the program\n");
        return 0;
    }
    if (choice == '1') {
        addUser(students, count, capacity);
    }
    if (choice == '3') {
        showUsers(*students, *count);
    }
    if (choice == '4'){
        updateUser(*students, *count);
    }
    if (choice == '2') {
        deleteUser(*students, count);
    }
    return 1;
}

int main(void) {
    char choice;
    Student *students = NULL;
    int count = 0;
    int capacity = 0;
    int running = 1;
    while(running){
    do {
        choice = input();
    } while (!input_checker(choice));

    running = do_order(choice, &students, &count, &capacity);
}

    free(students);
    return 0;
}