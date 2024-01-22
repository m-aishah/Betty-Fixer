#include "bettyFixer.h"

/**
* fixBettyError - Fix betty errors in a file.
* to the stdout (Needs some work)
* @fileName: The name of the file to run betty on
*
* Return: 1 on success, else -1
*/
int fixBettyError(char *fileName)
{
	int pipeFd[2], pid, status;

	/* Create a pipe. */
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
		/* Run betty on file. */
		execlp("betty", "betty", fileName, NULL);
		perror("exec");
		exit(EXIT_FAILURE);
	}
	/* In the parent process. */
	wait(&status);
	close(pipeFd[1]);
	/* Parse output of running betty that is stored in pipe. */
	parseBettyOutput(pipeFd);
	close(pipeFd[0]);
	/* Fix error messages in the file. */
	correctAndReplaceFile(fileName);
	/* Free structure array. */
	freeError();
	return (1);
}
