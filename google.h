#ifndef ASKGOOGLE_H
#define ASKGOOGLE_H

#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>  // manipulate strings (integer conversion) 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tinyxml.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "logging.h"
#include "utils.h"
#include <ctime>


const string MAPS_URI = "/GetGoogle/";
                                    
string askGoogle(char *input, char *keyword);


#endif //ASKGOOGLE_H
