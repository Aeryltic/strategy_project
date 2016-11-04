#include "Grid.h"

#include <cstdlib>

#include "Variables.h"
#include "MiscFunctions.h"

Grid::Grid(int type,int x,int y)
{
    active_ = false;
    discovered_ = false;
    group_ = 0;
    color_ = NEUTRAL_COLOR;
    coor_x_ = x;
    coor_y_ = y;
    type_ = type;
    settlement_ = 0;
    switch (type_)
    {
        case WATER:
            natural_resources_.set(1000,500,0,0,0);
            /*
            water_amount_ = WATER_WATER_START_VALUE + WATER_WATER_OSC ? rand() % WATER_WATER_OSC : 0;
            food_amount_ = FOOD_WATER_START_VALUE + FOOD_WATER_OSC ? rand() % FOOD_WATER_OSC : 0;
            wood_amount_ = WOOD_WATER_START_VALUE + WOOD_WATER_OSC ? rand() % WOOD_WATER_OSC : 0;
            stone_amount_ = STONE_WATER_START_VALUE + STONE_WATER_OSC ? rand() % STONE_WATER_OSC : 0;
            iron_amount_ = IRON_WATER_START_VALUE + IRON_WATER_OSC ? rand() % IRON_WATER_OSC : 0;
            */
            break;
        case LAND:
            natural_resources_.set(100,150,200,100,100);
            /*
            water_amount_ = WATER_LAND_START_VALUE + WATER_LAND_OSC ? rand() % WATER_LAND_OSC : 0;
            food_amount_ = FOOD_LAND_START_VALUE + FOOD_LAND_OSC ? rand() % FOOD_LAND_OSC : 0;
            wood_amount_ = WOOD_LAND_START_VALUE + WOOD_LAND_OSC ? rand() % WOOD_LAND_OSC : 0;
            stone_amount_ = STONE_LAND_START_VALUE + STONE_LAND_OSC ? rand() % STONE_LAND_OSC : 0;
            iron_amount_ = IRON_LAND_START_VALUE + IRON_LAND_OSC ? rand() % IRON_LAND_OSC : 0;
            */
            break;
    }
    owned_ = 0;
}

Grid::~Grid()
{
    if (settlement_) delete settlement_;
}

bool Grid::buildSettlement()
{
    if(settlement_)return false;

    settlement_ = new Settlement();
    setOwned();

    return true;
}

bool Grid::destroySettlement()
{
    if(settlement_)
    {
        delete settlement_;
        settlement_ = 0;
        unsetOwned();
        unsetColor();
        return true;
    }
    return false;
}

string Grid::info()
{
    string info;

  //  info += "SETTLEMENT: ";
 //   if (!settlement_) info += "not built yet\n";
  //  else info +=settlement_->name();

    info +=     natural_resources_.state();

    return info;
}

void Grid::renewResources()
{

}


