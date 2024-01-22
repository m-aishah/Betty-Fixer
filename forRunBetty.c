#include "bettyFixer.h"

bettyError *Errors[100]; /* Can't have more than 100 errors. */

/**
* parseBettyOutput - Parse error messages from betty in a pipe.
* @pipeFd: Pipe file descriptor arrays (where errors are to be read from).
*
* Return: void.
*/
void parseBettyOutput(int pipeFd[2])
{
	char c;
	char line[1024] = {0};
	int charsRead = 0, totalCharsRead = 0, lineCount = 0;
	int i = 0;
	bettyError *error;

	/* Read error from pipe character by character. */
	while ((charsRead = read(pipeFd[0], &c, 1)) > 0)
	{
		/* Keep count of each line. */
		// Need to use an alternative way of reading each line. This is not fullproof.
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
				/* Store each line in the line buffer. */
				line[strlen(line)] = '\0';
				/* Tokenize each line into respective parts. */
				error = tokenizeErrorLine(line);
				/* Store tokeized error into errors array. */
				if (error)
				{
					Errors[i] = error;
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
* tokenizeErrorLine - Tokenize each line of betty error message.
* @line: The error message/line to be tokenized.
*
* Return: a data structure (bettyError) containing
*			the different components of the error message.
*/
bettyError *tokenizeErrorLine(char line[1024])
{
	bettyError *error;
	char *token;

	/**
	 * Tokenize the line with : as the delimeter
	 * split the line into file name, line number,
	 * error type and error message itself.
	 */
	if (line[0] != 0)
	{
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
			error->lineNumber = atoi(token);
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

/**
* correctAndReplaceFile - Rewrites a file with modifications.
* @fileName: Th enam eof the file to be read.
*
* Return: 1 for success, otherwise -1
*/
int correctAndReplaceFile(char *fileName)
{
	FILE *filePtr, *tempFile;
	int lineCounter = 0;
	bettyError **errorPtr;
	char buffer[1024];
	char *modifiedLine, *result;

//	printf("\n\nIN READWRITE FUNCTION\n");
//	int i;
//	for (i = 0; i < 6; i++)
//	{
//		printf("\nLineNumber: %d\n", Errors[i]->lineNumber);
//	}
	/*Open the file */
	filePtr = fopen(fileName, "r");
	if (filePtr == NULL)
	{
		perror("fopen"); /* Handle fopen error. */
		return (-1);
	}

	/* Open temporary file for writing. */
	tempFile = fopen("tmp.c", "w");
	if (tempFile == NULL)
	{
		fclose(filePtr);
		perror("fopen");
		return (-1);
	}
	errorPtr = Errors;
	/* Read each line from the file. */
	while ((result = fgets(buffer, 1024, filePtr)) != NULL)
	{
		lineCounter++;
		/* Check that the current line does not have an error. */
		if (lineCounter == (*errorPtr)->lineNumber)
		{
			/* If there is an error. */
			/* Make a copy of the line with the error. */
			char bufferCopy[1024];

			strcpy(bufferCopy, buffer);

			/* Apply modifications for each error on the line. */
			while ((*errorPtr)->lineNumber == lineCounter)
			{
				modifiedLine = checkErrorMessage((*errorPtr)->errorMessage, bufferCopy);
				if (modifiedLine)
				{
					/* Update the copy for the next iteration. */
					strcpy(bufferCopy, modifiedLine);
					/* Free the memory for the modified line. */
					free(modifiedLine);
				}
				/* Move to the next error */
				errorPtr++;
			}
			/* Write corrected line into temporary file. */
			fputs(bufferCopy, tempFile);
		}
		else
			/**
			 * If there is no error,
			 * write the line dirrectly into temp file.
			 */
			fputs(buffer, tempFile);
		/* Update the indent variable if necessary. */
		updateIndent(buffer);
	}
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
