char *getLine();

char *getLimitedLine(int limit);

int getYesNoResponse(char *prompt);

int getPositiveInt();

/**
 * @brief Get the Float object
 *
 * @return float
 */
float getFloat();

float getBoundPositiveFloat(int lowerBound, int upperBound);