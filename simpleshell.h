#ifndef simpleshell_h
#define simpleshell_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stddef.h>

char _strcpy(char *dest, const char *src);
char _strcat(char *dest, const char *src);
size_t _strlen(const char *str);
char _strdup(const char *str);
char *_getenv(const char *name);
int compare(const char *str1, const char *str2);
void handle_execution(char **argv);
char *getpath(char *command);

#endif
