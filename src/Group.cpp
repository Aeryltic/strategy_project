#include "Group.h"

#include "MiscFunctions.h"
#include "Variables.h"

//Resources basic_settlement_req_res(0,0,100,100,0);

const int MAX_GATHERED_FOOD = 5;
const int MAX_GATHERED_WATER = 4;
const int MAX_GATHERED_WOOD = 3;
const int MAX_GATHERED_STONE = 1;
const int MAX_GATHERED_IRON = 0;

Group::Group()
{
    home_ = NULL;
}
Group::Group(void *nation, int color, int men,int women, char * name, Resources resources)
{
    color_ = color;
    men_count_ = men;
    women_count_ = women;
    home_ = NULL;
    curr_grid_ = NULL;
    name_ = name;
    backpack_ = resources;
    nation_ = nation;
}

Group::~Group()
{
    //dtor
}

Group * Group::split(int men,int women)
{
    if(men>men_count_)men=men_count_;
    if(women>women_count_)women=women_count_;

    men_count_ -= men;
    women_count_ -= women;

   // Group * group = new Group(men,women);
    return new Group(nation_, color_, men, women, (char*)(name_+string("\'")).c_str(), Resources(0,0,0,0,0));
}

string Group::info()
{
    string info;
    info+="NAME: "+name_+"\nMEN: "+to_string(men_count_)+"\nWOMEN: "+to_string(women_count_)+'\n'+backpack_.state();
    return info;
}

bool Group::doTask()
{
    if(!action_performed_)
    {
        bool performed=false;
        switch (task_)
        {
        case MODE_MOVE:
            performed=moveToGrid(dest_grid_);
            break;
        case MODE_BUILD_SETTLEMENT:
            performed=buildSettlement();
            break;
        case MODE_GATHER_RESOURCES:
            performed=gatherResources();
            break;
        default:
            break;
        }
        action_performed_ = performed;
    }
    return action_performed_;
}

bool Group::buildSettlement()
{
    if(Resources(basic_settlement_req_res)<=backpack_ && (!curr_grid_->isOwned() || curr_grid_ == home_ ))
    {
        if (home_ != curr_grid_)
        {
            home_ = curr_grid_;
        }
        curr_grid_->buildSettlement();
        useResources(basic_settlement_req_res);
        return true;
    }
    return false;
}

bool Group::gatherResources()
{
    if(curr_grid_ == home_ || !curr_grid_->isOwned())
    {
        unsigned
            food = MAX_GATHERED_FOOD * (men_count_ + women_count_),
            water = MAX_GATHERED_WATER * (men_count_ + women_count_),
            wood = MAX_GATHERED_WOOD * (men_count_ + women_count_),
            stone = MAX_GATHERED_STONE * (men_count_ + women_count_),
            iron = MAX_GATHERED_IRON * (men_count_ + women_count_);

        if( food > curr_grid_->resources()->food_) food = curr_grid_->resources()->food_;
        backpack_.food_ += food;
        curr_grid_->resources()->food_ -= food;

        if( water > curr_grid_->resources()->water_) water = curr_grid_->resources()->water_;
        backpack_.water_ += water;
        curr_grid_->resources()->water_ -= water;

        if( wood > curr_grid_->resources()->wood_) wood = curr_grid_->resources()->wood_;
        backpack_.wood_ += wood;
        curr_grid_->resources()->wood_ -= wood;

        if( stone > curr_grid_->resources()->stone_) stone = curr_grid_->resources()->stone_;
        backpack_.stone_ += stone;
        curr_grid_->resources()->stone_ -= stone;

        if( iron> curr_grid_->resources()->iron_) iron = curr_grid_->resources()->iron_;
        backpack_.iron_ += iron;
        curr_grid_->resources()->iron_ -= iron;

        return true;
    }
    return false;
}

bool Group::haveSufficientResources(Resources needed)
{
    return needed <= backpack_;
}
bool Group::moveToGrid(Grid * grid)
{
    if(curr_grid_)curr_grid_->unsetVisitor();
    curr_grid_ = grid;
    curr_grid_->setVisitor((void*)this,color_);
    return true;
}
void Group::useResources(Resources res)
{
    backpack_ -= res;
}
void Group::addResouces(Resources res)
{
    backpack_ += res;
}
