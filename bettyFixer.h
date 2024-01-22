#ifndef BETTYFIXER_H
#define BETTYFIXER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024

/**
 * struct bettyError - Container for each line of a betty error.
 * @fileName: The name of the file with the error.
 * @lineNumber: The line number the error is on.
 * @errorType: Tpe of error (WARNING/ ERROR).
 * @errorMessage: The error message itself.
 *
 * Description: Use this struct to store parts that make up a line of betty error.
 */
struct bettyError
{
    char *fileName;
    int lineNumber;
    char *errorType;
    char *errorMessage;
};

typedef struct bettyError bettyError;

extern bettyError *Errors[100]; /* Can't have more than 100 errors. */
extern int indent;

int fixBettyError(char *);

void parseBettyOutput(int[]);
bettyError *tokenizeErrorLine(char[]);
int correctAndReplaceFile(char *);

/* Helper Functions. */
void freeError(void);
void createPipe(int[]);
int updateIndent(char []);
void initializeErrorsArray(void);

/* Functions to Fix Error Messages. */
char *checkErrorMessage(char *, char[]);
char *removeTrailingWhitespaces(const char *);
char *fixIndent(const char *);
char *fixSpaceBeforeBracket(const char *);
char *addSpacesAroundOperators(const char *);
char *addLineAfterDeclaration(const char *);

#endif
