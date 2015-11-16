#include "wolfram.h"

const int   wolfram_app_in_use 	  = 0;
const string wolfram_app_id[] = {	"J938L5-VT7HJ589E9",
									"LWWKJV-38WP7TRT45",
									"######-##########"};
                                    
 
/* Probably doesn't work
TiXmlElement * getElementByName(TiXmlDocument & doc, std::string const & elemt_value) {

   TiXmlElement * elem = doc.RootElement(); //Tree root
   while (elem) {
      if (!std::string(elem -> Value()).compare(elemt_value)) return (elem);
      //elem = elem->NextSiblingElement();
      if (elem -> FirstChildElement()) {
         elem = elem -> FirstChildElement();
      } else if (elem -> NextSiblingElement()) {
         elem = elem -> NextSiblingElement();
      } else {
         while (!elem -> Parent() -> NextSiblingElement()) {
            if (elem -> Parent() -> ToElement() == doc.RootElement()) {
               return NULL;
            }
            elem = elem -> Parent() -> NextSiblingElement();
         }
      }
   }
   return (NULL);
}
*/

string parseXML(string input, string theQuestion)
{
 //TODO: XML parsing (may be overkill for this)

	//TiXmlDocument xml;
	//xml.Parse( input.c_str() );
    //TiXmlElement *node = getElementByName(xml,"user");
    //print("node: %s",node->Value());
	//xml.Print();
	//return input;



//Quick/Lazy XML Searching

print("\n\n******************Begin XML***********************\n\n");
print("%s",input.c_str());
print("\n\n****************** END XML ***********************\n\n");
    char *newinput = strdup(input.c_str());
    //print("Searching string (%s)\n",newinput);
    char *token = NULL;


    
    //Check for primary field
    if(token == NULL){
        token = strstr(newinput,"primary=\'true\'");
    }
    
    //Check for a description field
    if(token == NULL){
        
        token = strstr(newinput,"pod title=\'Description\'");
    }   
    
    // Check for a data field
    if(token == NULL){
        token = strstr(newinput,"scanner=\'Data\'");
    }
    
    //Check for a Interpretation field
    if(token == NULL){
        token = strstr(newinput,"title=\'Input interpretation\'");
    }
    

    
    // Put additional fields here
    //if(token == NULL){
    //    //Backup option: Check for a ##### field
    //    token = strstr(newinput,"#####'");
    //}
    
    
    //Just give up at this point
    if(token == NULL){
        return getRandomBadResults(theQuestion);
    }
            
    
    //Get text between <plaintext> and </plaintext>
    
    char* textbegin = strstr(token,"<plaintext>");

    //print("Searching string (%s)\n",token);
    if(textbegin == NULL)
        return getRandomBadResults(theQuestion);

    char* textend = strstr(textbegin,"</plaintext>");
    

    char stringbuffer [999999];
    memset(stringbuffer,0,999999);
    int numbytes = textend - textbegin;
    strncpy(stringbuffer, textbegin+11, numbytes-11);
    //print("output (%d): %s\n",numbytes,stringbuffer);
    
    string output = stringbuffer;

    return output;
    
}

string askWolfram(char *input, char *keyword)
{
    //print("Received URL: (%s)\n",input);
    string sXML;
    string sQuery = "http://api.wolframalpha.com/v2/query?input=";
    string rawquery = pullOutTextFromURL(input,keyword);
    string query = htmlEntitiesEncode(rawquery);
    sQuery.append(query);
    sQuery.append("&appid=");
    sQuery.append(wolfram_app_id[wolfram_app_in_use]);
    sQuery.append("&format=plaintext");
    
    print("query string: %s\n",sQuery.c_str());

    const char * url = (const char*) sQuery.c_str();
    sXML = getWebPage(url);

	string outputString = parseXML(sXML,rawquery);
	
	if(outputString.length() == 0 )
	{
		outputString.append("Sorry, I can't display images");
	}

    
    return htmlEntitiesDecode(outputString);
    
}
