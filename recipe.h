#ifndef RECIPE_H
#define RECIPE_H

#include <stdio.h> //printf
#include <stdlib.h> //random values
#include <sstream>  // manipulate strings (integer conversion) 
#include <string.h>
#include <vector>
#include "logging.h"

using namespace std;

class Recipe {

public:
        Recipe();
        int importRecipe(string file);
        int id;
        int uniqueid;
        
        int number_of_steps;
        int number_of_ingredients;
        int number_of_keywords;
        string recipeName;
        std::vector<std::string> Steps;
        std::vector<std::string> Ingredients;
        std::vector<std::string> Keywords;
        
protected:

    void addKeyword(string keyword);
    void addStep(string step);
    void addIngredient(string ingredient);
};
#endif //#define RECIPE_H

