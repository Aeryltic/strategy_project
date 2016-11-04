#include "Resources.h"

#include "MiscFunctions.h"

const int RESOURCE_TYPES = 5;

Resources::Resources(unsigned water,unsigned food,unsigned wood,unsigned stone,unsigned iron)
{
    water_=water;
    food_=food;
    wood_=wood;
    stone_=stone;
    iron_=iron;
}
Resources::Resources()
{
    water_=food_=wood_=stone_=iron_=0;
}
Resources::~Resources()
{
    //dtor
}

void Resources::set(unsigned water,unsigned food,unsigned wood,unsigned stone,unsigned iron)
{
    water_=water;
    food_=food;
    wood_=wood;
    stone_=stone;
    iron_=iron;
}

string Resources::state()
{
    string state="FOOD:  "+to_string(food_)+
                 "\nWATER: "+to_string(water_)+
                 "\nWOOD:  "+to_string(wood_)+
                 "\nSTONE: "+to_string(stone_)+
                 "\nIRON:  "+to_string(iron_);
    return state;
}

