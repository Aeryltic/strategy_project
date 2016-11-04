#ifndef NATION_H
#define NATION_H

#include <vector>
#include <string>

#include "Group.h"
#include "Enums.h"

using namespace std;
/*
Plany:
    a) funkcje:
        - buduj�ca odpowiednie budynki (a p�niej, zlecaj�ca budow� osobnej instancji budynku)
        - ulepszaj�ca odpowiedni rodzaj budynk�w (a p�niej, odpowiednie instancje budynk�w)
        - licz�ca zu�ycie (przychody i koszty) zasob�w w rundzie
    b) pola:
        - klasy grupy, cz�owieka
        - przyjaciele, wrogowie
        - posiadane ziemie, miasta
Docelowa hierarchia:
    Nation <- Group <- Human
Czy nawet lepiej: zawieraj�ce si� i przenikaj�ce grupy do kt�rych nale�y ka�dy cz�owiek, np. ze wzgl�du na narodowo��,
miejsce zamieszkania, zainteresowania itp.
*/
class Nation
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------ENUMS----------------------------------------------------------------------------------------------------------

//=====================================================================================================================
    public:
        Nation();
        Nation(int owner, const char * name, int color=0);
        Nation(int owner, string name, int color=0);

        virtual ~Nation();

        void splitGroup(unsigned  n,int popul);
   //     void setStartingGrid(Grid * grid);

        Group * getMainGroup(){return group_[0];}
        void addGroup(Group * group){group_.push_back(group);}

        unsigned groupCount(){return group_.size();}
        Group * getGroup(unsigned i){return group_[i];}

        string info();

        int getColor(){return color_;}
        string getName(){return name_;}

    protected:
    private:
//        friend GameInstance;
        string name_;
        int owner_;
        vector<Group*> group_;
        int color_;
};

#endif // NATION_H
