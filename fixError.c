#include "bettyFixer.h"

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
	char *correctedStr = (char *)malloc(lastNonWhitespaceIndex + 2);
	/* +2 to include the null terminator */
	if (correctedStr == NULL)
	{
		return (NULL); /* Memory allocation failed */
	}

	/* Copy the non-whitespace portion of the string to the new buffer */
	strncpy(correctedStr, str, lastNonWhitespaceIndex + 1);
	correctedStr[lastNonWhitespaceIndex + 1] = '\n';

	return (correctedStr);
}
