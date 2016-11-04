#include "Settlement.h"

Settlement::Settlement(string name)
{
    water_stock_=food_stock_=wood_stock_=stone_stock_=iron_stock_=houses_=0;
    name_=name;
}

Settlement::~Settlement()
{
    //dtor
}

/*
            Procedura budowy/ulepszania:
             - liczymy ile potrzeba materia��w
             - sprawdzamy czy wystarcza
             - je�li tak to wykonujemy
             Trzeba to �adnie zapakowa�...
              - tablica potrzebnych sk�adnik�w
              - proste funkcje wykonywane po spe�eniu warunk�w
*/
bool Settlement::buildHouse()
{
    // liczymy ile potrzeba (tu trzeba jakiej� og�lnej funkcji)
    int required_wood;//=houses_*required_wood_for_upgrade;
    int required_stone;
    int required_iron;
    // sprawdzamy czy wystarcza
    bool enough_wood=1;//required_wood<=wood_stock_;
    bool enough_stone=1;//required_stone<=stone_stock_;
    bool enough_iron=1;//required_iron<=iron_stock_;
    if (enough_wood && enough_stone && enough_iron)
    {
        // je�li tak to dzia�amy
        wood_stock_-=required_wood;
        stone_stock_-=required_stone;
        iron_stock_-=required_iron;
        return 1;
    }
    else
    {
        // je�li nie to nie (pewnie co� tam si� wy�wietli)
        return 0;
    }
}
bool Settlement::upgradeHouses()
{
    bool canUpgrade=false;
    if(canUpgrade)
    {
        return true;
    }
    else return false;
}

string Settlement::info()
{
    string info;
    info+=name_;
    return info;
   // int houses =
}
