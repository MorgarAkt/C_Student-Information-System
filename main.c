#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Student
{
    char name[50];
    int number;
    char password[20];
    char lectures[4][40];
    int grades[4];
    int intern;
    int semester;
    char department[30];
    int check;
} students;

typedef struct Lecturer
{
    char id[20];
    char name[50];
    char password[20];
    char lectures[4][40];
} lecturers;

char *departmans[3] = {"Computer Science", "Electrical Engineering", "Mechanical Engineering"};
char *lectures[12] = {"Algorithms", "Data_Structures", "Operating_Systems", "Computer_Architecture", "Electric_Circuits", "Termodinamics", "Microprocessors", "Microcontrollers", "Digital_Electronics", "Analog_Electronics", "Digital_Signal_Processing", "Ethics"};

FILE *stundentPaper, *studentCheck, *studentNames, *studentNumbers, *studentPasswords, *studentGrades, *studentLectures, *studentIntern, *studentDepartment, *studentSemester, *lecturerNames, *lecturerPasswords, *lecturerLectures, *lecturerIds, *adminPasswordF, *studentAffairPassword, *numberOfStudents, *numberOfLecturers;

void adminPanel(char password[], char studentAfPassword[], int lecturerCount, lecturers lecturer[]);
void studentAffairPanel(students student[200], char password[20], int *studentCount, char *studentAfPassword, lecturers lecturer[4], int *lecturerCount);
void lecturerPanel(char username[], char password[], lecturers lecturer[], students student[]);
void studentPanel(char username[], students student[], lecturers lecturer[], int studentCount);
void WriteEverythingToFile(students student[], lecturers lecturer[], int studentCount, int lecturerCount, char studentAfPassword[], char adminPassword[]);
void ReadEverythingFromFile(students student[], lecturers lecturer[], int *studentCount, int *lecturerCount, char studentAfPassword[], char adminPassword[]);
void encrypt(char password[]);
void decrypt(char password[]);

void printLogo()
{
    printf(" __ _             _            _      _____        __                            _   _             \n"
           "/ _\\ |_ _   _  __| | ___ _ __ | |_    \\_   \\_ __  / _| ___  _ __ _ __ ___   __ _| |_(_) ___  _ __  \n"
           "\\ \\| __| | | |/ _` |/ _ \\ '_ \\| __|    / /\\/ '_ \\| |_ / _ \\| '__| '_ ` _ \\ / _` | __| |/ _ \\| '_ \\ \n"
           "_\\ \\ |_| |_| | (_| |  __/ | | | |_  /\\/ /_ | | | |  _| (_) | |  | | | | | | (_| | |_| | (_) | | | |\n"
           "\\__/\\__|\\__,_|\\__,_|\\___|_| |_|\\__| \\____/ |_| |_|_|  \\___/|_|  |_| |_| |_|\\__,_|\\__|_|\\___/|_| |_|\n"
           "                                                                                                   \n"
           "                            __           _                                                         \n"
           "                           / _\\_   _ ___| |_ ___ _ __ ___                                          \n"
           "                           \\ \\| | | / __| __/ _ \\ '_ ` _ \\                                         \n"
           "                           _\\ \\ |_| \\__ \\ ||  __/ | | | | |                                        \n"
           "                           \\__/\\__, |___/\\__\\___|_| |_| |_|                                        \n"
           "                               |___/                                                               \n");
}

// using argv and argc to take type of user, user number and password from user
int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Turkish.turkish.1254");
    SetConsoleCP(1254);
    SetConsoleOutputCP(1254);

    int studentCount = 0;
    int lecturerCount = 0;
    char tempNumberString[20];
    char studentAfPassword[20];
    char adminPassword[20];

    char authority[20];
    char userName[20];
    char userPassword[20];

    students student[100];
    lecturers lecturer[4];
    ReadEverythingFromFile(student, lecturer, &studentCount, &lecturerCount, studentAfPassword, adminPassword);

    // send the user to chosen menu with if else statements
    // also every menu is a function

    printLogo();
    printf("\nWhat is the user's authorization?\nAdmin/Student Affair/Lecturer/Student\n");
    scanf("%s", authority);
    if (strcmp(strlwr(authority), "lecturer") == 0 || strcmp(strlwr(authority), "student") == 0)
    {
        printf("What is the user's username?\n");
        scanf("%s", userName);
    }

    printf("What is the user's password?\n");
    scanf("%s", userPassword);

    system("cls");
    printLogo();
    if (strcmp(strlwr(authority), "admin") == 0)
    {
        if (strcmp(userPassword, adminPassword) == 0)
        {

            adminPanel(adminPassword, studentAfPassword, lecturerCount, lecturer);
        }
        else
        {
            printf("Wrong password\n");
        }
    }
    else if (strcmp(strlwr(authority), "lecturer") == 0)
    {
        for (int i = 0; i < lecturerCount; i++)
        {
            if (strcmp(userName, lecturer[i].id) == 0 && strcmp(userPassword, lecturer[i].password) == 0)
            {

                lecturerPanel(userName, userPassword, lecturer, student);
                break;
            }
        }
        printf("Wrong username or password\n");
    }
    else if (strcmp(strlwr(authority), "student") == 0)
    {
        for (int i = 0; i < studentCount; i++)
        {
            itoa(student[i].number, tempNumberString, 10);
            if (strcmp(userName, tempNumberString) == 0 && strcmp(userPassword, student[i].password) == 0)
            {

                studentPanel(userName, student, lecturer, studentCount);
                break;
            }
            printf("Wrong username or password\n");
        }
    }
    else if (strcmp(strlwr(authority), "studentaffair") == 0)
    {
        if (strcmp(userPassword, studentAfPassword) == 0)
        {

            studentAffairPanel(student, userName, &studentCount, studentAfPassword, lecturer, &lecturerCount);
        }
    }
    else
    {
        printf("wrong type of input!!!!!!\n");
        exit(0);
    }
    if (argc == 0)
    {
        exit(0);
    }
    WriteEverythingToFile(student, lecturer, studentCount, lecturerCount, studentAfPassword, adminPassword);
    return 0;
}

// admin menu
void adminPanel(char password[], char studentAfPassword[], int lecturerCount, lecturers lecturer[])
{
    int studentCount = 0;
    char tempPass[20];
    char tempId[20];
    char confirm;
    int temp1 = 0;
    int menuCloser = 0;
    do
    {
        printf("1. Change Admin Password\n");
        printf("2. Change Student Affairs Password\n");
        printf("3. Change Lecturer Password\n");
        printf("5. Exit\n\n");
        scanf("%d", &temp1);
        switch (temp1)
        {
        case 1:
            printf("Enter new password: ");
            scanf("%s", &tempPass);
            strcpy(password, tempPass);
            printf("Password changed\n");
            menuCloser = 1;
            break;
        case 2:
            printf("Enter new password: ");
            scanf("%s", &tempPass);
            strcpy(studentAfPassword, tempPass);
            printf("Password changed\n");
            menuCloser = 1;
            break;
        case 3:
            printf("Enter new password: ");
            scanf("%s", &tempPass);
            printf("Enter lecturer id: ");
            scanf("%s", &tempPass);
            for (int i = 0; i < lecturerCount; i++)
            {
                if (strcmp(tempPass, lecturer[i].id) == 0)
                {
                    strcpy(lecturer[i].password, tempPass);
                    printf("Password changed\n");
                    menuCloser = 1;
                    break;
                }
            }
            menuCloser = 1;
            break;
        case 5:
            menuCloser = 1;
            break;
        default:
            printf("Invalid input\n");
            break;
        }
    } while (menuCloser == 0);
}

// student affair menu
void studentAffairPanel(students student[200], char password[20], int *studentCount, char *studentAfPassword, lecturers lecturer[4], int *lecturerCount)
{
    char tempPass[20];
    char tempName[50] = "\0";
    char tempId[20] = "\0";
    int tempNumber;
    int temp1 = 0;
    int temp2 = 0;
    int menuCloser = 0;
    do
    {
        printf("1. Change Student Affairs Password\n");
        printf("2. Add Student\n");
        printf("3. Delete Student\n");
        printf("4. Print All Students\n");
        printf("5. Add Lecturer\n");
        printf("6. Print Lecturer\n");
        printf("7. Assing Lectures to Lecturer\n");
        printf("8. Confirm Internship\n");
        printf("9. Exit\n\n");
        scanf("%d", &temp1);
        switch (temp1)
        {
        case 1:
            printf("Enter new password: ");
            scanf("%s", &tempPass);
            strcpy(studentAfPassword, tempPass);
            menuCloser = 1;
            break;

        // adds student to struct array and increases student count
        // also defines the defined lectures to student
        // and sets the student's password
        case 2:
            printf("Enter student name: ");
            scanf("%*c%50[^\n]", tempName);
            printf("Enter student number: ");
            scanf("%d", &tempNumber);
            strcpy(student[*studentCount].name, tempName);
            strcpy(student[*studentCount].password, "12345678");
            student[*studentCount].number = tempNumber;
            printf("Enter student department: \n");
            printf("1. Computer Science\n");
            printf("2. Electrical Engineering\n");
            printf("3. Mechanical Engineering\n");
            scanf("%d", &temp1);
            if (temp1 == 1)
            {
                for (int i = 0; i < 4; i++)
                {
                    strcpy(student[*studentCount].lectures[i], lectures[i]);
                }
            }
            else if (temp1 == 2)
            {
                for (int i = 0; i < 4; i++)
                {
                    strcpy(student[*studentCount].lectures[i], lectures[4 + i]);
                }
            }
            else if (temp1 == 3)
            {
                for (int i = 0; i < 4; i++)
                {
                    strcpy(student[*studentCount].lectures[i], lectures[8 + i]);
                }
            }
            strcpy(student[*studentCount].department, departmans[temp1 - 1]);
            student[*studentCount].check = 0;
            student[*studentCount].intern = 0;
            printf("Student added\n");
            *studentCount = *studentCount + 1;
            break;
        // deletes the student with shifting on array
        case 3:
            printf("Enter student number: ");
            scanf("%d", &tempNumber);
            for (int i = 0; i < *studentCount; i++)
            {
                if (student[i].number == tempNumber)
                {
                    for (int j = i; j < *studentCount - 1; j++)
                    {
                        student[j] = student[j + 1];
                    }
                    *studentCount = *studentCount - 1;
                    printf("Student deleted\n");
                    break;
                }
            }
            break;
            // lists every student in array
        case 4:
            for (int i = 0; i < *studentCount; i++)
            {
                printf("name = %s| number = %d| password = %s| departmant = %s\n", student[i].name, student[i].number, student[i].password, student[i].department);
            }
            break;
            // adds a lecturer to array
        case 5:
            if (*lecturerCount < 4)
            {
                printf("Enter lecturer name: ");
                scanf("%*c%50[^\n]", tempName);
                printf("Enter lecturer password: ");
                scanf("%s", tempPass);
                strcpy(lecturer[*lecturerCount].name, tempName);
                printf("Enter lecturer id: ");
                scanf("%s", tempId);
                strcpy(lecturer[*lecturerCount].id, tempId);
                strcpy(lecturer[*lecturerCount].password, tempPass);
                *lecturerCount = *lecturerCount + 1;
                printf("Lecturer added\n");
            }
            else
            {
                printf("Lecturer limit reached. There are already %d lecturers exists\n", *lecturerCount);
            }
            break;
        case 6:
            for (int i = 0; i < *lecturerCount; i++)
            {
                printf("name = %s| id = %s| password = %s| lectures =%s %s %s %s\n", lecturer[i].name, lecturer[i].id, lecturer[i].password, lecturer[i].lectures[0], lecturer[i].lectures[1], lecturer[i].lectures[2], lecturer[i].lectures[3]);
            }

            break;
            // assigns lectures to lecturer
        case 7:
            for (int i = 0; i < *lecturerCount; i++)
            {
                for (int k = 0; k < 3; k++)
                {

                    printf("%d. Lecturers Name = %s\n\n", i + 1, lecturer[i].name);
                    for (int j = 0; j < 12; j++)
                    {
                        printf("%d. %s\n", j + 1, lectures[j]);
                    }
                    scanf("%d", &temp2);
                    switch (temp2)
                    {
                    case 1:
                        strcpy(lecturer[i].lectures[k], lectures[0]);
                        break;
                    case 2:
                        strcpy(lecturer[i].lectures[k], lectures[1]);
                        break;
                    case 3:
                        strcpy(lecturer[i].lectures[k], lectures[2]);
                        break;
                    case 4:
                        strcpy(lecturer[i].lectures[k], lectures[3]);
                        break;
                    case 5:
                        strcpy(lecturer[i].lectures[k], lectures[4]);
                        break;
                    case 6:
                        strcpy(lecturer[i].lectures[k], lectures[5]);
                        break;
                    case 7:
                        strcpy(lecturer[i].lectures[k], lectures[6]);
                        break;
                    case 8:
                        strcpy(lecturer[i].lectures[k], lectures[7]);
                        break;
                    case 9:
                        strcpy(lecturer[i].lectures[k], lectures[8]);
                        break;
                    case 10:
                        strcpy(lecturer[i].lectures[k], lectures[9]);
                        break;
                    case 11:
                        strcpy(lecturer[i].lectures[k], lectures[10]);
                        break;
                    case 12:
                        strcpy(lecturer[i].lectures[k], lectures[11]);
                        break;
                    default:
                        printf("Invalid input\n");
                        k = k - 1;
                        break;
                    }
                }
            }
            break;
            // a menu to confirm student's internship
        case 8:
            printf("Enter student number: ");
            scanf("%d", &tempNumber);
            for (int i = 0; i < *studentCount; i++)
            {
                if (student[i].number == tempNumber)
                {
                    student[i].intern = 1;
                    printf("Student did her internship\n");
                }
            }
            break;
        case 9:
            menuCloser = 1;
            break;
        default:
            printf("Invalid input\n");
            break;
        }
    } while (menuCloser == 0);
}

// lecturer menu
void lecturerPanel(char username[], char password[], lecturers lecturer[], students student[])
{
    char tempPass[20];
    char tempLecture[20];
    int temp1 = 0;
    int temp2 = 0;
    int temp3 = 0;
    int menuCloser = 0;
    int whichLecturer = 0;
    int whichStudent = 500;

    // finds the Lecturers position in array
    // alsa similar named variables like whichStudent and whichLecturer are used to find the position of the lecturer and student in array
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(username, lecturer[i].id) == 0 && strcmp(password, lecturer[i].password) == 0)
        {
            whichLecturer = i;
            break;
        }
    }

    do
    {
        printf("1. Change Lecturer Password\n");
        printf("2. Enter Grade\n");
        printf("3. Exit\n");
        scanf("%d", &temp1);
        switch (temp1)
        {
        case 1:
            printf("Enter new password: ");
            scanf("%s", &tempPass);
            strcpy(lecturer[whichLecturer].password, tempPass);
            menuCloser = 1;
            break;
        case 2:
            printf("Enter student number: ");
            scanf("%d", &temp3);
            for (int i = 0; i < 4; i++)
            {
                if (student[i].number == temp3)
                {
                    whichStudent = i;
                    break;
                }
            }
            if (whichStudent == 500)
            {
                printf("Student not found\n");
                break;
            }
            printf("Enter The Name Of The Lecture: \n");
            printf("%s\n%s\n%s\n", lecturer[whichLecturer].lectures[0], lecturer[whichLecturer].lectures[1], lecturer[whichLecturer].lectures[2]);
            scanf("%s", &tempLecture);
            for (int i = 0; i < 4; i++)
            {
                if (strcmp(lecturer[whichLecturer].lectures[i], tempLecture) == 0)
                {
                    temp2 = i;
                    break;
                }
            }
            for (int i = 0; i < 4; i++)
            {
                if (strcmp(student[whichStudent].lectures[i], tempLecture) == 0)
                {
                    printf("Enter the grade: \n");
                    scanf("%d", &student[whichStudent].grades[i]);
                    student[whichStudent].check = student[whichStudent].check + 1;
                    break;
                }
            }

            break;
        case 3:
            menuCloser = 1;
            break;
        default:
            printf("Invalid input\n");
            break;
        }
    } while (menuCloser == 0);
}

// students menu
void studentPanel(char username[], students student[], lecturers lecturer[], int studentCount)
{
    char tempPass[20];
    char tempNumber[20];
    int tempNumber1 = 0;
    int departmant = 0;
    int studentCheckTemp = 0;
    int temp1 = 0;
    int menuCloser = 0;
    int a = 0;
    int gradeSum = 0;
    float gradeAverage = 0;

    // turning argv to int
    tempNumber1 = atoi(username);

    for (int i = 0; i < studentCount; i++)
    {
        if (student[i].number == tempNumber1)
        {
            a = i;
            break;
        }
    }

    if (student[a].check >= 4)
    {
        studentCheckTemp = 4;
    }
    else
    {
        studentCheckTemp = student[a].check;
    }

    if (student[a].check > 10)
    {
        for (int i = a; i < studentCount; i++)
        {
            student[i] = student[i + 1];
        }
        studentCount--;
    }

    printf("welcome %s\n", student[a].name);
    do
    {

        // this block prints student's graduate paper
        if (student[a].grades[0] >= 50 && student[a].grades[1] >= 50 && student[a].grades[2] >= 50 && student[a].grades[3] >= 50 && student[a].intern >= 1)
        {
            printf("You have succesfully graduated");
            stundentPaper = fopen(student[a].name, "w");
            fprintf(stundentPaper, "Your name is %s\n", student[a].name);
            fprintf(stundentPaper, "your departmant is %s\n", student[a].department);
            fprintf(stundentPaper, "your grades are %d %d %d %d \n", student[a].grades[0], student[a].grades[1], student[a].grades[2], student[a].grades[3]);
            gradeAverage = ((float)student[a].grades[0] + (float)student[a].grades[1] + (float)student[a].grades[2] + (float)student[a].grades[3]) / 4;
            fprintf(stundentPaper, "your average grade is %d \n", gradeAverage);
            fclose(stundentPaper);
            break;
        }

        printf("1. Change Student Password\n");
        printf("2. Print Grade\n");
        printf("3. Print Lecture\n");
        printf("4 .Exit\n");
        scanf("%d", &temp1);

        switch (temp1)
        {
        case 1:
            printf("Enter new password: ");
            scanf("%s", &tempPass);
            strcpy(student[a].password, tempPass);
            menuCloser = 1;
            break;
        case 2:
            for (int i = 0; i < studentCheckTemp; i++)
            {
                printf("-- %d.  %s %d\n", i, student[a].lectures[i], student[a].grades[i]);
                gradeSum = gradeSum + student[a].grades[i];
            }
            printf("Average Grade: %.2f\n", (float)gradeSum / (float)studentCheckTemp);
            break;
        case 3:
            printf("This term's lectures are :\n");
            printf("%s\n%s\n%s\n", student[a].lectures[0], student[a].lectures[1], student[a].lectures[2], student[a].lectures[3]);
            break;
        case 4:
            menuCloser = 1;
            break;
        default:
            printf("Invalid input\n");
            break;
        }
    } while (menuCloser == 0);
}

// cesar cipher algorith for password encryption
void decryptCesar(char *password)
{
    for (int i = 0; i < strlen(password); i++)
    {
        password[i] = password[i] - 1;
    }
}

void encryptCesar(char *password)
{
    for (int i = 0; i < strlen(password); i++)
    {
        password[i] = password[i] + 1;
    }
}

// read and write EverythingTOFROMFile functions prints all arrays and variables to file and reads them back
// these functions are only working for 2 in program
// first in the start for taking back all data back
// second in the end for taking all data to file
void ReadEverythingFromFile(students student[], lecturers lecturer[], int *studentCount, int *lecturerCount, char studentAfPassword[], char adminPassword[])
{
    int tempNumberOfStudents = 0;
    int tempNumberOfLecturers = 0;
    char tempStudentAfPassword[20] = "\0";
    char tempStudentPasswords[20] = "\0";
    char tempLecturerPasswords[20] = "\0";

    numberOfStudents = fopen("numberOfStudents.txt", "r");
    studentCheck = fopen("studentCheck.txt", "r");
    studentNames = fopen("studentNames.txt", "r");
    studentNumbers = fopen("studentNumbers.txt", "r");
    studentDepartment = fopen("studentDepartment.txt", "r");
    studentPasswords = fopen("studentPasswords.txt", "r");
    studentIntern = fopen("studentIntern.txt", "r");
    studentGrades = fopen("studentGrades.txt", "r");
    studentLectures = fopen("studentLectures.txt", "r");

    numberOfLecturers = fopen("numberOfLecturers.txt", "r");
    lecturerPasswords = fopen("lecturerPasswords.txt", "r");
    lecturerNames = fopen("lecturerNames.txt", "r");
    lecturerIds = fopen("lecturerIds.txt", "r");
    lecturerLectures = fopen("lecturerLectures.txt", "r");
    studentAffairPassword = fopen("studentAffairPassword.txt", "r");

    adminPasswordF = fopen("adminPassword.txt", "r");

    fscanf(adminPasswordF, "%s", adminPassword);
    decryptCesar(adminPassword);
    fscanf(numberOfLecturers, "%d", &tempNumberOfLecturers);
    fscanf(numberOfStudents, "%d\n", &tempNumberOfStudents);
    fscanf(studentAffairPassword, "%s\n", tempStudentAfPassword);
    decryptCesar(tempStudentAfPassword);
    strcpy(studentAfPassword, tempStudentAfPassword);
    *studentCount = *studentCount + tempNumberOfStudents;
    *lecturerCount = *lecturerCount + tempNumberOfLecturers;
    for (int i = 0; i < tempNumberOfStudents; i++)
    {
        fscanf(studentLectures, "%s %s %s %s\n", student[i].lectures[0], student[i].lectures[1], student[i].lectures[2], student[i].lectures[3]);
        fscanf(studentGrades, "%d %d %d %d\n", &student[i].grades[0], &student[i].grades[1], &student[i].grades[2], &student[i].grades[3]);
        fscanf(studentDepartment, "%[^\n]\n", student[i].department);
        fscanf(studentNames, "%[^\n]\n", student[i].name);
        fscanf(studentNumbers, "%d\n", &student[i].number);
        fscanf(studentPasswords, "%s\n", tempStudentPasswords);
        fscanf(studentCheck, "%d\n", &student[i].check);
        fscanf(studentIntern, "%d\n", &student[i].intern);
        decryptCesar(tempStudentPasswords);
        strcpy(student[i].password, tempStudentPasswords);
    }

    for (int i = 0; i < tempNumberOfLecturers; i++)
    {
        fscanf(lecturerNames, "%[^\n]\n", lecturer[i].name);
        fscanf(lecturerIds, "%s\n", lecturer[i].id);
        fscanf(lecturerPasswords, "%s\n", lecturer[i].password);
        fscanf(lecturerLectures, "%s %s %s\n", lecturer[i].lectures[0], lecturer[i].lectures[1], lecturer[i].lectures[2]);
    }

    fclose(studentCheck);
    fclose(numberOfStudents);
    fclose(studentNames);
    fclose(studentNumbers);
    fclose(studentDepartment);
    fclose(studentPasswords);
    fclose(studentIntern);
    fclose(studentGrades);
    fclose(studentLectures);
    fclose(studentAffairPassword);
    fclose(numberOfLecturers);
    fclose(lecturerNames);
    fclose(lecturerIds);
    fclose(lecturerPasswords);
    fclose(lecturerLectures);
    fclose(adminPasswordF);
}

void WriteEverythingToFile(students student[], lecturers lecturer[], int studentCount, int lecturerCount, char studentAfPassword[], char adminPassword[])
{
    char tempAdminPassword[20] = "\0";
    char tempStudentAfPassword[20] = "\0";
    char tempStudentPasswords[20] = "\0";

    studentCheck = fopen("studentCheck.txt", "w");
    numberOfStudents = fopen("numberOfStudents.txt", "w");
    studentNames = fopen("studentNames.txt", "w");
    studentNumbers = fopen("studentNumbers.txt", "w");
    studentDepartment = fopen("studentDepartment.txt", "w");
    studentPasswords = fopen("studentPasswords.txt", "w");
    studentIntern = fopen("studentIntern.txt", "w");
    studentGrades = fopen("studentGrades.txt", "w");
    studentLectures = fopen("studentLectures.txt", "w");
    studentAffairPassword = fopen("studentAffairPassword.txt", "w");
    numberOfLecturers = fopen("numberOfLecturers.txt", "w");
    lecturerNames = fopen("LecturerNames.txt", "w");
    lecturerIds = fopen("LecturerIds.txt", "w");
    lecturerPasswords = fopen("LecturerPasswords.txt", "w");
    lecturerLectures = fopen("LecturerLectures.txt", "w");
    adminPasswordF = fopen("adminPassword.txt", "w");

    encryptCesar(adminPassword);
    strcpy(tempAdminPassword, adminPassword);
    encryptCesar(studentAfPassword);
    fprintf(adminPasswordF, "%s\n", tempAdminPassword);
    fprintf(studentAffairPassword, "%s\n", studentAfPassword);
    for (int i = 0; i < studentCount; i++)
    {
        fprintf(studentIntern, "%d\n", student[i].intern);
        fprintf(studentCheck, "%d\n", student[i].check);
        fprintf(studentDepartment, "%s\n", student[i].department);
        fprintf(studentNames, "%s\n", student[i].name);
        fprintf(studentNumbers, "%d\n", student[i].number);
        strcpy(tempStudentPasswords, student[i].password);
        fprintf(studentGrades, "%d %d %d %d\n", student[i].grades[0], student[i].grades[1], student[i].grades[2], student[i].grades[3]);
        fprintf(studentLectures, "%s %s %s %s\n", student[i].lectures[0], student[i].lectures[1], student[i].lectures[2], student[i].lectures[3]);
        encryptCesar(tempStudentPasswords);
        fprintf(studentPasswords, "%s\n", tempStudentPasswords);
    }
    fprintf(numberOfStudents, "%d\n", studentCount);

    fprintf(numberOfLecturers, "%d\n", lecturerCount);
    for (int i = 0; i < lecturerCount; i++)
    {
        fprintf(lecturerNames, "%s\n", lecturer[i].name);
        fprintf(lecturerIds, "%s\n", lecturer[i].id);
        fprintf(lecturerPasswords, "%s\n", lecturer[i].password);
        fprintf(lecturerLectures, "%s %s %s\n", lecturer[i].lectures[0], lecturer[i].lectures[1], lecturer[i].lectures[2]);
    }

    fclose(studentCheck);
    fclose(adminPasswordF);
    fclose(numberOfStudents);
    fclose(studentNames);
    fclose(studentNumbers);
    fclose(studentDepartment);
    fclose(studentPasswords);
    fclose(studentIntern);
    fclose(studentGrades);
    fclose(studentLectures);
    fclose(studentAffairPassword);
    fclose(numberOfLecturers);
    fclose(lecturerNames);
    fclose(lecturerIds);
    fclose(lecturerLectures);
    fclose(lecturerPasswords);
}
