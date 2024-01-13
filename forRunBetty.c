#include "bettyFixer.h"

bettyError *Errors[100]; /* Can't have more than 100 errors. */

/**
* parseBettyOutput - a function to parse the output of runBetty on a file
* @pipeFd: the output to be parsed
*/

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
				line[strlen(line)] = c;
			}
			else
			{
				line[strlen(line)] = '\0';
				write(1, line, strlen(line));
				error = tokenizeErrorLine(line);
				if (error)
				{
					Errors[i] = error;
					/* Printing for testing */
					printf("\n\tFileName:%s, %ld_", Errors[i]->fileName,
							strlen(Errors[i]->fileName));
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
		/* Free error */
		exit(EXIT_FAILURE);
	}
	printf("\nline Count = %d\n", lineCount);
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
	char *modifiedLine, *result;

	printf("\n\nIN READWRITE FUNCTION\n");

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
		return (-1);
	}
	errorPtr = Errors;
	while ((result = fgets(buffer, 1024, filePtr)) != NULL)
	{
		lineCounter++;
		printf("result - %s, LineCounter -> %d\n", result, lineCounter);
		if (lineCounter == (*errorPtr)->lineNumber)
		{
			modifiedLine = checkErrorMessage((*errorPtr)->errorMessage, buffer);
			fputs(modifiedLine, tempFile);
			free(modifiedLine);
			errorPtr++;
		}
		else
			fputs(buffer, tempFile);
	}
	printf("Out\n");
	fclose(tempFile);
	fclose(filePtr);

	/* Delete Original Source File */
	/**
	* remove(fileName);
	* rename("tmp.c", fileName);
	*
	* printf("Successfully rwrote the lines that have errors!\n");
	*/
	return (1);
}
