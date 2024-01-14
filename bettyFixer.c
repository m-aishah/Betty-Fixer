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
