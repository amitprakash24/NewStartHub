#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define MAX_LENGTH 100
#define MAX_ENROLLMENTS 100

// File paths
#define ENTREPRENEURS_FILE "entrepreneurs.txt"
#define INVESTORS_FILE "investors.txt"
#define ENROLLMENTS_FILE "enrollments.txt"
#define EOF (-1)
// Data structure for entrepreneurs
struct Entrepreneur
{
    int ID;
    char businessType[MAX_LENGTH];
    char address[MAX_LENGTH];
    char phoneNumber[MAX_LENGTH];
    char pinCode[MAX_LENGTH];
};

// Data structure for investors
struct Investor
{
    int ID;
    char name[MAX_LENGTH];
    char address[MAX_LENGTH];
    char phoneNumber[MAX_LENGTH];
    char pinCode[MAX_LENGTH];
};

// Data structure for enrollment
struct Enrollment
{
    int enrollmentID;
    int entrepreneurID;
    int investorID;
    char investorName[MAX_LENGTH];
    char submissionDate[MAX_LENGTH];
};

// Function prototypes Entrepreneur
void addEntrepreneur();
void viewEntrepreneurs();
void editEntrepreneur();

// Function prototypes Investor
void addInvestor();
void viewInvestors();
void editInvestor();

// Function prototypes Enrollment
void addEnrollment();
void viewEnrollments();

// Function prototypes Search Enrollment
void binarySearchEnrollment();

//Generate Report
void generateReports();

void addEnrollmentToArray(struct Enrollment enrollment);
struct Enrollment enrollments[MAX_ENROLLMENTS];
// File operations
FILE *openFile(char *filePath, char *mode);
void closeFile(FILE *file);
int getNextID(char *filePath);
int enrollmentCount = 0;

int main()
{
    int choice;
    bool flag=true;
    while(flag)
    {

        printf("\n Admin Dashboard \n");
        printf("1. Add Entrepreneurs\n");
        printf("2. View Entrepreneurs\n");
        printf("3. Edit Entrepreneurs\n");
        printf("4. Add Investors\n");
        printf("5. View Investors\n");
        printf("6. Edit Investors\n");
        printf("7. Add Enrollment\n");
        printf("8. View Enrollment\n");
        printf("9.Generate Reports\n");
        printf("10.Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        printf(" your select option %d\n",choice);

        switch (choice)
        {
        case 1:
            addEntrepreneur();
            break;
        case 2:
            viewEntrepreneurs();
            break;
        case 3:
            editEntrepreneur();
            break;
        case 4:
            addInvestor();
            break;
        case 5:
            viewInvestors();
            break;
        case 6:
            editInvestor();
            break;
        case 7:
            addEnrollment();
            break;
        case 8:
            viewEnrollments();
            break;
        case 9:
            generateReports();
            break;
        case 10:
            printf("Exiting program.\n");
            flag=false;
            break;
        default:
            printf("Invalid choice. Please try again.\n");

        }//end of Switch case
    }//end of while

    return 0;
}//end of main

void addEntrepreneur()
{
    struct Entrepreneur entrepreneur;
    entrepreneur.ID = getNextID(ENTREPRENEURS_FILE);
    printf("\nEnter Entrepreneur Details\n");
    printf("Business Type: ");
    scanf("%s", entrepreneur.businessType);
    printf("Address: ");
    scanf("%s", entrepreneur.address);
    printf("Phone Number: ");
    scanf("%s", entrepreneur.phoneNumber);
    printf("Pin Code: ");
    scanf("%s", entrepreneur.pinCode);

    FILE *file = openFile(ENTREPRENEURS_FILE, "a");
    fprintf(file, "%d %s %s %s %s\n", entrepreneur.ID, entrepreneur.businessType, entrepreneur.address,
            entrepreneur.phoneNumber, entrepreneur.pinCode);
    closeFile(file);

    printf("Entrepreneur added successfully!\n");
}// end of addEntrepreneur Function


void viewEntrepreneurs()
{
    FILE *file = openFile(ENTREPRENEURS_FILE, "r");

    printf("\nEntrepreneurs List\n");
    printf("ID  Business Type  Address  Phone Number  Pin Code\n");

    struct Entrepreneur entrepreneur;
    while (fscanf(file, "%d %19s %49s %14s %9s", &entrepreneur.ID, entrepreneur.businessType, entrepreneur.address,
                  entrepreneur.phoneNumber, entrepreneur.pinCode) !=EOF)
    {
        printf("%-4d%-15s%-10s%-15s%-10s\n", entrepreneur.ID, entrepreneur.businessType, entrepreneur.address,
               entrepreneur.phoneNumber, entrepreneur.pinCode);
    }//end of while

    closeFile(file);
}//end of ViewEntrepreneur function



void editEntrepreneur()
{
    int idToEdit;
    printf("Enter Entrepreneur ID to edit:");
    scanf("%d", &idToEdit);

    FILE *inputFile = openFile(ENTREPRENEURS_FILE, "r");
    FILE *outputFile = openFile("temp.txt", "w");

    struct Entrepreneur entrepreneur;
    int found = 0;

    while (fscanf(inputFile, "%d %s %s %s %s", &entrepreneur.ID, entrepreneur.businessType, entrepreneur.address,
                  entrepreneur.phoneNumber, entrepreneur.pinCode) !=EOF)
    {
        if (entrepreneur.ID == idToEdit)
        {
            found = 1;
            printf("\nEnter new details for Entrepreneur ID %d\n", idToEdit);
            printf("Business Type: ");
            scanf("%s", entrepreneur.businessType);
            printf("Address: ");
            scanf("%s", entrepreneur.address);
            printf("Phone Number: ");
            scanf("%s", entrepreneur.phoneNumber);
            printf("Pin Code: ");
            scanf("%s", entrepreneur.pinCode);
        }
        fprintf(outputFile, "%d %s %s %s %s\n", entrepreneur.ID, entrepreneur.businessType, entrepreneur.address,
                entrepreneur.phoneNumber, entrepreneur.pinCode);
    }//end of while

    closeFile(inputFile);
    closeFile(outputFile);

    remove(ENTREPRENEURS_FILE);
    rename("temp.txt", ENTREPRENEURS_FILE);

    if (found)
    {
        printf("Entrepreneur details updated successfully!\n");
    }
    else
    {
        printf("Entrepreneur with ID %d not found.\n", idToEdit);
    }
}// end of editEntrepreneur Function

void addInvestor()
{
    struct Investor investor;
    investor.ID = getNextID(INVESTORS_FILE);

    printf("\nEnter Investor Details\n");
    printf("Name: ");
    scanf("%s", investor.name);
    printf("Address: ");
    scanf("%s", investor.address);
    printf("Phone Number: ");
    scanf("%s", investor.phoneNumber);
    printf("Pin Code: ");
    scanf("%s", investor.pinCode);

    FILE *file = openFile(INVESTORS_FILE, "a");
    fprintf(file, "%d %s %s %s %s\n", investor.ID, investor.name, investor.address, investor.phoneNumber, investor.pinCode);
    closeFile(file);

    printf("Investor added successfully!\n");
}// end of addInvestor function

void viewInvestors()
{
    FILE *file = openFile(INVESTORS_FILE, "r");

    printf("\nInvestors List\n");
    printf("ID  Name  Address  Phone Number  Pin Code\n");

    struct Investor investor;
    while (fscanf(file, "%d %s %s %s %s", &investor.ID, investor.name, investor.address, investor.phoneNumber, investor.pinCode)==5 || !feof(file))
    {
        printf("%-4d%-10s%-10s%-15s%-10s\n", investor.ID, investor.name, investor.address, investor.phoneNumber, investor.pinCode);
    }//end of while

    closeFile(file);
}//end of viewInvestors Function

void editInvestor()
{
    int idToEdit;
    printf("Enter Investor ID to edit: ");
    scanf("%d", &idToEdit);

    FILE *inputFile = openFile(INVESTORS_FILE, "r");
    FILE *outputFile = openFile("temp.txt", "w");

    struct Investor investor;
    int found = 0;

    while (fscanf(inputFile, "%d %s %s %s %s", &investor.ID, investor.name, investor.address, investor.phoneNumber, investor.pinCode) !=EOF)
    {
        if (investor.ID == idToEdit)
        {
            found = 1;
            printf("\nEnter new details for Investor ID %d\n", idToEdit);
            printf("Name: ");
            scanf("%s", investor.name);
            printf("Address: ");
            scanf("%s", investor.address);
            printf("Phone Number: ");
            scanf("%s", investor.phoneNumber);
            printf("Pin Code: ");
            scanf("%s", investor.pinCode);
        }//end of while
        fprintf(outputFile, "%d %s %s %s %s\n", investor.ID, investor.name, investor.address, investor.phoneNumber, investor.pinCode);
    }

    closeFile(inputFile);
    closeFile(outputFile);

    remove(INVESTORS_FILE);
    rename("temp.txt", INVESTORS_FILE);

    if (found)
    {
        printf("Investor details updated successfully!\n");
    }
    else
    {
        printf("Investor with ID %d not found.\n", idToEdit);
    }
}// end of editInvestor function

void addEnrollment()
{
    struct Enrollment enrollment;
    enrollment.enrollmentID = getNextID(ENROLLMENTS_FILE);

    printf("\nEnter Enrollment Details\n");
    printf("Entrepreneur ID: ");
    scanf("%d", &enrollment.entrepreneurID);
    printf("Investor ID: ");
    scanf("%d", &enrollment.investorID);
    printf("Investor Name: ");
    scanf("%s", enrollment.investorName);

    // Get current date and time
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    strftime(enrollment.submissionDate, sizeof(enrollment.submissionDate), "%Y-%m-%d %H:%M", localTime);
    addEnrollmentToArray(enrollment);
    FILE *file = openFile(ENROLLMENTS_FILE, "a");
    fprintf(file, "%d %d %d %s %s\n", enrollment.enrollmentID, enrollment.entrepreneurID, enrollment.investorID,
            enrollment.investorName, enrollment.submissionDate);
    closeFile(file);

    printf("Enrollment added successfully!\n");
}//end of addEnrollment Function


void viewEnrollments()
{
    binarySearchEnrollment();

}// end of viewEnrollments function

void binarySearchEnrollment()
{
    int targetID;
    printf("Enter Enrollment ID to search: ");
    scanf("%d", &targetID);

    FILE *file = openFile(ENROLLMENTS_FILE, "r");

    struct Enrollment enrollment;
    int found = 0;

    while (fscanf(file, "%d %d %d %s %s", &enrollment.enrollmentID, &enrollment.entrepreneurID, &enrollment.investorID,
                  enrollment.investorName, enrollment.submissionDate) == 5)
    {

        if (enrollment.enrollmentID == targetID)
        {
            found = 1;
            printf("\n-----------------------Enrollment Details-----------------------\n");
            printf("Enrollment ID  Entrepreneur ID  Investor ID  Investor Name  Submission Date\n");
            printf("%-15d%-19d%-12d%-15s%s\n", enrollment.enrollmentID, enrollment.entrepreneurID, enrollment.investorID,
                   enrollment.investorName, enrollment.submissionDate);
            break;
        }
    }//end of while

    if (!found)
    {
        printf("Enrollment with ID %d not found.\n", targetID);
    }

    closeFile(file);
}//end of binarySearchEnrollment function

void addEnrollmentToArray(struct Enrollment enrollment)
{

    if (enrollmentCount < MAX_ENROLLMENTS)
    {
        enrollments[enrollmentCount] = enrollment;
        enrollmentCount++;
    }
    else
    {
        printf("Maximum number of enrollments reached. Cannot add more.\n");
    }
}
//decelear the function to genrate report
void generateReports()
{
    struct Enrollment enrollment;
    FILE *file = openFile(ENROLLMENTS_FILE, "r");
    int i ;
    printf("\n--------------------- Enrollment Report ---------------------\n");
    printf("Enrollment ID  Entrepreneur ID  Investor ID  Investor Name  Submission Date\n");



    while (fscanf(file, "%d %d %d %s %s", &enrollment.enrollmentID, &enrollment.entrepreneurID, &enrollment.investorID,
                  enrollment.investorName, enrollment.submissionDate) ==5)
    {

        printf("%-15d%-19d%-12d%-15s%s\n", enrollment.enrollmentID, enrollment.entrepreneurID, enrollment.investorID,
               enrollment.investorName, enrollment.submissionDate);
    }//end of while
// Display enrollment details
    for (i= 0; i < enrollmentCount; i++)
    {
        struct Enrollment enrollment = enrollments[i];
        printf("%-15d%-19d%-12d%-15s%s\n", enrollment.enrollmentID, enrollment.entrepreneurID, enrollment.investorID,
               enrollment.investorName, enrollment.submissionDate);

    }// end of generateReports Function


}


// Function to open a file
FILE *openFile(char *filePath, char *mode)
{
    FILE *file = fopen(filePath, mode);
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return file;
}//end of file

// Function to close a file
void closeFile(FILE *file)
{
    fclose(file);
}

// Function to get the next available ID for a record
int getNextID(char *filePath)
{
    FILE* file = openFile(filePath, "r");
    int id = 1; // Default starting ID
    if (file != NULL)
    {
        fseek(file, 0, SEEK_END);
        if (ftell(file) != 0)
        {
            rewind(file);
            fscanf(file, "%*d"); // Skip the first field (ID)
            while (fscanf(file, "%*s") ==5 || !feof(file))
            {
                id++;
            }
        }
    }

    closeFile(file);

    return id;
}//end of genNextID Function
