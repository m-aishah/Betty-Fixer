#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int runBetty(char *fileName);
void createPipe(int[]);

/**
 * Future Updates:
 * Implement running on multiple files.
 * Implement doc errors (for now we are taking care of just betty syntax lint errors)
 */

/**
 * main - Entry point.
 * @argc: The number of arguments.
 * @argv: Arguments
 * Returns: 0 on success.
 */

int main(int argc, char *argv[])
{
    int pid, status;
    int pipeFd[2];
    if (argc < 2)
    {
        printf("Usage: %s <file_name>\n", argv[0]);
        return (1);
    }

    runBetty(argv[1]);

    return (0);
}

int runBetty(char *fileName)
{
    int pipeFd[2], pid, status;

    createPipe(pipeFd);

    /* Run betty in a new process. */
    pid = fork();
    if (pid < 0)
    {
        /* Close pipe if fork failed. */
        close(pipeFd[0]);
        close(pipeFd[1]);

        perror("fork");
        return (-1);
    }

    if (pid == 0)
    {
        close(pipeFd[0]);
        /* Duplicate stdout as pipe write file descriptor.*/
        dup2(pipeFd[1], STDOUT_FILENO);
        close(pipeFd[1]);

        execlp("betty", "betty", fileName, NULL);

        perror("exec");
        return (-1);
    }
    /* In the parent process*/
    wait(&status);
    /* Print for testing */
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>I am in the parent process\n");
    close(pipeFd[1]);

    /* Read read form pipe into buffer and write from buffer to the stdout. */
    char buff[1024];
    size_t charsRead;
    while (charsRead = read(pipeFd[0], buff, 1024))
    {
        write(STDOUT_FILENO, buff, charsRead);
    }

    return (1);
}

void createPipe(int pipeFd[])
{
    /* Create a pipe. */
    if (pipe(pipeFd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}