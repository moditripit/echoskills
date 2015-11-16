#ifndef DISNEY_H
#define DISNEY_H

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

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

const string DISNEY_URI = "/GetDisney/";              
                

string askDisney(char *input, char *keyword);


#endif //DISNEY_H
