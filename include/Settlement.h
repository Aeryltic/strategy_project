#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <string>
#include <vector>
#include "Building.h"

using namespace std;
/*
Plany:
    a) funkcje:
        - buduj¹ca odpowiednie budynki (a póŸniej, zlecaj¹ca budowê osobnej instancji budynku)
        - ulepszaj¹ca odpowiedni rodzaj budynków (a póŸniej, odpowiednie instancje budynków)
        - licz¹ca zu¿ycie (przychody i koszty) zasobów w rundzie
    b) pola:
        - klasy budynków
        - vectory budynków tak aby móc pracowaæ na ka¿dym budynku z osobna
*/
class Settlement
{
    public:
        Settlement(string name="settlement");
        virtual ~Settlement();

        string name(){return name_;}
        int beds(){return houses_*house_capacity_;}
        bool buildHouse();
        bool upgradeHouses();
        string info();

    protected:
    private:
        vector<Building> building;
        string name_;
        int water_stock_,food_stock_,wood_stock_,stone_stock_,iron_stock_;
        int houses_;
        int house_capacity_,storage_capacity_;
        int house_lvl;
};

#endif // SETTLEMENT_H
