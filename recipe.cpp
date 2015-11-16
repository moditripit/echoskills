#include "recipe.h"
#include "recipelist.h" //temporary

using namespace std;

static unsigned int lastID = 0;

Recipe::Recipe()
{
        id                      = ++lastID;
        uniqueid                = 0;
        number_of_keywords      = 0;
        number_of_steps         = 0;
        number_of_ingredients   = 0 ;
        
}

void Recipe::addKeyword(string keyword)
{
        Keywords.push_back(keyword);
        number_of_keywords++;
}

void Recipe::addStep(string step)
{
       Steps.push_back(step);
       number_of_steps++;
}

void Recipe::addIngredient(string ingredient)
{
       Ingredients.push_back(ingredient);
       number_of_ingredients++;
}

int Recipe::importRecipe(string file)
{    
    //TODO: Put recipes in xml or file form and read it here
    std::size_t found;
  
    if(file.find("scone") != std::string::npos)
    {
        uniqueid = scone_id;
        addKeyword("scone");
        addKeyword("scones");
        recipeName.assign(scone_title); 
        int numSteps = (sizeof( sconerecipe ) / sizeof( sconerecipe[ 0 ] ));
        int i = 0;
        for( i = 0; i < numSteps ; i++ )
        {
            addStep(sconerecipe[i]);
        }
        
        int numIngredient = (sizeof( sconeingredients ) / sizeof( sconeingredients[ 0 ] ));
        for( i = 0; i < numIngredient ; i++ )
        {
            addIngredient(sconeingredients[i]);
        }
        return uniqueid;
    }
    else if(file.find("pumpkin") != std::string::npos)
    {
        uniqueid = pumpkinbread_id;
        recipeName.assign(pumpkinbread_title);
        addKeyword("pumpkin");
        addKeyword("pumpkin bread");
        
        int numSteps = (sizeof( pumpkinbreadrecipe ) / sizeof( pumpkinbreadrecipe[ 0 ] ));
        int i = 0;
        for( i = 0; i < numSteps ; i++ )
        {
           // print("adding step to vector (%s)\n",pumpkinbreadrecipe[i]);
            addStep(pumpkinbreadrecipe[i]);
        }
        
        int numIngredient = (sizeof( pumpkinbreadingredients ) / sizeof( pumpkinbreadingredients[ 0 ] ));
        for( i = 0; i < numIngredient ; i++ )
        {
           // print("adding ingredient to vector (%s)\n",pumpkinbreadingredients[i]);
            addIngredient(pumpkinbreadingredients[i]);
        } 
        return uniqueid;
    }
    else
    {
        return 0;
    }
    
}
