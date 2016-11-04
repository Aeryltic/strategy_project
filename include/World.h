#ifndef WORLD_H
#define WORLD_H

#include "Settlement.h"
#include "Grid.h"

using namespace std;


class World
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------ENUMS----------------------------------------------------------------------------------------------------------
    enum
    {
        WATER,LAND,
        AVAILABLE_LAND_TYPES
    };
//=====================================================================================================================

    public:
        World(unsigned width,unsigned height);
        World();
        virtual ~World();
        unsigned getWidth(){return width_;}
        unsigned getHeight(){return height_;}
        void build();
        Grid * getGrid(int x,int y){if(y>=0 && y<height_ && x>=0 && x<width_)return grid_[y][x];return 0;}

//-------MISC----------------------------------------------------------------------------------------------------------
        string info();
        string map_str();
//---------------------------------------------------------------------------------------------------------------------
    protected:
    private:
        unsigned width_,height_;
        Grid *** grid_;
};

#endif // WORLD_H
