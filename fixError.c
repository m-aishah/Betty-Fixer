#include "bettyFixer.h"
int indent = 1;

/**
 * checkErrorMessage - Check error message and
 *					call required function to fix it.
 * @errorMessage: Error message to be checked.
 * @buffer: The string/line with the problem to be fixed.
 *
 * Return: The modified line.
 */
char *checkErrorMessage(char *errorMessage, char buffer[])
{
	/* Check if error is trailing whitespace error. */
	if (strcmp(errorMessage, " trailing whitespace") == 0)
	{
		return (removeTrailingWhitespaces(buffer));
	}
	/* Check if error is code indent error. */
	else if (errorMessage, " code indent should use tabs where possible")
	{
		return (fixIndent(buffer));
	}
	return ("This line has an error\n");
}

/**
* removeTrailingWhitespaces - Removes trailing whitespaces from a string.
* @str: The string in question.
*
* Return: The corrected string.
*/
char *removeTrailingWhitespaces(const char *orgStr)
{
	int length, lastNonWhitespaceIndex;
	char *correctedStr;

	/* Handle NULL input string. */
	if (orgStr == NULL)
	{
		return (NULL);
	}

	/* Get the length of the string. */
	length = strlen(orgStr);

	/* Find the index of the last non-whitespace character. */
	lastNonWhitespaceIndex = length - 1;

	while (lastNonWhitespaceIndex >= 0 && isspace(orgStr[lastNonWhitespaceIndex]))
	{
		lastNonWhitespaceIndex--;
	}

	/* Allocate memory for the corrected string. */
	correctedStr = (char *)malloc(lastNonWhitespaceIndex + 1);

	if (correctedStr == NULL)
	{
		return (NULL); /* Memory allocation failed */
	}

	/* Copy the non-whitespace portion of the string to the new buffer. */
	strncpy(correctedStr, orgStr, lastNonWhitespaceIndex + 1);
	correctedStr[lastNonWhitespaceIndex + 1] = '\n';

	return (correctedStr);
}

/**
 * fixIndent - Adds necessaary indent to the beginning of a string.
 * @orgStr: The string in question
 *
 * Return: Returns a pointer to the corrected String.
 */
char *fixIndent(const char *orgStr)
{
	int i, len;
	int orgIndx = 0;
	int  correctedIndx = 0;
	char *correctedStr;

	/* Handle NULL input string. */
	if (orgStr == NULL)
	{
		return (NULL);
	}

	/* Get the length of the string. */
	len = strlen(orgStr);

	/* Allocate memory to store corrected string. */
	correctedStr = (char *)malloc(len + indent);
	/* Handle memory allocation failure. */
	if (correctedStr == NULL)
	{
		return (NULL);
	}

	/* Get index of first non-space or tab character. */
	while (orgStr[orgIndx] == ' ' || orgStr[orgIndx] == '\t')
		orgIndx++;

	/* Add required number of tabs (indent) to start of correctedString. */
	for (i = 0; i < indent; i++)
	{
		correctedStr[correctedIndx++] = '\t';
	}

	/* Copy the rest of orgString into the correctedString. */
	while (orgIndx < len)
		correctedStr[correctedIndx++] = orgStr[orgIndx++];

	return (correctedStr);
}
