#include "bettyFixer.h"

bettyError *Errors[100]; /* Can't have more than 100 errors. */

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
        exit(EXIT_FAILURE);
    }
    /* In the parent process*/
    wait(&status);
    /* Print for testing */
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>I am in the parent process\n");
    close(pipeFd[1]);

    parseBettyOutput(pipeFd);

    close(pipeFd[0]);
    readWrite(fileName);

    return (1);
}

void parseBettyOutput(int pipeFd[2])
{
    char c;
    char line[1024] = {0};
    int charsRead = 0, totalCharsRead = 0, lineCount = 0;
    int i = 0;
    bettyError *error;

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

                error = tokenizeErrorLine(line);
                if (error && error->errorType)
                {
                    Errors[i] = error;
                    /* Printing for testing */
                    printf("\n\tFileName:%s_", Errors[i]->fileName);
                    printf("\n\tlineNumber: %d", Errors[i]->lineNumber);
                    printf("\n\terrorType: %s", Errors[i]->errorType);
                    printf("\n\terrorMessage: %s", Errors[i]->errorMessage);
                    i++;
                }
                /* Empty the line buffer */
                memset(line, 0, sizeof(line));
            }
        }
    }
    if (lineCount == 2)
    {
        fprintf(stderr, "File does not exist!\n");
        /* Free error */
        exit(EXIT_FAILURE);
    }
    // fixError(lineCount, Errors);
    printf("\nline Count = %d\n", lineCount);

    printf("Outside");
    write(1, line, strlen(line));
}

/**
 * tokenizeErrorLine - a function to tokenize each betty error message
 * @line: the error message/line to be tokenized
 * Return: a data structure (bettyError) containing
 * the different components of the error message
 */
bettyError *tokenizeErrorLine(char line[1024])
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
            token = strtok(NULL, ":");
        }

        if (token != NULL)
        {
	    printf("token before: %s=\n", token);
            error->lineNumber = atoi(&token[1]);
	    printf("DEBUG: converted line number: %d\n", error->lineNumber);
            token = strtok(NULL, ":");
        }

        if (token != NULL)
        {
            error->errorType = strdup(token);
            strcat(error->errorType, "\0");
            token = strtok(NULL, ":");
        }

        if (token != NULL)
        {
            error->errorMessage = strdup(token);
            strcat(error->errorMessage, "\0");
        }

        return error;
    }
    return NULL;
}

/**
 * readWrite - a function to read and rewrite a file with modifications
 * @fileName: file to be read
 * Return: 1 for success, otherwise -1
 */

int readWrite(char *fileName)
{
	FILE *filePtr, *tempFile;
	int lineCounter = 0;
	bettyError **errorPtr;
	char buffer[1024];
	char *modifiedLine;

	filePtr = fopen(fileName, "r");
	if (filePtr == NULL)
	{
		perror("fopen");
		return (-1);
	}

	tempFile = fopen("tmp.c", "w");
	if (tempFile == NULL)
	{
		fclose(filePtr);
		perror("fopen");
		return(-1);
	}

	errorPtr = Errors;
	while (fgets(buffer, 1024, filePtr) != NULL)
	{
		lineCounter++;
		if (lineCounter == (*errorPtr)->lineNumber)
		{
			modifiedLine = strdup(checkErrorMessage(buffer));
			fputs(modifiedLine, tempFile);
			free (modifiedLine);
			errorPtr++;
		}
		else
			fputs(buffer, tempFile);
	}



	fclose(tempFile);
	fclose(filePtr);

	return(1);
}

/**
 * checkErrorMessage - a function to check tne betty error messages for a match
 * and carry out the corresponding action
 * @buffer: line to be compared to the error message
 * Return: modified line
 */

char * checkErrorMessage(char buffer[])
{
	return ("This line has an error");
}
