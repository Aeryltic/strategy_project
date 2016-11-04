#ifndef GRID_H
#define GRID_H

#include "Settlement.h"
#include "Resources.h"
const int NEUTRAL_COLOR = 0;
enum
{
    WATER,LAND,
    AVAILABLE_LAND_TYPES
};
class Grid
{
    public:
    //--(CONS/DES)TRUCTORS--------------------------------------------------------------
        Grid(){}
        Grid(int type,int x,int y);
        virtual ~Grid();
    //--SETTLEMENT_MANAGEMENT-----------------------------------------------------------
        bool buildSettlement();
        bool destroySettlement();
        Settlement * getSettlement(){return settlement_;}
    //--OWNERSHIP-----------------------------------------------------------------------
        bool isOwned(){return owned_;}
        void setOwned(){owned_ = 1;}
        void unsetOwned(){owned_ = 0;}
    //--RESOURCES-----------------------------------------------------------------------
        Resources * resources(){return &natural_resources_;}
        void renewResources();
    //--POSITION------------------------------------------------------------------------
        int posX(){return coor_x_;}
        int posY(){return coor_y_;}
    //--COLOR---------------------------------------------------------------------------
        int inactiveColor(){return color_;}
        int activeColor(){return color_ + 1;}
        void setColor(int color){color_ = color;}
        void unsetColor(){color_ = NEUTRAL_COLOR;}
    //--MISC----------------------------------------------------------------------------
        int getType(){return type_;}
        string info();
    //--VISITOR-------------------------------------------------------------------------
        void setVisitor(void * visitor, int color){group_ = visitor; color_ = color;}
        void unsetVisitor(){group_ = 0; unsetColor();}
        void * getVisitor(){return group_;}
        bool hasVisitor(){return group_ != 0;}
    //--DISCOVER------------------------------------------------------------------------
        void discover(){discovered_ = true;}
        bool isDiscovered(){return discovered_;}
    //--ACTIVE--------------------------------------------------------------------------
        void setActive(){active_ = true;}
        void setInactive(){active_ = false;}
        bool isActive(){return active_;}

    protected:
    private:

        friend class World;
        int type_;
        Resources natural_resources_;
        Settlement * settlement_;
        int coor_x_,coor_y_;
        bool owned_;
        int color_;

        void * group_;
        bool discovered_;
        bool active_;

 //   private:

};

#endif // GRID_H
