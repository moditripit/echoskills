#include "urbandict.h"
string getRandomUrbanDictionary ();

string parseResultsUrban(string input, string theQuestion)
{
    string resultString;

    char *newinput = strdup(input.c_str());
    char stringbuffer [999999];
    
    print("\n\n******************Begin XML***********************\n\n");
	print("%s",input.c_str());
	print("\n\n****************** END XML ***********************\n\n");

    char *token = NULL;
/*
{"tags":["chops","chopped","chopping","weed","sex","chopper","high","penis","pork","cut"],
* "result_type":"exact","list":[{"defid":15239,"word":"chop","author":"sim1",
* "permalink":"http://chop.urbanup.com/15239",
* "definition":"The art of trying to get a girl to go out wit you...And gettin' her digits... ",
* "example":"Man this kid was fully trying to chop me last nite and now we're dealing...\r\n",
* "thumbs_up":1321,"thumbs_down":550,"current_vote":""},{"defid":26952,"word":"Chops",
* "author":"Guy who hates pop punk","permalink":"http://chops.urbanup.com/26952","definition":"Long sideburns reaching down to the jawline.",
* "example":"If I were really cool, I'd have me some wicked bushy chops.","thumbs_up":607,"thumbs_down":238,"current_vote":""},
*/

    char *definitionFirst = strstr(newinput,"\"definition\":\"");
    char *definitionStart = NULL;
    char *definitionEnd = NULL;
    
	if (definitionFirst != NULL) {
		definitionStart = definitionFirst + 14;
	}

	if (definitionStart != NULL) {
		definitionEnd = strstr(definitionStart,"\",\"");
	}
	
    if(definitionEnd != NULL)
    {
        memset(stringbuffer,0,999999);
        int numbytes = definitionEnd - definitionStart;
        strncpy(stringbuffer, definitionStart, numbytes);
        resultString.append(theQuestion);
        resultString.append(": ");
        resultString.append(stringbuffer);
        resultString.append(" ");
    }
    
    //Just give up at this point
    if(definitionEnd == NULL){
         //print("%s",input.c_str());
        return getRandomBadResults(theQuestion);
    }
    
    char *exampleFirst = strstr(definitionEnd,"\"example\":\"");
    char *exampleStart = NULL;
    char *exampleEnd = NULL;
    
	if (exampleFirst != NULL) {
		exampleStart = exampleFirst + 11;
	}

	if (exampleStart != NULL) {
		exampleEnd = strstr(exampleStart,"\",\"");
	}
	
	int numBytesShifted = 0;
    if(exampleEnd != NULL)
    {
        memset(stringbuffer,0,999999);
        int numbytes = exampleEnd - exampleStart;
        numBytesShifted = exampleEnd - newinput;
        strncpy(stringbuffer, exampleStart, numbytes);
        resultString.append(" For example, ");
        resultString.append(stringbuffer);
        resultString.append(" ");
        resultString = removeNewlines(resultString);
        resultString = removeBackslash(resultString);
    }
    
    //Just finish up then
    if(exampleEnd == NULL){
        return resultString;
    }

    return resultString;
    
}

string askUrbanDictionary(char *input, char *keyword)
{
    print("askUrbanDictionary Called\n");
    
    print("Received URL: (%s)\n",input);
    string sResults;
    string sQuery = "http://api.urbandictionary.com/v0/define?term=";
    string rawquery = pullOutTextFromURL(input,keyword);
    string newquery = "";
    string encodedQuery = "";
    
    if( strstr(rawquery.c_str(),"random") != NULL || 
		strstr(rawquery.c_str(),"Random") != NULL) {
		string randomWord = getRandomUrbanDictionary();
		newquery.append(randomWord);
		encodedQuery = replacespaces(newquery);
	    rawquery = newquery;
	}
	else 
	{
		encodedQuery = replacespaces(rawquery);
	}

	print("Appending to encodedQuery");
	sQuery.append(encodedQuery);
	
    print("query string: %s\n",sQuery.c_str());

    const char * url = (const char*) sQuery.c_str();
    
    print("obtaining web data");
    sResults = getWebPage(url);

    print("parsing results");
	string outputString = parseResultsUrban(sResults,rawquery);
	
	if(outputString.length() == 0 )
	{
		outputString.append("Sorry, I can't display images");
	}

    print("returning answer");
    return htmlEntitiesDecode(outputString);
}

string getRandomUrbanDictionary () {
	print("getRandomUrbanDictionary Called\n");
       
    string sResults;
    string sQuery = "http://www.urbandictionary.com/random.php";
    
    print("obtaining page data for random value");
    const char * url = (const char*) sQuery.c_str();
    sResults = getWebPage(url);
    char *newinput = strdup(sResults.c_str());
    char stringbuffer [500];
    string resultString = "";

    char *token = NULL;
    //<title>Urban Dictionary: netflix and chill</title>
    
    char *normalizedFirst = strstr(newinput,"<title>Urban Dictionary: ");
    char *normalizedStart = NULL;
    char *normalizedEnd = NULL;
    
    //print(normalizedFirst);
	if (normalizedFirst != NULL) {
		//print("Found normalized");
		normalizedStart = normalizedFirst + 25;
	}

	if (normalizedStart != NULL) {
		//print("Found the end of normalized");
		normalizedEnd = strstr(normalizedStart,"</title>");
	}
	
    if(normalizedEnd != NULL)
    {
        memset(stringbuffer,0,500);
        int numbytes = normalizedEnd - normalizedStart;
        //print("numbytes = %d",numbytes);
        strncpy(stringbuffer, normalizedStart, numbytes);
        resultString.append(stringbuffer);
    }
	print("Grabbed new random search: %s",resultString.c_str());
    return resultString;
}
