#include "file.h"

char* fileRead (char* filePath){
    /* Open file and find size */
    FILE* file = fopen (filePath, "r");
    fseek (file, 0, SEEK_END);
    long fileSize = ftell (file);
    rewind (file);

    /* Allocate memory and read to string */
    char* string = malloc(fileSize + 1);
    fread (string, fileSize, 1, file);
    fclose (file);

    /* Null terminate string */
    string[fileSize] = 0;

    return string;
}
