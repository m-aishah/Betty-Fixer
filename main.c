#include "bettyFixer.h"

/**
 * Future Updates:
 * Implement running on multiple files.
 * Implement doc errors (for now we are taking care of just betty syntax lint errors)
 */

/**
 * main - Entry point.
 * @argc: The number of arguments.
 * @argv: Arguments
 * Returns: 0 on success.
 */

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <file_name>\n", argv[0]);
        return (1);
    }

    runBetty(argv[1]);

    return (0);
}