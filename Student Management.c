#include <stdio.h>
#include <stdlib.h>

void addStudent();
void displayStudentRecords();
void deleteStudent();
void examination();

int main() 
{
    int choice;
    
    while (1) {
        printf("\n=====STUDENT DATABASE MANAGEMENT SYSTEM=====");
        printf("\n\t     1. Add Student");
        printf("\n\t     2. Display Records");
        printf("\n\t     3. Delete Student");
        printf("\n\t     4. Examination");
        printf("\n\t     5. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudentRecords();
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                examination();
                break;
            case 5:
                printf("\n\tThank you!\n");
                exit(0);
            default:
                printf("\n\tEnter a valid number!\n");
                break;
        }
    }
    return 0;
}

void addStudent() 
{
    FILE *fp;
    char first_name[20], last_name[20], Course[10], city[20];
    int roll_no;
    float grade;

    fp = fopen("information.txt", "a");
    
    if (fp == NULL) 
    {
        fprintf(stderr, "Can't open file\n");
        return;
    }
    
    printf("=======Add Student Info=======");
    char t[100];
    printf("\n\tEnter First Name  : ");
    scanf("%s", first_name);
    printf("\tEnter Last Name   : ");
    scanf("%s", last_name);
    printf("\tEnter Roll-No     : ");
    scanf("%d", &roll_no);
    printf("\tEnter Course      : ");
    scanf("%s", Course);
    printf("\tEnter City        : ");
    scanf("%s", city);
    grade=0.0; 
    sprintf(t,"%s,%s,%d,%s,%s,%d\n",first_name,last_name,roll_no,Course,city,grade);
    fputs(t,fp);
    fclose(fp);
    printf("\n\tRecord stored successfully!\n");
}

void displayStudentRecords() 
{
    FILE *fp;
    char first_name[20], last_name[20], Course[10], city[20];
    int roll_no;
    float grade;
    
    fp = fopen("information.txt", "r");
    
    if (fp == NULL) {
        fprintf(stderr, "Can't open file\n");
        return;
    }
    
    printf("=======Student Records=======\n");
    while (fscanf(fp, "%[^,],%[^,],%d,%[^,],%[^,],%f\n", first_name, last_name, &roll_no, Course, city, &grade) != EOF) 
    {
        printf("Name: %s %s\n",first_name,last_name);
        printf("Roll no: %d\n",roll_no);
        printf("Course: %s\n",Course);
        printf("City: %s\n",city);
        printf("Grade: %.2f\n\n",grade);
    }
    fclose(fp);
}

void deleteStudent() 
{
    FILE *fp, *temp_fp;
    char first_name[20], last_name[20], Course[10], city[20];
    int roll_no;
    float grade;
    int delete_roll_no;
    int found = 0;

    fp = fopen("information.txt", "r");
    temp_fp = fopen("temp.txt", "w");

    if (fp == NULL || temp_fp == NULL) {
        fprintf(stderr, "Can't open file\n");
        return;
    }

    printf("=======Delete Student Record=======\n");
    printf("Enter the roll number of the student to delete: ");
    scanf("%d", &delete_roll_no);

    while (fscanf(fp, "%[^,],%[^,],%d,%[^,],%[^,],%f\n", first_name, last_name, &roll_no, Course, city, &grade) == 6) {
        if (roll_no == delete_roll_no) {
            found = 1;
        } else {
            fprintf(temp_fp, "%s,%s,%d,%s,%s,%.2f\n", first_name, last_name, roll_no, Course, city, grade);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (!found) {
        printf("Record not found for roll number: %d\n", delete_roll_no);
    } else {
        remove("information.txt");
        rename("temp.txt", "information.txt");
        printf("Record deleted successfully for roll number: %d\n", delete_roll_no);
    }
}

void examination() 
{
    FILE *fp, *temp_fp;
    char first_name[20], last_name[20], Course[10], city[20];
    int roll_no;
    float grade;
    int roll_no_to_change;
    int found = 0;
    fp = fopen("information.txt", "r");
    temp_fp = fopen("temp.txt", "w");

    if (fp == NULL || temp_fp == NULL) {
        fprintf(stderr, "Can't open file\n");
        return;
    }

    printf("=======Examination Portal=======\n");
    printf("Enter the roll number of the student to change grades: ");
    scanf("%d", &roll_no_to_change);

    while (fscanf(fp, "%[^,],%[^,],%d,%[^,],%[^,],%f\n", first_name, last_name, &roll_no, Course, city, &grade) == 6) 
    {
        if (roll_no == roll_no_to_change) 
        {
            found = 1;
            int n;
            printf("Enter no of subjects:");
            scanf("%d",&n);
            int marks[n],tot=0;
            for (int i=0;i<n;i++)
            {
                printf("Enter marks for Subject %d:",i+1);
                scanf("%d",&marks[i]);
                tot+=(int)(marks[i]/10)+1;
            }
            grade=(float)tot/n;
        }
        fprintf(temp_fp, "%s,%s,%d,%s,%s,%.2f\n", first_name, last_name, roll_no, Course, city, grade);
    }

    fclose(fp);
    fclose(temp_fp);

    if (found==0) 
         printf("Record not found for roll number: %d\n", roll_no_to_change);
    else 
    {
        remove("information.txt");
        rename("temp.txt", "information.txt");
        printf("Grades updated successfully for roll number: %d\n", roll_no_to_change);
    }
}
