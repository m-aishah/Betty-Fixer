#include "bettyFixer.h"

/**
 * addSpacesAroundOperators - Add spaces around operators in a string.
 * @orgStr: The string in question.
 *
 * Return: The corrected string.
 */
char *addSpacesAroundOperators(const char* orgStr)
{
	size_t len, resultIndex, i;
	char * correctedStr;
	
	/* Handle NULL input String. */
	if (orgStr == NULL)
		return (NULL);
	
	/* Calculate the length of the input string. */
	len = strlen(orgStr);

	/* Allocate memory for the modified string. */
	/* Each operator can be replaced by itself + 1 space. */
	correctedStr = (char*)malloc((2 * len) * sizeof(char));

	/* Handle memory allocation failure. */
	if (correctedStr == NULL) 
	{
		perror("malloc");
		return (NULL);
	}

	/* Initialize index for the result string. */
	resultIndex = 0;

	/* Loop through each character in the input string. */
	for (i = 0; i < len; i++) 
	{
		/**
		* If the current character is an operator,
		* add a space before and after it.
		*/
		if (orgStr[i] == '+' || orgStr[i] == '-' || orgStr[i] == '*' || orgStr[i] == '/' || orgStr[i] == '=') 
		{
			/* Add space before the operator. */
			if (i > 0 && orgStr[i - 1] != ' ') 
				correctedStr[resultIndex++] = ' ';

			/* Add the operator. */
			correctedStr[resultIndex++] = orgStr[i];

			/* Add space after the operator or equal sign. */
			if (i < len - 1 && orgStr[i + 1] != ' ')
				correctedStr[resultIndex++] = ' ';
		} 
		else
		{
			/* If the current character is not an operator, copy it as is. */
			correctedStr[resultIndex++] = orgStr[i];
		}
	}

	return (correctedStr);
}

/**
 * addLineAfterDeclaration - Adds a newline character to the beginning of a string.
 * @orgStr: The string in question.
 *
 * Return: The modified string.
 */
char *addLineAfterDeclaration(const char *orgStr)
{
	/* Handle NULL input string. */
	if (orgStr == NULL)
		return NULL;

	/* Calculate the length of the original string. */
	size_t orgLength = strlen(orgStr);

	/**
	 * Allocate memory for the corrected string,
	 * including space for the newline character.
	 */
	char *correctedStr = (char*)malloc((orgLength + 1) * sizeof(char));

	/* Handle memory allocation failure. */
	if (correctedStr == NULL)
	{
		perror("malloc");
		return NULL;
	}

	/* Add newline character at the beginning. */
	correctedStr[0] = '\n';

	/* Copy the original string to the corrected string starting from index 1. */
	strcpy(correctedStr + 1, orgStr);

	return (correctedStr);
}
