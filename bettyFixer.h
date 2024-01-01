#ifndef BETTYFIXER_H
#define BETTYFIXER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int runBetty(char *);
void createPipe(int[]);

#endif