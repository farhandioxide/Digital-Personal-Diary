#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define USERFILE "user.txt"

void signup();
int login();
void addEntry();
void viewEntries();
void searchEntry();
void editEntry();
void deleteEntry();
void exportEntries();
void clearInput() { while (getchar() != '\n'); }

char currentUser[30];  

int main() {
    int choice;
    char cchoice;

    printf("=== Personal Diary Program ===\n");

// sign up and login 
    while (1) {
        printf("\n1. Signup\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        clearInput();

        if (choice == 1) signup();
        else if (choice == 2) {
            if (login()) break;
            else printf("\nLogin failed. Try again.\n");
        }
        else exit(0);
    }

 //diary menu
    while (1) {
        printf("\n=== Diary Menu ===\n");
        printf("A. Add Entry\n");
        printf("V. View Entries\n");
        printf("S. Search Entry\n");
        printf("E. Edit Entry\n");
        printf("D. Delete Entry\n");
        printf("X. Export Entries\n");
        printf("Q. Quit\n");
        printf("Choose: ");
        scanf(" %c", &cchoice);
        clearInput();
        cchoice = toupper(cchoice);

        switch (cchoice) {
            case 'A': addEntry(); break;
            case 'V': viewEntries(); break;
            case 'S': searchEntry(); break;
            case 'E': editEntry(); break;
            case 'D': deleteEntry(); break;
            case 'X': exportEntries(); break;
            case 'Q': exit(0);
            default: printf("Invalid option.\n");
        }
    }

    return 0;
}

//functions

//sign up

void signup() {
    FILE *fp = fopen(USERFILE, "a");  
    char user[30], pass[30];

    if (!fp) {
        printf("Error creating user file.\n");
        return;
    }

    printf("\nCreate username: ");
    getchar();
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = 0;

    printf("Create password: ");
    getchar();
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0;

    fprintf(fp, "%s %s\n", user, pass);  
    fclose(fp);

    printf("Signup successful!\n");
}

// login 

int login() {
    FILE *fp = fopen(USERFILE, "r");
    if (!fp) {
        printf("No user registered. Please signup first.\n");
        return 0;
    }

    char storedUser[30], storedPass[30];
    char user[30], pass[30];

    printf("\nEnter username: ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = '\0';

    printf("Enter password: ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';

    while (fscanf(fp, "%29s %29s", storedUser, storedPass) == 2) {
        if (strcmp(user, storedUser) == 0 && strcmp(pass, storedPass) == 0) {
            strcpy(currentUser, user);
            fclose(fp);
            printf("\nLogin successful!\n");
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// entry func...--->
