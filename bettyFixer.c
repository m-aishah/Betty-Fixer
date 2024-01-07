#include "bettyFixer.h"

bettyError *tokenize(char[]);

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

    char c;
    int charsRead = 0, totalCharsRead = 0, lineCount = 0;
    char line[1024] = {0};
    int i = 0;
    bettyError *error;
    bettyError *Errors[100]; /* Can't have more than 100 errors. */

    while ((charsRead = read(pipeFd[0], &c, 1)) > 0)
    {
        if (c == '\n')
            lineCount++;

        if (lineCount > 1)
        {
            if (c != '\n')
            {
                strcat(line, &c);
            }
            else
            {
                printf("\n>>>>>>>>>>>>>>>>>>>>>Line %d>>>>>\n", lineCount);
                write(1, line, strlen(line));

                error = tokenize(line);
                if (error && (strcmp(error->fileName, "total") != 0))
                {
                    Errors[i] = error;
                    /* Printing for testing */
                    printf("\n\tFileName: %s", Errors[i]->fileName);
                    printf("\n\tlineNumber: %s", Errors[i]->lineNumber);
                    printf("\n\terrorType: %s", Errors[i]->errorType);
                    printf("\n\terrorMessage: %s", Errors[i]->errorMessage);
                    i++;
                }
                /* Empty the line buffer */
                memset(line, 0, sizeof(line));
            }
        }
    }

    printf("Outside");
    write(1, line, strlen(line));
    close(pipeFd[0]);

    return (1);
}

/**
 * tokenize - a function to tokenize each betty error message
 * @line: the error message/line to be tokenized
 * Return: a data structure (bettyError) containing
 * the different components of the error message
 */

bettyError *tokenize(char line[1024])
{
    bettyError *error;
    char *token;

    if (line[0] != 0)
    {
        printf("\n\tIn tokenize function: end%s\n", line);
        error = malloc(sizeof(bettyError));
        token = strtok(line, ":");
        if (token != NULL)
        {
            error->fileName = strdup(token);
            strcat(error->fileName, "\0");
            // printf("\n The fileName: %s\n", error->fileName);
            token = strtok(NULL, ":");
        }

        if (token != NULL)
        {
            error->lineNumber = strdup(token);
            strcat(error->lineNumber, "\0");
            // printf("\n The LineNumber: %s\n", error->lineNumber);
            token = strtok(NULL, ":");
        }

        if (token != NULL)
        {
            error->errorType = strdup(token);
            strcat(error->errorType, "\0");
            // printf("\n The errorType: %s\n", error->errorType);
            token = strtok(NULL, ":");
        }

        if (token != NULL)
        {
            error->errorMessage = strdup(token);
            strcat(error->errorMessage, "\0");
            // printf("\n The errorMessage: %s\n", error->errorMessage);
        }

        return error;
    }
    return NULL;
}
