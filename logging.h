#ifndef LOGGING_H
#define LOGGING_H
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <ctime>
#include <string.h>
#include <stdlib.h>

void print( const char* format, ... );
std::string getLog(void);

#endif //LOGGING_H
