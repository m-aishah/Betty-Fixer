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
