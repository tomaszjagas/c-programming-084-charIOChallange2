#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void convertCase(FILE *fptr, const char *path);

int main() {
    // file pointer to hold reference of input file
    FILE *fptr = NULL;
    char path[100];

    printf("Enter path of source file: ");
    scanf("%s", path);

    fptr = fopen(path, "r");

    // fopen() return NULL if unable to open file
    if (fptr == NULL) {
        // unable to open file - exit
        printf("\nUnable to open file.\n");
        printf("Please check if file exists.\n");
        exit(EXIT_FAILURE);
    }

    convertCase(fptr, path);

    return 0;
}

void convertCase(FILE *fptr, const char *path) {
    FILE *dest = NULL;
    char ch = '\0';

    // temporary file to store result
    dest = fopen("temp.txt", "w");

    // if unable to create temporary file
    if (dest == NULL) {
        printf("Unable to create temporary file.");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    // repeat till the end of file
    while ((ch = fgetc(fptr)) != EOF) {
        // if current character is uppercase toggle is to lowercase and viceversa
        if (isupper(ch)) {
            ch = tolower(ch);
        }
        else if (islower(ch)) {
            ch = toupper(ch);
        }

        // print toggled character to destination file
        fputc(ch, dest);
    }

    // close all files
    fclose(fptr);
    fclose(dest);

    // delete original source file
    remove(path);

    // rename temporary file as original file
    rename("temp.txt", path);
}