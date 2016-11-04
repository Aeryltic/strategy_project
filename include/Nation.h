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
        - buduj¹ca odpowiednie budynki (a póŸniej, zlecaj¹ca budowê osobnej instancji budynku)
        - ulepszaj¹ca odpowiedni rodzaj budynków (a póŸniej, odpowiednie instancje budynków)
        - licz¹ca zu¿ycie (przychody i koszty) zasobów w rundzie
    b) pola:
        - klasy grupy, cz³owieka
        - przyjaciele, wrogowie
        - posiadane ziemie, miasta
Docelowa hierarchia:
    Nation <- Group <- Human
Czy nawet lepiej: zawieraj¹ce siê i przenikaj¹ce grupy do których nale¿y ka¿dy cz³owiek, np. ze wzglêdu na narodowoœæ,
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
