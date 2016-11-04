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
             - liczymy ile potrzeba materia³ów
             - sprawdzamy czy wystarcza
             - jeœli tak to wykonujemy
             Trzeba to ³adnie zapakowaæ...
              - tablica potrzebnych sk³adników
              - proste funkcje wykonywane po spe³eniu warunków
*/
bool Settlement::buildHouse()
{
    // liczymy ile potrzeba (tu trzeba jakiejœ ogólnej funkcji)
    int required_wood;//=houses_*required_wood_for_upgrade;
    int required_stone;
    int required_iron;
    // sprawdzamy czy wystarcza
    bool enough_wood=1;//required_wood<=wood_stock_;
    bool enough_stone=1;//required_stone<=stone_stock_;
    bool enough_iron=1;//required_iron<=iron_stock_;
    if (enough_wood && enough_stone && enough_iron)
    {
        // jeœli tak to dzia³amy
        wood_stock_-=required_wood;
        stone_stock_-=required_stone;
        iron_stock_-=required_iron;
        return 1;
    }
    else
    {
        // jeœli nie to nie (pewnie coœ tam siê wyœwietli)
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
