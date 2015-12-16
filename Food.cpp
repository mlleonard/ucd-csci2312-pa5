//
// Created by Madeline Leonard on 12/14/15.
//

#include "Food.h"

namespace Gaming
{

    const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g,p,capacity)
    { }

    Food::~Food()
    {
//        std::cout<< "Calling destructor for derived class Food" << std::endl;
    }

    void Food::print(std::ostream &os) const
    {
        os<<FOOD_ID<<this->__id;
    }
};