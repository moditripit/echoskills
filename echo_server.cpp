/*****************************

Echo Web Server

******************************/

#include "echo_server.h"
#include "mycookbook.h"
#include "wolfram.h"
#include "google.h"
#include "disney.h"
#include "urbandict.h"

// Maximum bytes
const unsigned long STDIN_MAX = 1000000;

extern const char *disneyNames[];
extern int disneyNamesLength;
using namespace std;


int is_get(char* method, char* uri) {
  if (strcmp (method, "GET") != 0) {
    return 0;
  }

  return 1;
}

int is_put(char* method, char* uri)
{
    if(strcmp (method, "PUT") != 0)
    {
        return 0;
    }
    return 1;
}

int main(void) {
	//Setup Network Stuff
    // Backup the stdio streambufs
    streambuf * cin_streambuf  = cin.rdbuf();
    streambuf * cout_streambuf = cout.rdbuf();
    streambuf * cerr_streambuf = cerr.rdbuf();
    int ConLen(0), DecLen(0), RetVal(0);
    bool bErr; // Error Flag
    const char *cString, *cStrRet; // Uninitialized C-Strings
    string sReply, sTemp; // Strings
    string sHead("Content-Type: text/html\r\n\r\n"); // HTTP header
    ostringstream ss; // String Stream object
    FCGX_Request request;
    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);
    double ticker = 0.0f;
    print("\n\n\n********************************** --Server has started-- *************************************\n%s\n\n",
																									getLocalIP().c_str());
    //Create Cookbook Instance
    MyCookbook* Recipe = new MyCookbook();
    
	//Wait for requests
    while (FCGX_Accept_r(&request) == 0) //this call is blocking
    {
        //Pre-process requests ========================
        char * method = FCGX_GetParam("REQUEST_METHOD", request.envp); //GET, PUT, etc...
        char * uri = FCGX_GetParam("REQUEST_URI", request.envp);
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);
        cin.rdbuf(&cin_fcgi_streambuf);
        cout.rdbuf(&cout_fcgi_streambuf);
        cerr.rdbuf(&cerr_fcgi_streambuf);



		//Process Request based on content =========================
		
		//Print to terminal was we received
		print("***** New Request ******* Received Request URL:\t \"%s\" \n",uri);
		string output_string;
        //These are the different Intents / commands
        if(strcmp (uri, "/CheckServerStatus") == 0)
        {
            output_string.append("Running smooth like butter");
        }

        //Search for the term "/GetRecipe/" in the url
        else if(strstr(uri, "/GetRecipe/") != NULL)
        {
            output_string.append(Recipe->getRecipe(uri));
        }

        //Search for the term "/GetWolfram/" in the url
        else if(strstr(uri, Wolfram_URI.c_str()) != NULL)
        {
            output_string.append(askWolfram(uri,(char*)Wolfram_URI.c_str()));

        }
        
        //Search for the term "/GetGoogle/" in the url
        else if(strstr(uri, MAPS_URI.c_str()) != NULL)
        {
			   //Check to see if it's a request for disney
				int x = 0;
				int founddisney = 0;
				for(x = 0; x < disneyNamesLength ; x++)
				{
					if(strstr(uri,disneyNames[x]) != NULL)
					{

						output_string.append(askDisney(uri,(char*)MAPS_URI.c_str()));
						founddisney = 1;
					}
				}
    
				if(founddisney == 0)
					output_string.append(askGoogle(uri,(char*)MAPS_URI.c_str()));

        }
        
        //Search for the term "/GetUrbanDictionary/" in the url
        else if(strstr(uri, URBANDICT_URI.c_str()) != NULL)
        {
            output_string.append(askUrbanDictionary(uri,(char*)URBANDICT_URI.c_str()));
        }

        //Open the debug log, only to the screen. don't log the log
        else if(strstr(uri, "/GetLogs/") != NULL)
        {
            cout << "<plaintext>" << getLog();
            output_string.append("Displayed Logs");
        }
		
        //Default case
        else
        {
            output_string.append("What the hell do you want now?");
        }
        
        if(output_string.length() == 0)
		{
			output_string.append("Oops, I didn't do anything that time, you might want to check my logs");
		}
		
		
		//Site Output =========================================
		
		//This must always occur so website returns successful status
        cout << "Content-type: text/html\r\n"
             << "\r\n";
        cout << output_string <<endl;
        print("****************** Echo Server Output: (%s)\n",output_string.c_str());


//Debugging Server Only
/*
        cout << "<P>\n"
             << "<html>\n"
             << "  <head>\n"
             << "    <title>You shouldn't be here</title>\n"
             << "  </head>\n"
             << "  <body>\n"
             << "    <h1>You shouldn't be here</h1>\n"
             << "    <h2>Method: " << method <<"</h2>\n"
             << "    <h2>URI: " << uri <<"</h2>\n"
             << "  </body>\n"
             << "</html>\n";
*/

    }

    // restore stdio streambufs
    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);

    return 0;
}

