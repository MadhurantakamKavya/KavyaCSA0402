#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>   // for _mkdir on Windows
#include <errno.h>    // for perror()

int main() {
    char mainDirectory[] = "C:\\Users\\itssk\\OneDrive\\Desktop";
    char subDirectory[] = "os";
    char fileName[] = "example.txt";
    char mainDirPath[300];
    char filePath[400];

    // Build full folder path
    snprintf(mainDirPath, sizeof(mainDirPath), "%s\\%s", mainDirectory, subDirectory);

    // Create the directory (if it doesn’t exist)
    if (_mkdir(mainDirPath) == -1 && errno != EEXIST) {
        perror("Error creating directory");
        return 1;
    }

    // Build the full file path
    snprintf(filePath, sizeof(filePath), "%s\\%s", mainDirPath, fileName);

    // Create or open file
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }

    fprintf(file, "This is an example file content.\n");
    fclose(file);

    printf("? File created successfully at:\n%s\n", filePath);
    return 0;
}


