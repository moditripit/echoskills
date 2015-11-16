#ifndef WOLFRAM_H
#define WOLFRAM_H
#include <iostream>
#include <string>
#include <sstream>  // manipulate strings (integer conversion) 
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include "tinyxml.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "logging.h"
#include "utils.h"

const string Wolfram_URI = "/GetWolfram/";
                                    
string askWolfram(char *input, char *keyword);


#endif //WOLFRAM_H
