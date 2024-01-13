#include "bettyFixer.h"

bettyError *Errors[100]; /* Can't have more than 100 errors. */

/**
* runBetty - Runs betty on a file and writes the output
* to the stdout (Needs some work)
* @fileName: The name of the file to run betty on
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
	close(pipeFd[1]);

	parseBettyOutput(pipeFd);
	close(pipeFd[0]);
	readWrite(fileName);
	freeError();
	return (1);
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
			printf("token before:%s, len= %ld\n", token, strlen(token));
			error->lineNumber = atoi(token);
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
		return (error);
	}
	return (NULL);
}
