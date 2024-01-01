#include "bettyFixer.h"

/**
 * createPipe - Creates a new pipe.
 * @pipeFd: Array of integers to store the file descriptors of the new pipe.
 *
 * Return: void.
 */
void createPipe(int pipeFd[])
{
    /* Create a pipe. */
    if (pipe(pipeFd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

/**
 * runBetty - Runs betty on a file and writes the output to the stdout (Needs some work)
 * @ fileName: The name of the file to run betty on
 *
 * Return: 1 on success, else -1
 */
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