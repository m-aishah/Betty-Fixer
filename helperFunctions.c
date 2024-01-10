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
 * freeError - a function to free Error
 */

void freeError()
{
	bettyError *ptr;
	int i = 0;

	while (Errors[i])
	{
		ptr = Errors[i];
		free (ptr->fileName);
		free (ptr->errorType);
		free (ptr->errorMessage);
		free (ptr);
		i++;
	}

	// free (Errors);
}
