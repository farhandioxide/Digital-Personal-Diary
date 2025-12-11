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

char currentUser[30];  // Store the logged-in username

int main() {
    int choice;
    char cchoice;

    printf("=== Personal Diary Program ===\n");

    // Signup/Login loop
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

    // Logged-in main menu with shortcuts
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
