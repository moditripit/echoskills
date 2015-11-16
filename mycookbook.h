#ifndef MYCOOKBOOK_H
#define MYCOOKBOOK_H

#include <stdio.h> //printf
#include <stdlib.h> //random values
#include <sstream>  // manipulate strings (integer conversion) 
#include <string.h>
#include "recipe.h"
#include <vector>
#include "logging.h"

class MyCookbook {

protected:

    int RecipeIndex;
    int TotalSteps;
    int TotalIngredients;
    //unsigned int currentrecipeid;
    int recipestep;
    //Recipe currentRecipe;
    //std::vector<Recipe> Recipes;

public:
        MyCookbook();
        int FindRecipe(char * input);
        string getRecipe(char * input);

};
#endif //#define MYCOOKBOOK_H

