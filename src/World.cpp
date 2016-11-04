#include "World.h"

#include <cstdlib>
#include <iostream>
#include "MiscFunctions.h"

using namespace std;
World::World(unsigned width,unsigned height)
{
    width_=width;
    height_=height;
    grid_=new Grid**[height_];
    for(unsigned i=0;i<height_;i++)
    {
        grid_[i]=new Grid*[width_];
    }
}
World::World()
{
    width_=height_=0;
    grid_=0;
}
World::~World()
{
   // cout<<"deleting: world"<<endl;
    if(height_ && grid_)
    {
        for(unsigned i=0;i<height_;i++)
        {
            for(unsigned j=0;j<width_;j++)delete grid_[i][j];
            delete [] grid_[i];
        }
        delete [] grid_;
    }
  //  cout<<"deleted: world"<<endl;
}

void World::build()
{
    for(int i=0;i<height_;i++)
    {
        for(int j=0;j<width_;j++)
        {
            grid_[i][j]=new Grid(rand()%AVAILABLE_LAND_TYPES,j,i);
        }
    }
}

//-------MISC----------------------------------------------------------------------------------------------------------
string World::info()
{
//    grid_[0][0].type_;
//    string info="World size: "+to_string(width_)+"x"+to_string(height_)+"\n";
string info;//="";
/*
    for(int i=0;i<height_;i++)
    {
        for(int j=0;j<width_;j++)
        {
            info+="("+to_string(grid_[i][j]->type_)+","
                +to_string(grid_[i][j]->natural_resources_.water_)+","
                +to_string(grid_[i][j]->natural_resources_.food_)+","
                +to_string(grid_[i][j]->natural_resources_.wood_)+","
                +to_string(grid_[i][j]->natural_resources_.stone_)+","
                +to_string(grid_[i][j]->natural_resources_.iron_)+") ";
        }
        info+="\n";
    }
    */
    return info;
}
string World::map_str()
{
    string img; // "img"
    /*
    *   y=i*2;
    *   x=j%2 + j*2
    */
    for(int i=0;i<height_;i++)
    {
        if(i%2)img+=' ';
        for(int j=0;j<width_;j++)
        {
            switch (grid_[i][j]->type_)
            {
                case WATER:img+=' ';break;
                case LAND:img+='#';break;
            }
            img+=' ';
        }
        img+="\n\n";
    }
    return img;
}
