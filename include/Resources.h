#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
using namespace std;

struct Resources
{
        Resources();
        Resources(unsigned water,unsigned food,unsigned wood,unsigned stone,unsigned iron);
        virtual ~Resources();
        void set(unsigned water,unsigned food,unsigned wood,unsigned stone,unsigned iron);

        bool operator <= (const Resources & resources)
        {
            return (water_<=resources.water_ && food_<=resources.food_ &&
                    wood_<=resources.wood_ && stone_<=resources.stone_ &&
                    iron_<=resources.iron_);
        }

        Resources & operator += (const Resources res)
        {
            food_ += res.food_;
            water_ += res.water_;
            wood_ += res.wood_;
            stone_ += res.stone_;
            iron_ += res.iron_;
            return *this;
        }

        Resources & operator -= (const Resources res)
        {
            food_ -= res.food_;
            water_ -= res.water_;
            wood_ -= res.wood_;
            stone_ -= res.stone_;
            iron_ -= res.iron_;
            return *this;
        }

        unsigned water_,food_,wood_,stone_,iron_;

        string state();
};

#endif // RESOURCES_H
