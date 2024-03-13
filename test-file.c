#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILES 100

typedef struct{
    char title[50];
    char author[50];
    char publicationYear[50];
    char price[50];
}Book;

typedef struct{
    char filename[50];
}File;

typedef struct{
    char filename[50];
    char updateadd[50];
}Update;

typedef struct{
    char filename[50];
}Remove;

char fileNames[MAX_FILES][100];
int fileCount = 0;

void createFile(){
    system("cls");

    Book book;
    printf("\nEnter title: ");
    scanf("%s", book.title);
    printf("Enter author: ");
    scanf("%s", book.author);
    printf("Enter year published: ");
    scanf("%s", book.publicationYear);
    printf("Enter price: ");
    scanf("%s", book.price);

    char filename[100];
    sprintf(filename, "%s-%s.txt", book.title, book.author);

    char fileWithExtension[100];
    sprintf(fileWithExtension, "%s.txt", filename);

    FILE* file = fopen(fileWithExtension, "w");
    if (file == NULL){
        printf("Unable to create the file.\n");
        return;
    }

    strcpy(fileNames[fileCount], filename);
    fileCount++;

    fprintf(file, "Title: %s\n", book.title);
    fprintf(file, "Author: %s\n", book.author);
    fprintf(file, "Year Published: %s\n", book.publicationYear);
    fprintf(file, "Price: %s\n", book.price);

    puts("");
    printf("File '%s' created successfully.\n", filename);
    puts("");

    fclose(file);

    FILE* filenamesFile = fopen("filenames.txt", "a");
    if(filenamesFile == NULL){
        printf("Unable to open the filenames file.\n");
        return;
    }

    fprintf(filenamesFile, "%s\n", filename);

    fclose(filenamesFile);
}

void loadFileNames(){
    FILE* filenamesFile = fopen("filenames.txt", "r");
    if(filenamesFile == NULL){
        return;
    }

    char filename[100];
    while (fgets(filename, sizeof(filename), filenamesFile) != NULL) {
        strtok(filename, "\n"); // Remove the newline character
        strcpy(fileNames[fileCount], filename);
        fileCount++;
    }

    fclose(filenamesFile);
}

void updateFile() {
    system("cls");

    printf("\nEnter filename: ");
    char filename[50];
    scanf("%s", filename);

    char fileWithExtension[50];
    sprintf(fileWithExtension, "%s.txt", filename);

    FILE* file = fopen(fileWithExtension, "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    Book book;
    // Read the existing book details
    fscanf(file, "Title: %[^\n]\n", book.title);
    fscanf(file, "Author: %[^\n]\n", book.author);
    fscanf(file, "Year Published: %[^\n]\n", book.publicationYear);
    fscanf(file, "Price: %[^\n]\n", book.price);

    fclose(file);

    int choice;
    printf("\nSelect the field to update:\n");
    printf("1. Title\n");
    printf("2. Author\n");
    printf("3. Year Published\n");
    printf("4. Price\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter the new title: ");
            scanf("%s", book.title);
            break;
        case 2:
            printf("Enter the new author: ");
            scanf("%s", book.author);
            break;
        case 3:
            printf("Enter the new year published: ");
            scanf("%s", book.publicationYear);
            break;
        case 4:
            printf("Enter the new price: ");
            scanf("%s", book.price);
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }

    char newFileWithExtension[50];
    sprintf(newFileWithExtension, "%s-%s.txt", book.title, book.author);

    // Rename the existing file
    if (rename(fileWithExtension, newFileWithExtension) != 0) {
        printf("Unable to rename the file.\n");
        return;
    }

    printf("File updated successfully.\n");

    // Update the filename in the list
    int i;
    for (i = 0; i < fileCount; i++) {
        if (strcmp(fileNames[i], fileWithExtension) == 0) {
            strcpy(fileNames[i], newFileWithExtension);
            break;
        }
    }
}


void readFile() {
    system("cls");

    printf("\nEnter filename: ");
    char filename[50];
    scanf("%s", filename);

    char fileWithExtension[50];
    sprintf(fileWithExtension, "%s.txt", filename);

    FILE* file = fopen(fileWithExtension, "r");

    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    printf("\nFile contents:\n");

    int c;
    while ((c = fgetc(file)) != EOF) {
        printf("%c", c);
    }

    fclose(file);
}

void removeFile(){
    system("cls");

    printf("\nEnter filename: ");
    char filename[50];
    scanf("%s", filename);
	int counter;
	
    char fileWithExtension[50];
    sprintf(fileWithExtension, "%s.txt", filename);

    if(remove(fileWithExtension) == 0){
        printf("File removed successfully.\n");

        FILE* filenamesFile = fopen("filenames.txt", "w");
        if (filenamesFile == NULL) {
            printf("Unable to open the filenames file.\n");
            return;
        }

        for(counter = 0; counter < fileCount; counter++){
            if(strcmp(fileNames[counter], filename) != 0){
                fprintf(filenamesFile, "%s\n", fileNames[counter]);
            }
        }

        fclose(filenamesFile);
    }else{
        printf("Unable to remove the file.\n");
    }
}

void renameFile(){
    system("cls");
	
	int counter;
	
    printf("\nEnter the current filename: ");
    char currentFilename[50];
    scanf("%s", currentFilename);

    char currentFileWithExtension[50];
    sprintf(currentFileWithExtension, "%s.txt", currentFilename);

    printf("Enter the new filename: ");
    char newFilename[50];
    scanf("%s", newFilename);

    char newFileWithExtension[50];
    sprintf(newFileWithExtension, "%s.txt", newFilename);

    FILE* currentFile = fopen(currentFileWithExtension, "r");

    if (currentFile == NULL){
        printf("Unable to open the current file.\n");
        return;
    }

    FILE* newFile = fopen(newFileWithExtension, "w");

    if (newFile == NULL){
        printf("Unable to create the new file.\n");
        fclose(currentFile);
        return;
    }

    int c;
    while ((c = fgetc(currentFile)) != EOF) {
        fputc(c, newFile);
    }

    fclose(currentFile);
    fclose(newFile);

    if (remove(currentFileWithExtension) == 0) {
        printf("File renamed successfully.\n");

        FILE* filenamesFile = fopen("filenames.txt", "w");
        if (filenamesFile == NULL) {
            printf("Unable to open the filenames file.\n");
            return;
        }

        for (counter = 0; counter < fileCount; counter++) {
            if (strcmp(fileNames[counter], currentFilename) == 0) {
                strcpy(fileNames[counter], newFilename);
            }
            fprintf(filenamesFile, "%s\n", fileNames[counter]);
        }

        fclose(filenamesFile);
    } else {
        printf("Unable to rename the file.\n");
    }
}

void displayBookContent() {
    system("cls");

    if (fileCount == 0) {
        printf("\nNo files.\n");
        return;
    }

    printf("\nBook Content:\n");

    int counter;
    for (counter = 0; counter < fileCount; counter++) {
        printf("\nBook #%d\n", counter + 1);

        char fileWithExtension[100];
        sprintf(fileWithExtension, "%s.txt", fileNames[counter]);

        FILE* file = fopen(fileWithExtension, "r");

        if (file == NULL) {
            printf("Unable to open the file: %s\n", fileNames[counter]);
            continue;
        }

        Book book;

        fscanf(file, "Title: %[^\n]\n", book.title);
        fscanf(file, "Author: %[^\n]\n", book.author);
        fscanf(file, "Year Published: %[^\n]\n", book.publicationYear);
        fscanf(file, "Price: %[^\n]\n", book.price);

        printf("Title: %s\n", book.title);
        printf("Author: %s\n", book.author);
        printf("Year Published: %s\n", book.publicationYear);
        printf("Price: %s\n", book.price);

        fclose(file);
    }

    printf("\n");
    system("pause");
}


int main(){
    loadFileNames();

    int choice;

    while (1) {
        system("cls");

        puts("[===============================]");
        puts("[ C R U D R D E ]");
        puts("[===============================]");
        puts(" | |");
        puts(" | 1. Create a file |");
        puts(" | 2. Read a file |");
        puts(" | 3. Update a file |");
        puts(" | 4. Delete a file |");
        puts(" | 5. Rename a file |");
        puts(" | 6. Display book contents |");
        puts(" | 7. Exit |");
        puts(" | |");
        puts(" |_____________________________|");
        printf("\n Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createFile();
                system("pause");
                break;
            case 2:
                readFile();-
                system("pause");
                break;
            case 3:
                updateFile();
                system("pause");
                break;
            case 4:
                removeFile();
                system("pause");
                break;
            case 5:
                renameFile();
                system("pause");
                break;
            case 6:
            	displayBookContent();
            	system("pause");
            	break;
            case 7:
                printf("\nExiting program...\n");
                system("pause");
                exit(0);
            default:
                system("pause");
                printf("\nInvalid choice.\n");
        }
    }

    return 0;
}