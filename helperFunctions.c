#include "bettyFixer.h"

bettyError *Errors[100]; /* Can't have more than 100 errors. */
int indent;

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
 * freeError - a function to free Errors (array of structures).
 */
void freeError(void)
{
	bettyError *ptr;
	int i = 0;

	/* Free each element of each structure in the Errors Array. */
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
 * updateIndent - Updates the indent variable.
 *		to keep track of the number of tabs for required on a line.
 * @buffer: The line.
 * Return: The number of ndents for the line.
 */
int updateIndent(char buffer[])
{
	int i, len;
	const char *keys[] = {"for", "while", "if", "else", "switch", "case"};

	len = sizeof(keys) / sizeof(keys[0]);

	for (i = 0; i < len; i++)
	{
		if (strstr(buffer, keys[i]) != NULL)
			indent++;
	}

	if (strchr(buffer, '}') != NULL)
		indent--;

	return (indent);
}


void initializeErrorsArray() {
    for (int i = 0; i < 100; ++i) {
       Errors[i] = NULL;
    }
}
