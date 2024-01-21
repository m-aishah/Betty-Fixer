#include "bettyFixer.h"

/**
 * main - Entry point.
 * @argc: The number of arguments.
 * @argv: Arguments
 *
 * Return: 0 on success, else 1.
 */
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <file_name>\n", argv[0]);
		return (1);
	}
	fixBettyError(argv[1]);
	return (0);
}


/**
 * Future Updates: - updates we plan to implement
 * Implement running on multiple files.
 * Implement doc errors (for now we are taking care
 * of just betty syntax lint errors)
 * Use threads to increase speed.
 */
