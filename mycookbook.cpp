#include "mycookbook.h"
//#include "recipelist.h"

using namespace std;

enum RecipeSteps { NAME = 0, INGREDIENTS = 1, STEPONE = 2};

Recipe currentRecipe;
int currentrecipeid = 0;
               
MyCookbook::MyCookbook()
{
    RecipeIndex = -1;
    TotalSteps = 0;
    TotalIngredients = 0;
    //currentrecipeid = 0;
    recipestep = 0;
}

int MyCookbook::FindRecipe(char * input)
{
    //TODO: Keep local copy and keywords
        // So I don't have to read the file every time
    //TODO: This is only for right now
    //Deleting last recipe
    Recipe reset;
    currentRecipe = reset;
    //This is temporary ^
        //print("Finding recipe %s\n",input);
        
    return currentRecipe.importRecipe(input);
       
}

string MyCookbook::getRecipe(char * input)
{
    string returnString;
    int read = 0;
    int newrecipe = 0;
    int askedForName = 0;
    //Controls
    if(strstr(input, "repeat") != NULL && currentrecipeid > 0)
    {
        read = 1;
    }
    else if(strstr(input, "next") != NULL && currentrecipeid > 0)
    {
        recipestep++;
        read = 1;
    }
    else if((strstr(input, "last") != NULL ||
            strstr(input, "previous") != NULL) && currentrecipeid > 0)
    {
            if(recipestep != INGREDIENTS)
            {
                recipestep--;
            }
                
            read = 1;
    }
    else if(strstr(input, "first") != NULL && currentrecipeid > 0)
    {
        recipestep = 1;
        read = 1;
    }
    else if((strstr(input, "step") != NULL || strstr(input, "which") != NULL) && currentrecipeid > 0)
    {
        returnString.append("You are on ");
        read = 1;
    }
    else if((strstr(input, "name") != NULL ||
            strstr(input, "title") != NULL ||
            strstr(input, "call") != NULL) && currentrecipeid > 0 )
    {

            return currentRecipe.recipeName;
        
    }
    else if(strstr(input, "ingredient") != NULL && currentrecipeid > 0)
    {
        recipestep = NAME;
        read = 1;
    }
    else
    {
        
        int found = FindRecipe(input);
        if (found == 0)
        {
            if(currentrecipeid == 0)
            {
                return "Please ask for a recipe first";
            }
            return "Could not process your request";
        }
        print("Found new Recipe, id = %d\n",found);
        //print("currentRecipe.Steps[0] = %s\n",currentRecipe.Steps.at(0).c_str());
        //print("Getting Recipe id=%d\n",currentrecipeid);

        if((currentrecipeid  != found) && found > 0)
        {
            recipestep = INGREDIENTS;
            currentrecipeid  = currentRecipe.uniqueid;
            newrecipe = 1;
        }
        else
        {
            print("same recipe found currentrecipeid = %d \n",currentrecipeid);
            //print("same recipe found currentRecipe.uniqueid = %d \n",currentRecipe.uniqueid);
        }
        
        read = 1;
    }

    //print("After controls \n");

    //Recipe narration
    //Title of Recipe
    if (askedForName == 1 || newrecipe == 1 )
    {
        returnString.append(currentRecipe.recipeName);
        if(newrecipe)
        {
            recipestep = INGREDIENTS;
        }
    }
    
    
    //Ingredients / Steps
    if(recipestep == INGREDIENTS && read == 1)
    {

        int i = 0;
        for(i = 0; i < currentRecipe.number_of_ingredients; i++)
        {
            returnString.append(currentRecipe.Ingredients.at(i));
        }


    }
    else if( read == 1 && (recipestep >= STEPONE && recipestep < currentRecipe.number_of_steps+STEPONE))
    {
        returnString.append(currentRecipe.Steps.at(recipestep-STEPONE));
        //print("Recipe Step %d Grabbed (%s)\n",recipestep,returnString.c_str());
    }
    else
    {
        returnString.append("Wait. and Enjoy.");
        recipestep = currentRecipe.number_of_steps;
        print("Hit default case, no more steps? recipestep is %d\n",recipestep);
        print("Hit default case, Recipe id=%d\n",currentrecipeid);

    }

    return returnString;
}
