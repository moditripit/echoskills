#include "google.h"

string parseResults(string input, string theQuestion)
{

    string resultString;

    char *newinput = strdup(input.c_str());
    char stringbuffer [999999];
    
    //Example strings
    //<div class="kno-ecr-pt kno-fb-ctx _hdf" data-ved="0CIIBENwdKAAwCw">CVS Pharmacy - Photo<div class="starring-container"><div> <div class="knowledge-starring__star-toggle-link r-ikwjjbqUXvGo" role="button" tabindex="0" jsaction="r.r2j2oNFOKhA" data-rtid="ikwjjbqUXvGo" jsl="$t t-iQk1XMn57vA;$x 0;" data-ved="0CIMBEK9BMAs"> <div class="ikwjjbqUXvGo-lZ0H0hh3ZP4 stt-tog stt-uf" aria-label="Save place to your Map">  </div> </div>   <div class="stt-not" style="display:none" aria-label="Location saved notification"> <div class="_QUe">Saved to your Map</div> <div class="_sUe"><a href="/maps/place/is+cvs+on+underhill+and+dean+open/data=!4m2!3m1!1s0x88e7667a4be43a09:0x54a4b66c709ae011" tabindex="0" role="button" onmousedown="return rwt(this,'','','','12','AFQjCNHw--60rU6dG4XyDfOpeUFma5gZmQ','Rq4GU97j2UHlEkVEUIfBiQ','0CIQBEKNMMAs','','',event)">View on Map</a></div> <div class="_yRg"> <div class="_zRg"></div> </div> </div>  </div></div></div>
    //<div class="kno-ecr-pt kno-fb-ctx _hdf" data-ved="0CHkQ3B0oADAM">Bank of America<div class="starring-container"><div> <div class="knowledge-starring__star-toggle-link r-itzdonxqV6B4" role="button" tabindex="0" jsaction="r.r2j2oNFOKhA" data-rtid="itzdonxqV6B4" jsl="$t t-iQk1XMn57vA;$x 0;" data-ved="0CHoQr0EwDA"> <div class="itzdonxqV6B4-lZ0H0hh3ZP4 stt-tog stt-uf" aria-label="Save place to your Map">  </div> </div>   <div class="stt-not" style="display:none" aria-label="Location saved notification"> <div class="_QUe">Saved to your Map</div> <div class="_sUe"><a href="/maps/place/is+bank+of+america+on+alafaya+and+chickasaw+open/data=!4m2!3m1!1s0x88e765ade90c1ff7:0x49a3da1c99ea492d" tabindex="0" role="button" onmousedown="return rwt(this,'','','','13','AFQjCNE12Xk_tpQZjLdHlviwU1Xn-T01wg','8m_EDOi-F7MhSAxvo577Gg','0CHsQo0wwDA','','',event)">View on Map</a></div> <div class="_yRg"> <div class="_zRg"></div> </div> </div>  </div></div></div>

    // ************* Find the name **********************
    print("Finding name");
    char *beginnamecontainer = strstr(newinput,"kno-ecr-pt kno-fb-ctx _hdf");
    char* endnamecontainer = NULL;
    char* beginname = NULL;
    char* endname = NULL;
    if(beginnamecontainer != NULL)
    {
                endnamecontainer = strstr(beginnamecontainer,">");
    }
    if(endnamecontainer != NULL)
    {
        beginname = endnamecontainer+1;
        endname = strstr(beginname,"<");
    }
    if(endname != NULL)
    {
        memset(stringbuffer,0,999999);
        int numbytes = endname - beginname;
        strncpy(stringbuffer, beginname, numbytes);
        resultString.append(stringbuffer);
        resultString.append(" ");
    }
    
    // ************* Find the address **********************
    //  //<span style="font-weight:bold">Address:</span>&nbsp;<span>9975 Lake Underhill Rd, Orlando, FL 32825</span>
    char *beginaddresscontainer = strstr(newinput,"Address:</span>");
    char* endaddresscontainer = NULL;
    char* beginaddress = NULL;
    char* endaddress = NULL;
    if(beginaddresscontainer != NULL)
    {
                endaddresscontainer = strstr(beginaddresscontainer,"<span>");
    }
    if(endaddresscontainer != NULL)
    {
        beginaddress = endaddresscontainer+6;
        endaddress = strstr(beginaddress,"<");
    }
    if(endaddress != NULL)
    {
        memset(stringbuffer,0,999999);
        int numbytes = endaddress - beginaddress;
        strncpy(stringbuffer, beginaddress, numbytes);
        resultString.append("at ");
        resultString.append(stringbuffer);
        resultString.append(" ");
        
        //Since we have an address, let's change the context of the sentence
        resultString.insert(0,"The ");
    }
    
    
    // ************* Find the open / closed status **********************
    print("Finding status");
    //print("Searching string (%s)\n",newinput);
    char *token = NULL;
    //Check if closed first and return
    if(strstr(newinput,"<span class=\"_CK _lo\">Closed now</span>") != NULL)
    {
        return " is now closed";
    }
    if(token == NULL){
        token = strstr(newinput,"<span class=\"_CK _SX\">Closing soon</span>");
        if(token != NULL){
            
        //temp - todo: add hours
            resultString.append("will be closing soon");
        }
    }   
    if(token == NULL){
        token = strstr(newinput,"<span class=\"_CK _TX\">Open today</span>");
        if(token != NULL){
            //temp - todo: add hours
            resultString.append("is currently open");
        }
    }

    //Just give up at this point
    if(token == NULL){
         //print("%s",input.c_str());
        return getRandomBadResults(theQuestion);
    }
    

    print("Finding hours");
    string begin = "<a class=\"fl\" href=\"javascript:void(0)\"><span>";
    char* textbegin = strstr(token,"<a class=\"fl\" href=\"javascript:void(0)\"><span>");
    char* textend = strstr(textbegin,"</span></a>");


    memset(stringbuffer,0,999999);
    int numbytes = textend - textbegin;
    strncpy(stringbuffer, textbegin+begin.length(), numbytes-begin.length());
    //print("output (%d): %s\n",numbytes,stringbuffer);
    
    string times = stringbuffer;
    
    print("Returning google maps result");
    
    if(strstr(stringbuffer,"Open 24 hours") != NULL)
    {
        resultString.append(", it is ");
    }
    else
    {
        resultString.append(", it's hours are ");
    }
    resultString.append(times);

    return resultString;
    
}

string askGoogle(char *input, char *keyword)
{
    //print("Received URL: (%s)\n",input);
    string sResults;
    string sQuery = "http://www.google.com/search?q=";
    
    string rawquery = pullOutTextFromURL(input,keyword);
    string query = htmlEntitiesEncode(rawquery);
    sQuery.append(query);
    
    static int use = 0;
    
    if(use == 0)
    {
        sQuery.append("&aqs=chrome..69i57j69i64.1119j0j9&sourceid=chrome&es_sm=122&ie=UTF-8");
        use = 1;
    }
    else
    {
        sQuery.append("&aqs=chrome..69i57j69i64.10319j0j7&sourceid=chrome&es_sm=122&ie=UTF-8");
        use = 1;
    }

    
    print("query string: %s\n",sQuery.c_str());

    const char * url = (const char*) sQuery.c_str();
    
    print("obtaining web data");
    sResults = getWebPage(url);

    print("parsing results");
	string outputString = parseResults(sResults,rawquery);
	
	if(outputString.length() == 0 )
	{
		outputString.append("Sorry, I can't display images");
	}

    print("returning answer");
    return outputString;
    
}

