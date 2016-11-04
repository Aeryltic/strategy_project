#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include "Resources.h"

const char LAND_CHAR = '#';
const char WATER_CHAR = '~';

//----LAND-------------------------------------
const int WATER_LAND_START_VALUE = 100;
const int WATER_LAND_OSC = 100;

const int FOOD_LAND_START_VALUE = 30;
const int FOOD_LAND_OSC = 40;

const int WOOD_LAND_START_VALUE = 50;
const int WOOD_LAND_OSC = 250;

const int STONE_LAND_START_VALUE = 30;
const int STONE_LAND_OSC = 100;

const int IRON_LAND_START_VALUE = 5;
const int IRON_LAND_OSC = 50;

//---WATER-------------------------------------
const int WATER_WATER_START_VALUE = 1000;
const int WATER_WATER_OSC = 100;

const int FOOD_WATER_START_VALUE = 50;
const int FOOD_WATER_OSC = 40;

const int WOOD_WATER_START_VALUE = 0;
const int WOOD_WATER_OSC = 0;

const int STONE_WATER_START_VALUE = 0;
const int STONE_WATER_OSC = 0;

const int IRON_WATER_START_VALUE = 0;
const int IRON_WATER_OSC = 0;

//---------------------------------------------


const Resources basic_settlement_req_res(0,0,100,100,0);

#endif // VARIABLES_H_INCLUDED
