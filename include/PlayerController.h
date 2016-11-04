#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Nation.h"

class PlayerController
{
    public:
        PlayerController(Nation * nation);
        virtual ~PlayerController();

        void getKey(char key);

    protected:

    private:
        Nation * player_nation_;
};

#endif // PLAYERCONTROLLER_H
