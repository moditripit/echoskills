#include "logging.h"

const char * logfile = "logging.txt";

void print( const char* format, ... ) {
    FILE * pFile;
    
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  
    pFile = fopen (logfile,"a");
    
    fprintf(stderr,"\n%s: \t",buf);
    fprintf(pFile, "\n%s: \t",buf);
    
    va_list args;
    va_start( args, format );
    vfprintf( stderr, format, args );
    vfprintf( pFile, format, args );
    va_end( args );
    
    fclose(pFile);
}


std::string getLog() 
{
    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;
    std::string returnString;
    pFile = fopen (logfile,"r");
    
    if (pFile==NULL) 
    {
        return "Error attempting to get log";
    }
    
    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);
    
    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) 
    {
        return "Could not allocate memory";
    }
  
    // copy the file into the buffer:
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) 
    {
        return "Error reading log file";
    }
    
    returnString.assign(buffer);
    
    free(buffer);
    return returnString;
    
}
