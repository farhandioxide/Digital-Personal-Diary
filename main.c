#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//colors
#define RED      "\033[31m"
#define GREEN    "\033[32m"
#define YELLOW   "\033[33m"
#define BLUE     "\033[34m"
#define MAGENTA  "\033[35m"
#define CYAN     "\033[36m"
#define RESET    "\033[0m"

#define USERFILE "user.txt"

//func. prototypes [A]

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

// main func.

int main() {
    int choice;
    char cchoice;

    printf(CYAN "=== Personal Diary Program ===\n" RESET);

    // Signup and Login 
    while (1) {
        printf(YELLOW "\n1. Signup\n" RESET);
        printf(YELLOW "2. Login\n" RESET);
        printf(YELLOW "3. Exit\n" RESET);
        printf(MAGENTA "Choose: " RESET);
        scanf("%d", &choice);
        clearInput();

        if (choice == 1) signup();
        else if (choice == 2) {
            if (login()) break;
            else printf(RED "\nLogin failed. Try again.\n" RESET);
        }
        else exit(0);
    }

    // MEnu after login 
    while (1) {
        printf(CYAN "\n=== Diary Menu ===\n" RESET);
        printf(YELLOW "A. Add Entry\n" RESET);
        printf(YELLOW "V. View Entries\n" RESET);
        printf(YELLOW "S. Search Entry\n" RESET);
        printf(YELLOW "E. Edit Entry\n" RESET);
        printf(YELLOW "D. Delete Entry\n" RESET);
        printf(YELLOW "X. Export Entries\n" RESET);
        printf(YELLOW "Q. Quit\n" RESET);
        printf(MAGENTA "Choose: " RESET);
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
            default: printf(RED "Invalid option.\n" RESET);
        }
    }

    return 0;
}

//--------------------
//func. definitions
//sign up func [F]

void signup() {
    FILE *fp = fopen(USERFILE, "a");
    char user[30], pass[30];

    if (!fp) {
        printf(RED "Error creating user file.\n" RESET);
        return;
    }

    printf(MAGENTA "\nCreate username: " RESET);
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = 0;

    printf(MAGENTA "Create password: " RESET);
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0;

    fprintf(fp, "%s %s\n", user, pass);
    fclose(fp);

    printf(GREEN "Signup successful!\n" RESET);
}

//login func.

int login() {
    FILE *fp = fopen(USERFILE, "r");
    if (!fp) {
        printf(RED "No user registered. Please signup first.\n" RESET);
        return 0;
    }

    char storedUser[30], storedPass[30];
    char user[30], pass[30];

    printf(MAGENTA "\nEnter username: " RESET);
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = '\0';

    printf(MAGENTA "Enter password: " RESET);
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';

    while (fscanf(fp, "%29s %29s", storedUser, storedPass) == 2) {
        if (strcmp(user, storedUser) == 0 && strcmp(pass, storedPass) == 0) {
            strcpy(currentUser, user);
            fclose(fp);
            printf(GREEN "\nLogin successful!\n" RESET);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

//---------------
// ADD Entry func. [S]

void addEntry() {
    char filename[50];
    sprintf(filename, "%s_diary.txt", currentUser);

    FILE *fp = fopen(filename, "a");
    if (!fp) {
        printf(RED "Error opening diary file.\n" RESET);
        return;
    }

    char date[20], title[50], content[500], line[200];

    printf(MAGENTA "\nEnter date (DD/MM/YYYY): " RESET);
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = 0;

    printf(MAGENTA "Enter title: " RESET);
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    printf(MAGENTA "Write content (end with a single line containing only ~):\n" RESET);

    content[0] = '\0';
    while (1) {
        fgets(line, sizeof(line), stdin);
        if (strcmp(line, "~\n") == 0) break;
        strcat(content, line);
    }

    fprintf(fp, "DATE: %s\nTITLE: %s\nCONTENT:\n%s---\n",
            date, title, content);
    fclose(fp);

    printf(GREEN "Entry added.\n" RESET);
}

//View Entry function

void viewEntries() {
    char filename[50];
    sprintf(filename, "%s_diary.txt", currentUser);

    FILE *fp = fopen(filename, "r");
    char line[600];
    int current = 0;

    if (!fp) {
        printf(RED "No entries found.\n" RESET);
        return;
    }

    printf(CYAN "\n=== All Entries ===\n\n" RESET);

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "DATE:")) {
            current++;
            printf(YELLOW "\n=== Entry #%d ===\n" RESET, current);
        }
        printf("%s", line);
    }

    if (current == 0)
        printf(RED "No entries available.\n" RESET);

    fclose(fp);
}

// search Entry func.

void searchEntry() {
    char filename[50];
    sprintf(filename, "%s_diary.txt", currentUser);

    FILE *fp = fopen(filename, "r");
    char line[600];
    int found = 0, target, current = 0;

    if (!fp) {
        printf(RED "No entries.\n" RESET);
        return;
    }

    printf(MAGENTA "Enter entry number to search: " RESET);
    scanf("%d", &target);
    clearInput();

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "DATE:")) {
            current++;
            if (current == target) {
                found = 1;
                printf(YELLOW "\n=== Entry #%d ===\n" RESET, target);
                printf("%s", line);
                while (fgets(line, sizeof(line), fp)) {
                    printf("%s", line);
                    if (strstr(line, "---")) break;
                }
                break;
            }
        }
    }

    if (!found)
        printf(RED "No entry found with that number.\n" RESET);

    fclose(fp);
}

// Edit entry func.

void editEntry() {
    char filename[50];
    sprintf(filename, "%s_diary.txt", currentUser);

    FILE *fp = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    char line[600];
    int found = 0, target, current = 0;

    if (!fp || !temp) {
        printf(RED "File error.\n" RESET);
        return;
    }

    printf(MAGENTA "Enter entry number to edit: " RESET);
    scanf("%d", &target);
    clearInput();

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "DATE:")) {
            current++;
            if (current == target) {
                found = 1;

                char date[50], newTitle[50], newContent[500];
                strcpy(date, line + 6);
                date[strcspn(date, "\n")] = 0;

                printf(MAGENTA "New title: " RESET);
                fgets(newTitle, sizeof(newTitle), stdin);
                newTitle[strcspn(newTitle, "\n")] = 0;

                printf(MAGENTA "New content (end with ~):\n" RESET);
                newContent[0] = '\0';
                char l[200];
                while (1) {
                    fgets(l, sizeof(l), stdin);
                    if (strcmp(l, "~\n") == 0) break;
                    strcat(newContent, l);
                }

                fprintf(temp,
                        "DATE: %s\nTITLE: %s\nCONTENT:\n%s---\n",
                        date, newTitle, newContent);

                while (fgets(line, sizeof(line), fp))
                    if (strstr(line, "---")) break;

                continue;
            }
        }
        fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    if (found)
        printf(GREEN "Entry updated successfully.\n" RESET);
    else
        printf(RED "No entry found with that number.\n" RESET);
}

//DELETE entry func.

void deleteEntry() {
    char filename[50];
    sprintf(filename, "%s_diary.txt", currentUser);

    FILE *fp = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    char line[600];
    int found = 0, target, current = 0;

    if (!fp || !temp) {
        printf(RED "File error.\n" RESET);
        return;
    }

    printf(MAGENTA "Enter entry number to delete: " RESET);
    scanf("%d", &target);
    clearInput();

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "DATE:")) {
            current++;
            if (current == target) {
                found = 1;

                printf(YELLOW "\n=== Entry #%d ===\n" RESET, target);
                printf("%s", line);
                while (fgets(line, sizeof(line), fp)) {
                    printf("%s", line);
                    if (strstr(line, "---")) break;
                }

                char confirm;
                printf(RED "Are you sure you want to delete this entry? (Y/N): " RESET);
                scanf(" %c", &confirm);
                clearInput();
                if (toupper(confirm) == 'Y') {
                    printf(GREEN "Entry deleted.\n" RESET);
                    continue;
                } else {
                    fseek(fp, -strlen(line), SEEK_CUR);
                    current--;
                }
            }
        }
        fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    if (!found)
        printf(RED "No entry found with that number.\n" RESET);
}

//-----------
//Export Entry func. [f] 

void exportEntries() {
    char filename[50], exportFile[50];
    sprintf(filename, "%s_diary.txt", currentUser);
    sprintf(exportFile, "%s_export.txt", currentUser);

    FILE *fp = fopen(filename, "r");
    FILE *out = fopen(exportFile, "w");
    char line[600];
    int current = 0;

    if (!fp || !out) {
        printf(RED "File error.\n" RESET);
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "DATE:")) current++;
        fprintf(out, "%s", line);
    }

    fclose(fp);
    fclose(out);

    printf(GREEN "All entries exported to '%s'\n" RESET, exportFile);
}

//--------------
