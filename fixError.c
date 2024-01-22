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
		return (removeTrailingWhitespaces(buffer));
	
	/* Check if error is code indent error. */
	else if (strcmp(errorMessage, " code indent should use tabs where possible") == 0)
		return (fixIndent(buffer));

	else if(strcmp(errorMessage, " please, no spaces at the start of a line") == 0)
		return(fixIndent(buffer));
	
	/* Check if error is space required before parenthesis. */
	else if (strcmp(errorMessage, " space required before the open parenthesis '('") == 0)
		return (fixSpaceBeforeBracket(buffer));
	
	/* Check if error is spaces around operators. */
	else if (strstr(errorMessage, " spaces required around that") != NULL)
		return(addSpacesAroundOperators(buffer));
	
	else if (strstr(errorMessage, " spaces preferred around that") != NULL)
		return(addSpacesAroundOperators(buffer));
	
	/* Check if error is missing line after declaration error. */
	else if (strcmp(errorMessage, " Missing a blank line after declarations") == 0)
		return(addLineAfterDeclaration(buffer));
	
	return (NULL);
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
		return (NULL);
	
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
		perror("malloc");
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
		return (NULL);
	
	/* Get the length of the string. */
	len = strlen(orgStr);

	/* Allocate memory to store corrected string. */
	correctedStr = (char *)malloc(len + indent);
	/* Handle memory allocation failure. */
	if (correctedStr == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	/* Get index of first non-space or tab character. */
	while (orgStr[orgIndx] == ' ' || orgStr[orgIndx] == '\t')
		orgIndx++;

	/* Add required number of tabs (indent) to start of correctedString. */
	for (i = 0; i < indent; i++)
		correctedStr[correctedIndx++] = '\t';
	
	/* Copy the rest of orgString into the correctedString. */
	while (orgIndx < len)
		correctedStr[correctedIndx++] = orgStr[orgIndx++];

	return (correctedStr);
}

char *fixSpaceBeforeBracket(const char *str)
{
	int modStrIndex, strIndex, len;
	char *modifiedStr;
	if (str == NULL)
		return (NULL); /* Handle NULL input string. */

	len = strlen(str);
	modifiedStr = (char *)malloc((len * 1.5) * sizeof(char *));
	if (modifiedStr == NULL)
	{
		return (NULL); /* Memory Allocation Failed. */
	}	
	
	modStrIndex = 0;
	strIndex = 0;
/**
	while (strIndex < len)
	{
		modifiedStr[modStrIndex] = str[strIndex];
		modStrIndex++;
		strIndex++;
		if (str[strIndex] != ' ' && strIndex + 1 < len && str[strIndex + 1] == '(')
			modifiedStr[modStrIndex] = ' ';
	}
*/
	for (int strIndex = 0; strIndex < len; strIndex++)
	{
		modifiedStr[modStrIndex++] = str[strIndex];
		if (strIndex + 1 < len && str[strIndex] != ' ' && str[strIndex + 1] == '(')
		{
			modifiedStr[modStrIndex++] = ' ';
		}
	}
	return (modifiedStr);

}
