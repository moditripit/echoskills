#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "fcgio.h"
#include "curlfuncs.h"
#include "logging.h"

//Get IP
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

std::string getRandomBadResults(std::string theQuestion);
std::string htmlEntitiesDecode (std::string str);
std::string htmlEntitiesEncode (std::string str);
std::string pullOutTextFromURL(char *input,char* token);
std::string getWebPage(const char* url);
std::string getLocalIP(void);
std::string replacespaces(string input);
std::string removeNewlines(string input);
std::string removeBackslash(string input);
#endif //UTILS_H
