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
	char line[MAX_LINE_LENGTH];
	int lineCount = 0;
	int j = 0;

	/* Initialize Global Errors Array. */
	/* initializeErrorsArray(); */

	/* Duplicate stdin as read end of pipe. */
	dup2(pipeFd[0], STDIN_FILENO);

	/* Read from stdin (pipe) line by line. */
	while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL)
	{
		/* Keep track of line number. */
		lineCount++;
		
		/* Tokenize line starting from line 3. */
		if (lineCount > 2)
		{
			/* Replace newline character at the end of the line. */
			line[strlen(line) - 1] = '\0';
			bettyError *error = tokenizeErrorLine(line);

			/* Set tokenized line as one of the structures in Erors array. */
			if (error != NULL)
			{
				Errors[j] = error;
				j++;
			}
		}
	}
	if (!Errors[0])
		exit(EXIT_SUCCESS);
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
	char *token;

	/* Allocate memory for error struct. */
	bettyError *error = malloc(sizeof(bettyError));
	/* Handle memory allocation failure. */
	if (error == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	/**
	 * Tokenize the line with : as the delimeter
	 * split the line into file name, line number,
	 * error type and error message itself.
	 */
	if (line)
	{
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
	free(error);
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
	char buffer[MAX_LINE_LENGTH];
	char *modifiedLine, *result;

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
	/* Set pointer to the start of the Errors array. */
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
	remove(fileName);
	rename("tmp.c", fileName);

	return (1);
}
