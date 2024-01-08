#include "bettyFixer.h"

int removeTrailingWhitespaces(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("fopen");
        return(-1);
    }

    // Read content from the file
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *content = malloc(fileSize + 1);
    if (content == NULL) {
        perror("malloc");
        fclose(file);
        return(-1);
    }

    fread(content, 1, fileSize, file);
    content[fileSize] = '\0';

    fclose(file);

    // Remove trailing whitespaces
    char *end = content + fileSize - 1;
    while (end > content && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        *end-- = '\0';
    }

    // Write the modified content back to the file
    FILE *outputFile = fopen(fileName, "w");
    if (outputFile == NULL) {
        perror("fopen");
        free(content);
        return(-1);
    }

    fputs(content, outputFile);

    fclose(outputFile);
    free(content);
return(0);
}
