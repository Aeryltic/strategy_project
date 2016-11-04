#include "PlayerController.h"

PlayerController::PlayerController(Nation * nation)
{
    player_nation_ = nation;
}

PlayerController::~PlayerController()
{
    //dtor
}

void getKey(char key);
