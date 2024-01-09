#include "bettyFixer.h"

char *removeTrailingWhitespaces(const char *str)
{
    if (str == NULL)
    {
        return NULL; // Handle NULL input string
    }

    int length = strlen(str);

    // Find the index of the last non-whitespace character
    int lastNonWhitespaceIndex = length - 1;
    while (lastNonWhitespaceIndex >= 0 && isspace(str[lastNonWhitespaceIndex]))
    {
        lastNonWhitespaceIndex--;
    }

    // Allocate memory for the corrected string
    char *correctedStr = (char *)malloc(lastNonWhitespaceIndex + 2); // +2 to include the null terminator
    if (correctedStr == NULL)
    {
        return NULL; // Memory allocation failed
    }

    // Copy the non-whitespace portion of the string to the new buffer
    strncpy(correctedStr, str, lastNonWhitespaceIndex + 1);
    correctedStr[lastNonWhitespaceIndex + 1] = '\n';
    correctedStr[lastNonWhitespaceIndex + 2] = '\0'; // Null-terminate the string

    return correctedStr;
}
