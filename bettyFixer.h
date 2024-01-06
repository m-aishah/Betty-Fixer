#ifndef BETTYFIXER_H
#define BETTYFIXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct bettyError
{
    char *fileName;
    char *lineNumber;
    char *errorType;
    char *errorMessage;
};

typedef struct bettyError bettyError;

int runBetty(char *);
void parseBettyOutput(int[]);
bettyError *tokenizeErrorLine(char[]);

void createPipe(int[]);

#endif