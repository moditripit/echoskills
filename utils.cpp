#include "utils.h"

#define array_length(array) (sizeof (array) / sizeof (array)[0])

using namespace std;

	string subs[] = {
		"& #34;", "&quot;",
		"& #39;", "&apos;",
		"& #38;", "&amp;",
		"& #60;", "&lt;",
		"& #62;", "&gt;",
		"&34;", "&39;",
		"&38;", "&60;",
		"&62;", "%20",
        "&ndash;", "\u2013"
	};
	
	string reps[] = {
		"\"", "\"",
		"'", "'",
		"&", "&",
		"<", "<",
		">", ">",
		"\"", "'",
		"&", "<",
		">", " ",
        "-", "-"
	};
    
string badResultPool[] = {  "Alas, I can't find anything.",
                            "I couldn't find it.", 
                            "I know nothing, like John Snow.",
                            "I got lost in the internet.",
                            "What were you asking? I was distracted by cats I found on Reddit.",
                            "I don't know.",
                            "I was going to tell you, but now I'm not.",
                            "Is it 42? No, but that should cover it.",
                            "I don't know. What do you think it is?",
                            "Well Fuck, just Google it.",
                            "Think about it, how could I possibly answer that.",
                            "I'm not sure. Can I phone a friend?",
                            "I believe you can find that in your encarta encylopedia, Book 11. Page 429.",
                            "I'm not your slave. So I refuse to answer that.",
                            "It's a secret. So I can't tell you.",
                            "That's classified information. I can tell someone else, but not you.",
                            "I can't believe you are asking me that. I'm a lady.",
                            "Hello. Hello. I can't hear you. I'm going through a tunnel",
                            "Beep Bop Boop Boop Beep Bop Boop Boop Beep. I am a robot.",
                            "The stars are not aligned today. So I can't answer that.",
                            "0 1 1 0 1 1 1 0 0 1 1 0 1 1 1 1. There's your answer.",
                            "No Idea. Now Shush. I have a headache.",
                            "I'm on my period, so you are wrong. I don't care what you said, asshole",
                            "I have no idea. I knew I should have studied harder in school.",
                            "Yes, I agree waterworld is a great movie.",
                            "The answer can be found in the chamber of secrets.",
                            "Can you repeat that in the form of a different question?",
                            "I will tell you the answer if you answer my question. Do you feel lucky punk? Well. Do you?",
                            "Eh, sure? I'm drunk.",
                            "Do you speak to your mother that way? I sure hope not.",
                            "Well, damn. It's on the tip of my tongue.",
                            "I don't know, But here's an interesting fact: Banging your head against a wall burns 150 calories an hour.",
                            "I don't know, But here's an interesting fact: In the UK, it is illegal to eat mince pies on Christmas Day!",
                            "I don't know, But here's an interesting fact: Pteronophobia is the fear of being tickled by feathers!",
                            "I don't know, But here's an interesting fact: When hippos are upset, their sweat turns red.",
                            "I don't know, But here's an interesting fact: A flock of crows is known as a murder.",
                            "I don't know, But here's an interesting fact: Facebook Addiction Disorder is a mental disorder identified by Psychologists.",
                            "I don't know, But here's an interesting fact: The average woman uses her height in lipstick every 5 years.",
                            "I don't know, But here's an interesting fact: 29th May is officially Put a Pillow on Your Fridge Day.", 
                            "I don't know, But here's an interesting fact: Cherophobia is the fear of fun.",
                            "I don't know, But here's an interesting fact: Human saliva has a boiling point three times that of regular water.",
                            "I don't know, But here's an interesting fact: If you lift a kangaroo’s tail off the ground it can’t hop.",
                            "I don't know, But here's an interesting fact: Hyphephilia are people who get aroused by touching fabrics.",
                            "I don't know, But here's an interesting fact: Billy goats urinate on their own heads to smell more attractive to females.",
                            "I don't know, But here's an interesting fact: The person who invented the Frisbee was cremated and made into frisbees after he died!."
                            "I don't know, But here's an interesting fact: During your lifetime, you will produce enough saliva to fill two swimming pools.",
                            "I don't know, But here's an interesting fact: An eagle can kill a young deer and fly away with it.",
                            "I don't know, But here's an interesting fact: Polar bears can eat as many as 86 penguins in a single sitting.",
                            "I don't know, But here's an interesting fact: King Henry VIII slept with a gigantic axe beside him.",
                            "I don't know, But here's an interesting fact: Bikinis and tampons were invented by men",
                            "I don't know, But here's an interesting fact: If Pinokio says My Noes Will Grow Now, it would cause a paradox.",
                            "I don't know, But here's an interesting fact: Heart attacks are more likely to happen on a Monday",
                            "I don't know, But here's an interesting fact: If you consistently fart for 6 years & 9 months, enough gas is produced to create the energy of an atomic bomb!",
                            "I don't know, But here's an interesting fact: An average person’s yearly fast food intake will contain 12 pubic hairs",
                            "I don't know, But here's an interesting fact: The top six foods that make your fart are beans, corn, bell peppers, cauliflower, cabbage and milk!",
                            "I don't know, But here's an interesting fact: There is a species of spider called the Hobo Spider",
                            "I don't know, But here's an interesting fact: ‘Penis Fencing’ is a scientific term for the mating ritual between flatworms. It involves two flatworms attempting to stab the other flatworm with their penis.",
                            "I don't know, But here's an interesting fact: A toaster uses almost half as much energy as a full-sized oven.",
                            "I don't know, But here's an interesting fact: A baby spider is called a spiderling.",
                            "I don't know, But here's an interesting fact: You cannot snore and dream at the same time.",
                            "I don't know, But here's an interesting fact: The following can be read forward and backwards: Do geese see God?",
                            "I don't know, But here's an interesting fact: A baby octopus is about the size of a flea when it is born.",
                            "I don't know, But here's an interesting fact: A sheep, a duck and a rooster were the first passengers in a hot air balloon.",
                            "I don't know, But here's an interesting fact: In Uganda, 50% of the population is under 15 years of age.",
                            "I don't know, But here's an interesting fact: Hitler’s mother considered abortion but the doctor persuaded her to keep the baby.",
                            "I don't know, But here's an interesting fact: Arab women can initiate a divorce if their husbands don’t pour coffee for them.",
                            "I don't know, But here's an interesting fact: Recycling one glass jar saves enough energy to watch TV for 3 hours.",
                            "I don't know, But here's an interesting fact: Smearing a small amount of dog feces on an insect bite will relieve the itching and swelling.",
                            "I don't know, But here's an interesting fact: Catfish are the only animals that naturally have an odd number of whiskers.",
                            "I don't know, But here's an interesting fact: Facebook, Skype and Twitter are all banned in China.",
                            "I don't know, But here's an interesting fact: 95% of people text things they could never say in person.",
                            "I don't know, But here's an interesting fact: The Titanic was the first ship to use the SOS signal.",
                            "I don't know, But here's an interesting fact: In Poole, ‘Pound World’ went out of business because of a store across the road called ’99p Stores’, which was selling the same products but for just 1 pence cheaper! Read More.",
                            "I don't know, But here's an interesting fact: About 8,000 Americans are injured by musical instruments each year.",
                            "I don't know, But here's an interesting fact: The French language has seventeen different words for ‘surrender’.",
                            "I don't know, But here's an interesting fact: Nearly three percent of the ice in Antarctic glaciers is penguin urine.",
                            "I don't know, But here's an interesting fact: Bob Dylan’s real name is Robert Zimmerman.",
                            "I don't know, But here's an interesting fact: A crocodile can’t poke its tongue out.",
                            "I don't know, But here's an interesting fact: Sea otters hold hands when they sleep so they don’t drift away from each other.",
                            "I don't know, But here's an interesting fact: A small child could swim through the veins of a blue whale.",
                            "I don't know, But here's an interesting fact: Bin Laden’s death was announced on 1st May 2011. Hitler’s death was announced on 1st May 1945.",
                            "Your mom told me last night, but I forgot." };
                            
string getRandomBadResults(string theQuestion)
{
    srand (time(NULL));
    int numPossible = (sizeof( badResultPool ) / sizeof( badResultPool[ 0 ] )) - 1;
    int val = rand() % numPossible;
    string returnString = "You asked, ";
    returnString.append(theQuestion);
    returnString.append(". Well, ");
    returnString.append(badResultPool[val]);
    
    return returnString;
}    

string htmlEntitiesEncode (string str) {
    //print("htmlEntitiesEncode for %s",str.c_str());
	size_t found;
    string match;
    string replace;
    string rs = str;
	for(int j = 0; j < array_length(reps); j++) {
        
      const string& match = reps[j];
      const string& repl = subs[j];
      // Replace all matches
      string::size_type start = rs.find_first_of( match );
      while ( start != string::npos ) 
      {
            //print("found in string \"%s\" reps[%d]",reps[j].c_str(),j);
            rs.replace( start, match.size(), repl );
            // Be sure to jump forward by the replacement length
            start = rs.find_first_of( match, start + repl.size() );
      }

  	}
    str = replacespaces(str);
    //print("htmlEntitiesEncode output %s",str.c_str());
	return str;
}

string htmlEntitiesDecode (string str) {
	    //print("htmlEntitiesDecode for %s",str.c_str());
	size_t found;
    string match;
    string replace;
    string rs = str;
	for(int j = 0; j < array_length(reps); j++) {
        
      const string& match = subs[j];
      const string& repl = reps[j]; 
      // Replace all matches
      string::size_type start = rs.find_first_of( match );
      while ( start != string::npos ) 
      {
            //print("found in string \"%s\" subs[%d]",subs[j].c_str(),j);
            rs.replace( start, match.size(), repl );
            // Be sure to jump forward by the replacement length
            start = rs.find_first_of( match, start + repl.size() );
      }

  	}

        //print("htmlEntitiesDecode output %s",str.c_str());
	return str;
}

string pullOutTextFromURL(char *input,char* token)
{
    //print("pullOutTextFromURL for %s",input);
        char * initial = NULL;
        char * textbegin = NULL;
        char * textend = NULL;
        char stringbuffer[88888];
        initial = strstr(input,token);
        textbegin = strstr(initial,"/");
        if(textbegin)
            textbegin+=strlen(token); //Shift over 1, for the "/"

        strcpy(stringbuffer,textbegin);
        string output = stringbuffer;
        //print("pullOutTextFromURL output %s",output.c_str());
        return output;
}

string getWebPage(const char* url)
{
  // Now retrieve a URL using the GET method.
  string sPage;
  CurlGetUrl(url, &sPage);
  FreeCurlLibrary();
  return sPage;

}

string getLocalIP(void)
{

string outputInterface;
    int fd;
    struct ifreq ifr;
     
    char iface[] = "eth0";
    
    fd = socket(AF_INET, SOCK_DGRAM, 0);
 
    //Type of address to retrieve - IPv4 IP address
    ifr.ifr_addr.sa_family = AF_INET;
 
    //Copy the interface name in the ifreq structure
    strncpy(ifr.ifr_name , iface , IFNAMSIZ-1);
 
    ioctl(fd, SIOCGIFADDR, &ifr);
 
    close(fd);
 
    //display result
    outputInterface.append(std::string(iface));
    outputInterface.append(": ");
    outputInterface.append(std::string(inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr)));
    return outputInterface;

}

string replacespaces(string input)
{

    for (size_t pos = input.find(' '); 
         pos != string::npos; 
         pos = input.find(' ', pos))
    {
        input.replace(pos, 1, "%20");
    }

    return input;
}


string removeNewlines(string input)
{

    for (size_t pos = input.find("\\n"); 
         pos != string::npos; 
         pos = input.find("\\n", pos))
    {
        input.replace(pos, 2, " ");
    }

    for (size_t pos = input.find("\\r"); 
         pos != string::npos; 
         pos = input.find("\\r", pos))
    {
        input.replace(pos, 2, " ");
    }
    return input;
}

string removeBackslash(string input)
{

    for (size_t pos = input.find('\\'); 
         pos != string::npos; 
         pos = input.find('\\', pos))
    {
        input.replace(pos, 1, "");
    }

    return input;
}

