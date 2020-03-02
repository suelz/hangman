#ifndef __UTILS_H__
#define __UTILS_H__


char getCharacter(const char * prompt, const char* error);
char getCharacter(const char *prompt, const char* error, const char validInput[], int validInputLength);

void clearScreen();

void waitForKeyPress();



#endif // !__UTILS_H__