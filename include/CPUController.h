#ifndef CPUCONTROLLER_H
#define CPUCONTROLLER_H

#include "Nation.h"

class CPUController
{
    public:

        CPUController();
        virtual ~CPUController();

        void setControlledNation(Nation * nation){controlled_nation_=nation;}
        Nation * getControlledNation(){return controlled_nation_;}

        void control();
    protected:
    private:

        Nation * controlled_nation_;

};

#endif // CPUCONTROLLER_H
