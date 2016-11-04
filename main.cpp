#include "GameInstance.h"
//#include <iostream>
using namespace std;
int main()
{
    GameInstance * gameInstance=new GameInstance;
    gameInstance->run();
    delete gameInstance;
    return 0;
  //  cout<<"all good"<<endl;
}
