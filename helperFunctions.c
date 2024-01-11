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
 * freeError - a function to free Error
 */

void freeError(void)
{
	bettyError *ptr;
	int i = 0;

	while (Errors[i])
	{
		ptr = Errors[i];
		free(ptr->fileName);
		free(ptr->errorType);
		free(ptr->errorMessage);
		free(ptr);
		i++;
	}

	/* free(Errors); */
}

/**
 * checkErrorMessage - a function to check tne betty error messages for a match
 * and carry out the corresponding action
 * @errorMessage: betty error message to be checked
 * @buffer: line to be compared to the error message
 * Return: modified line
 */

char *checkErrorMessage(char *errorMessage, char buffer[])
{
	if (strcmp(errorMessage, " trailing whitespace") == 0)
	{
		/*trailingWhiteSpace(buffer)*/
		return (removeTrailingWhitespaces(buffer));
	}
	return ("This line has an error\n");
}
