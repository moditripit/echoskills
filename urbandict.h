#ifndef URBANDICT_H
#define URBANDICT_H

#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>  // manipulate strings (integer conversion) 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "logging.h"
#include "utils.h"
#include <ctime>


const string URBANDICT_URI = "/GetUrbanDictionary/";              
                
string askUrbanDictionary(char *input, char *keyword);


#endif //URBANDICT_H
