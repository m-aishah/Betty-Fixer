#include "bettyFixer.h"
int indent = 1;

/**
 * checkErrorMessage - a function to check tne betty error messages for a match
 * and carry out the corresponding action
 * @errorMessage: betty error message to be checked
 * @buffer: line to be compared to the error message
 * Return: modified line
 */

char *checkErrorMessage(char *errorMessage, char buffer[])
{
	if (strcmp(errorMessage, " trailing whitespace") == 0)
	{
		return (removeTrailingWhitespaces(buffer));
	}
	else if (errorMessage, " code indent should use tabs where possible")
	{
		return (fixIndent(buffer));
	}
	return ("This line has an error\n");
}

/**
* removeTrailingWhitespaces - a function to remove trailing whitespaces
* from a string
* @str: input string
* Return: formatted string
*/
char *removeTrailingWhitespaces(const char *str)
{
	int length, lastNonWhitespaceIndex;

	if (str == NULL)
	{
		return (NULL); /* Handle NULL input string */
	}
	length = strlen(str);

	/* Find the index of the last non-whitespace character */
	lastNonWhitespaceIndex = length - 1;

	while (lastNonWhitespaceIndex >= 0 && isspace(str[lastNonWhitespaceIndex]))
	{
		lastNonWhitespaceIndex--;
	}
	
	/* Allocate memory for the corrected string */
	char *correctedStr = (char *)malloc(lastNonWhitespaceIndex + 1);
	if (correctedStr == NULL)
	{
		return (NULL); /* Memory allocation failed */
	}

	/* Copy the non-whitespace portion of the string to the new buffer */
	strncpy(correctedStr, str, lastNonWhitespaceIndex + 1);
	correctedStr[lastNonWhitespaceIndex + 1] = '\n';

	return (correctedStr);
}

char *fixIndent(const char *orgStr)
{
	int i, len;
	int orgIndx = 0;
	int  correctedIndx = 0;
	char *correctedStr;

	if (orgStr == NULL)
	{
		return (NULL); /* Handle NULL input string. */
	}

	len = strlen(orgStr);

	correctedStr = (char *)malloc(len + indent);
	if (correctedStr == NULL)
	{
		return (NULL); /* Memory Allocation Failed. */
	}

	while (orgStr[orgIndx] == ' ' || orgStr[orgIndx] == '\t')
		orgIndx++;

	for ( i = 0; i < indent; i++)
	{
		correctedStr[correctedIndx++] = '\t';
	}

	while(orgIndx < len)
		correctedStr[correctedIndx++] = orgStr[orgIndx++];

	return (correctedStr);
}
