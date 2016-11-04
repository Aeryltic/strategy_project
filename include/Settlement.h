#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <string>
#include <vector>
#include "Building.h"

using namespace std;
/*
Plany:
    a) funkcje:
        - buduj�ca odpowiednie budynki (a p�niej, zlecaj�ca budow� osobnej instancji budynku)
        - ulepszaj�ca odpowiedni rodzaj budynk�w (a p�niej, odpowiednie instancje budynk�w)
        - licz�ca zu�ycie (przychody i koszty) zasob�w w rundzie
    b) pola:
        - klasy budynk�w
        - vectory budynk�w tak aby m�c pracowa� na ka�dym budynku z osobna
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
