#ifndef GROUP_H
#define GROUP_H

#include "Grid.h"
#include "Resources.h"

#include <string>

using namespace std;

enum
{
    MOVE_TO_GRID,
    BUILD_SETTLEMENT,
    GATHER_RESOURCES,
    DO_NOTHING
};

enum
{
    MODE_NO_ACTION,
    MODE_MOVE,
    MODE_GATHER_RESOURCES,
    MODE_BUILD_SETTLEMENT,

    MODE_COUNT
};

class Group
{
    public:

        Group();
        Group(void * nation, int color, int men,int women, char * name, Resources resources=Resources(0,0,0,0,0));
      //  Group(int men,int women,char * name);
        virtual ~Group();
        //------FUNCTIONS---------------------------------------------------

        Group * split(int men,int women);

        void setTask(int taskID){task_ = taskID;}
        bool doTask();
        bool moveToGrid(Grid * grid);
        bool buildSettlement();
        bool gatherResources();

        void setHome(){home_ = curr_grid_;}
        void unsetHome(){home_ = 0;}

        void setName(string name){name_ = name;}
        string getName(){return name_;}

        string homeCityName(){
            return  (home_ && home_->getSettlement()) ?
                    (home_->getSettlement()->name()) :
                    (string("none"));
        }

        string info();
        int population(){return men_count_ + women_count_;}
        void setResources(Resources resources){backpack_ = resources;}

        bool haveSufficientResources(Resources needed);

        Grid * getGrid(){return curr_grid_;}

        void * getNation(){return nation_;}

        Resources * resources(){return &backpack_;}

        void setDestination(Grid * dest){dest_grid_ = dest;}

        void useResources(Resources res);
        void addResouces(Resources res);

    protected:
    private:
//------VARIABLES---------------------------------------------------
        string name_;
        int men_count_,women_count_;
        Grid *home_, *curr_grid_, *dest_grid_;
        Resources backpack_;
        int task_;

        bool action_performed_;
        int color_;

        void * nation_;

};

#endif // GROUP_H
