#include "bettyFixer.h"

/**
 * removeTrailingWhitespaces - a function to remove trailing
 * whitespaces in a given file
 * @fileName: file to be modified
 * Return: 0 on success, -1 otherwise
 */

int removeTrailingWhitespaces(const char *fileName)
{
	char buffer[1024];
	size_t bytesRead, index;
	FILE *file, *tempFile, *outputFile;

	file = fopen(fileName, "r");
	if (file == NULL)
	{
		perror("fopen");
		return (-1);
	}

	tempFile = tmpfile(); /* A temp file for writing modified content */
	if (tempFile == NULL)
	{
		perror("tmpfile");
		fclose(file);
		return (-1);
	}

	while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0)
	{
		index = bytesRead - 1;
		while (index > 0 && (buffer[index] == ' ' || buffer[index] == '\t'
					|| buffer[index] == '\r'))
			index--;

	fwrite(buffer, 1, index + 1, tempFile);
	}

	rewind(tempFile);

	outputFile = fopen(fileName, "w");
	if (outputFile == NULL)
	{
		perror("fopen");
		fclose(file);
		fclose(tempFile);
		return(-1);
	}

	while ((bytesRead = fread(buffer, 1, sizeof(buffer), tempFile)) > 0) {
        fwrite(buffer, 1, bytesRead, outputFile);
    }

    fclose(file);
    fclose(tempFile);
    fclose(outputFile);
    return(0);
}
