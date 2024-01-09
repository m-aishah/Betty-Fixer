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

struct bettyError
{
    char *fileName;
    int lineNumber;
    char *errorType;
    char *errorMessage;
};

typedef struct bettyError bettyError;

extern bettyError *Errors[100]; /* Can't have more than 100 errors. */
int runBetty(char *);
void parseBettyOutput(int[]);
bettyError *tokenizeErrorLine(char[]);

void createPipe(int[]);
/* int removeTrailingWhitespaces(const char *fileName); */
int readWrite(char *);
char *checkErrorMessage(char *, char[]);

/* Functions to fill error messages. */
char *removeTrailingWhitespaces(const char *);

#endif
