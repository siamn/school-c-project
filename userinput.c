#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// responsibility of caller to free line after usage for this function.
char *getLine()
{
    char *line = NULL;
    size_t len = 0;
    ssize_t linelen;
    int choice;
    char *end;

    linelen = getline(&line, &len, stdin);
    if (linelen < 0)
    {
        free(line);
        printf("Could not read user input. Try again.");
        return NULL;
    }
    int lastCharacter = strlen(line) - 1;
    if (line[lastCharacter] == '\n')
    {
        line[lastCharacter] = '\0';
    }

    return line;
}

// function should handle freeing memory itself (as only 1, 0 or -1 is returned (-1 for error))
int getYesNoResponse(char *msg)
{
    char *input;
    int response = 2;
    while (response > 1)
    {
        printf("%s", msg);
        printf("Please type 'yes'/'y'  or 'no'/'n' below:\n");
        input = getUserInput();
        printf("%lu\n", strlen(input));
        printf("%lu\n", strlen("y"));
        if (strcmp(input, "yes") == 0 || strcmp(input, "y") == 0)
        {
            free(input); // free input as no longer needed.
            return 1;
        }
        else if (strcmp(input, "no") == 0 || strcmp(input, "n") == 0)
        {
            free(input); // free input as no longer needed.
            return 0;
        }
        else
        {
            printf("Please try again.\n");
        }
    }
    free(input); // free input as no longer needed.
    return -1;
}

// function should handle freeing memory itself as a parsed integer is returned rather than the string.
int getPositiveInt()
{
    char *line = getUserInput();
    int choice;
    char *end;

    choice = strtol(line, &end, 10);
    if (end == line || choice < 0)
    {
        if (choice == 0)
        {
            if (errno == ERANGE)
            {
                printf("Input out of range\n");
            }
            if (errno == EINVAL)
            {
                printf("Could not parse input.\n");
            }
        }
        printf("Please try again with a valid number.\n");
        return -1;
    }
    free(line); // have to free line as no longer being used after this function exits.
    return choice;
}