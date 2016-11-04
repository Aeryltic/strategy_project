#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include "Nation.h"
#include "World.h"

#include "structs.h"

#include <vector>

#include <curses.h>

using namespace std;

const int SCREEN_HEIGHT = 70;
const int SCREEN_WIDTH = 100;

const int MAPX=5;
const int MAPY=5;

const int COLOR_GREY = COLOR_WHITE + 1;
const unsigned MAX_NATIONS = 3;



enum
{
    WHITE_BLACK = 0,
    WHITE_GREY,

    RED_BLACK,
    RED_GREY,

    GREEN_BLACK,
    GREEN_GREY,

    BLUE_BLACK,
    BLUE_GREY,

    COLOR_PAIR_COUNT
};

class GameInstance
{
    public:

        GameInstance();
        virtual ~GameInstance();

        void run();

    protected:
    private:

//------VARIABLES-------------------------------------------------------------------------------------------------

        World * world_;
        Grid * active_grid_;

        vector<Nation*> nation_;
        Nation * player_nation_;

        point pointer_;

        bool running_;
        bool needs_printing_;

        unsigned pressed_key_;
        int tick_;

        int mode_;

        bool round_end_;

        unsigned round_number_;

//------FUNCTIONS-------------------------------------------------------------------------------------------------

        void update();
        void print();

        string info();

        void newGame();
        bool createWorld(int height,int width);
        bool addPlayerNation();
        bool addCPUNation();
        int nextNationColor();

        void printMap(); // mostly done
        void printUI(); // to do

        bool isAtMap(int x,int y){return x >= MAPX && x < MAPX+world_->getWidth()*2 &&
                                         y >= MAPY && y < MAPY+world_->getHeight()*2;}
        void convertToMapCoor(int & x, int & y)
        {
            x-=MAPX;
            y-=MAPY;
            x/=2;
            if(x%2)y--;
            y/=2;
        }
        void convertToAbsoluteCoor(int & x, int & y)
        {
            y*=2;
            if(x%2)y++;
            x*=2;
            y+=MAPY;
            x+=MAPX;
        }

    //--CONTROLS--------------------------------------------------------------------------------------------------

        void updatePointer();

        bool endingSignalSent();

        void fprintw(int y,int x,string str);

        bool approveAction(char * str);

        void resetMode(){mode_ = MODE_NO_ACTION;}

};

#endif // GAMEINSTANCE_H
