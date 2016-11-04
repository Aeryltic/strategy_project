#include "Nation.h"
#include "MiscFunctions.h"

Nation::Nation()
{
    owner_ = CPU_CONTROLLER;
    group_.push_back(new Group((void*)this, color_, 20,20,(char*)"main_group"));
}

Nation::Nation(int owner, string name, int color)
{
 //   this->Nation();
    color_ = color;
    owner_ = owner;
    name_ = name;
    group_.push_back(new Group((void*)this, color_, 20, 20, (char*)"main_group"));
}

Nation::Nation(int owner, const char * name, int color)
{
  //  this->Nation();
    color_ = color;
    owner_ = owner;
    name_ = name;
    group_.push_back(new Group((void*)this, color_, 20,20,(char*)"main_group"));
}

Nation::~Nation()
{
    for(unsigned i=0; i<group_.size(); i++)delete group_[i];
    group_.clear();
}

string Nation::info()
{
    string info="NAME: "+name_+"\nCOLOR: "+to_string(color_)+"\nGROUPS: ("+to_string(group_.size())+")";
    for(unsigned i=0;i<group_.size();i++)info+="\n\t"+group_[i]->getName();
    return info;
}
