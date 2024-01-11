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
bettyError *tokenizeErrorLine(char[]);

int runBetty(char *);
int readWrite(char *);

void freeError();
void createPipe(int[]);
void parseBettyOutput(int[]);

/* Functions to fill error messages. */
char *checkErrorMessage(char *, char[]);
char *removeTrailingWhitespaces(const char *);

#endif
