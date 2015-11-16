#include "disney.h"

std::string epcot_url             = "epcot";
std::string magickingdom_url      = "magic-kingdom";
std::string hollywoodstudios_url  = "hollywood-studios";
std::string animalkingdom_url     = "animal-kingdom";
std::string typhoonlagoon_url     = "typhoon-lagoon";
std::string blizzardbeach_url     = "blizzard-beach";

std::string epcot_display             = "Epcot";
std::string magickingdom_display      = "Magic Kingdom";
std::string hollywoodstudios_display  = "Hollywood Studios";
std::string animalkingdom_display     = "Animal Kingdom";
std::string typhoonlagoon_display     = "Typhoon Lagoon";
std::string blizzardbeach_display     = "Blizzard Beach";

int epcot = 0;
int magickingdom = 1;
int animalkingdom = 4;
int hollywoodstudios = 6;
int blizzardbeach = 10;
int typhoonlagoon = 12;

int disneyNamesLength = 14;          
const char *disneyNames[] = { "epcot",
                            "magic kingdom",
                            "magic%20kingdom",
                            "disney",
                            "animal kingdom", 
                            "animal%20kingdom", 
                            "m.g.m.", 
                            "mgm", 
                            "hollywood studios", 
                            "hollywood%20studios",                             
                            "blizzard beach", 
                            "blizzard%20beach",
                            "typhoon lagoon",
                            "typhoon%20lagoon" };    
                                                  
string parseResults(string input, string theQuestion, string ParkName, int flagtommorrow)
{
    string resultString;

    char *newinput = strdup(input.c_str());
    char stringbuffer [999999];
    
    //Example strings
    //<h2><strong>Park Hours:</strong> <span>9:00am – 9:00pm</span><div class="extraMagicHoursSeparator"></div><strong>Extra Magic Hours:</strong> <span>9:00pm – 11:00pm</span><br><a class="colorMagicKingdomBlue" href="https://disneyworld.disney.go.com/destinations/epcot/">Park Information</a></h2>

    // ************* Find the hours **********************
    print("Finding name");
    char *beginhourcontainer = strstr(newinput,"<strong>Park Hours:</strong> <span>");
    char* endhourcontainer = NULL;
    char* beginhour = NULL;
    char* endhour = NULL;
    if(beginhourcontainer != NULL)
    {
                endhourcontainer = strstr(beginhourcontainer,"<span>");
    }
    if(endhourcontainer != NULL)
    {
        beginhour = endhourcontainer+6;
        endhour = strstr(beginhour,"<");
    }
    if(endhour != NULL)
    {
        memset(stringbuffer,0,999999);
        int numbytes = endhour - beginhour;
        strncpy(stringbuffer, beginhour, numbytes);

        resultString.append("The hours for ");
        resultString.append(ParkName);
        
        //Maybe make flags for different range of dates to allow
        // for using relative weekday names (ie. sunday, monday, etc..)
        // or for longer ranges, spit out the date here.
        if(flagtommorrow)
        {
          resultString.append(" tomorrow");  
        }
        resultString.append(" are ");
        
        //Remove unicode en dash, otherwise alexa says "en dash"
        char* newstring = stringbuffer;
        char* dash = strstr(newstring,"&ndash;");
        if(dash != NULL)
        {
            dash[0] = ' ';
            dash[1] = ' ';
            dash[2] = ' ';
            dash[3] = 't';
            dash[4] = 'o';
            dash[5] = ' ';
            dash[6] = ' ';
            
            resultString.append(std::string(newstring));
        }
        else
        {
            resultString.append(stringbuffer);
        }
    }
    

    //Just give up at this point
    if(endhour == NULL){
         //print("%s",input.c_str());
        return getRandomBadResults(theQuestion);
    }

    return resultString;
    
}

string askDisney(char *input, char *keyword)
{
    print("askDisney Called\n");
    //https://disneyworld.disney.go.com/calendars/epcot/2015-07-17/#timeofday=allday
    
    print("Received URL: (%s)\n",input);
    string sResults;
    string sQuery = "https://disneyworld.disney.go.com/calendars/";
    
    string rawquery = pullOutTextFromURL(input,keyword);
    string ParkName; 
    
    int x = 0;
    int founddisney = 0;
    string outputName;
    for(x = 0; x < disneyNamesLength ; x++)
    {
        if(strstr(input,disneyNames[x]) != NULL)
        {
            founddisney = x;
            print("Found disney location (%s) at loc %d\n",disneyNames[x],x);
            break;
        }
    }
    if(founddisney >= epcot && founddisney < magickingdom){
         ParkName.assign(epcot_url);
         outputName = epcot_display;
    }
    else if(founddisney >= magickingdom && founddisney < animalkingdom){
        ParkName.assign(magickingdom_url);
        outputName = magickingdom_display;
    }
    else if(founddisney >= animalkingdom && founddisney < hollywoodstudios){
        ParkName.assign(animalkingdom_url);  
        outputName = animalkingdom_display;      
    }
    else if(founddisney >= hollywoodstudios && founddisney < blizzardbeach){
        ParkName.assign(hollywoodstudios_url);  
        outputName = hollywoodstudios_display;   
    }   
    else if(founddisney >= blizzardbeach && founddisney < typhoonlagoon){
        ParkName.assign(blizzardbeach_url); 
        outputName = blizzardbeach_display;     
    }  
    else {
        ParkName.assign(typhoonlagoon_url);  
        outputName = typhoonlagoon_display;
    }
    
    int addtime = 0;
    int flagtommorrow = 0;
    if(strstr(input,"tomorrow") != NULL)
    {
        addtime = 24 * 60 * 60;
        flagtommorrow = 1;
    }

    time_t t = time(0) + addtime;   // get time now
    struct tm * now = localtime( & t );
    char year [10];
    char month[10];
    char day  [10];
    sprintf(year, "%d",now->tm_year + 1900 );
    sprintf(month, "%.2d",now->tm_mon + 1 );
    sprintf(day, "%.2d",now->tm_mday );

    sQuery.append(ParkName); 
    //sQuery.append("/2015-07-18/"); //TODO
    sQuery.append("/");
    sQuery.append(year);
    sQuery.append("-");
    sQuery.append(month);
    sQuery.append("-");
    sQuery.append(day);
    sQuery.append("/");
    print("query string: %s\n",sQuery.c_str());

    const char * url = (const char*) sQuery.c_str();
    
    print("obtaining web data");
    sResults = getWebPage(url);

    print("parsing results");
	string outputString = parseResults(sResults,rawquery,outputName,flagtommorrow);
	
	if(outputString.length() == 0 )
	{
		outputString.append("Sorry, I can't display images");
	}

    print("returning answer");
    return htmlEntitiesDecode(outputString);
}

