#ifndef __COCA_COLA_FUNCTIONS__
#define __COCA_COLA_FUNCTIONS__

#include <stdio.h>
#include "Macros.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define WEBSITE_LINK "https://www.coca-colacompany.com/"


void printLOGO();
void cocaColaLinkWebsite();
void findSecretRecipe();
void pinkKey(char* str);
void blueKey(char* str);
void greenKey(char* str);
void yellowKey(char* str);
void redKey(char* str);

#endif /* __COCA_COLA_FUNCTIONS__ */