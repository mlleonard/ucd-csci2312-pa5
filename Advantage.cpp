//
// Created by Madeline Leonard on 12/14/15.
//
#include "Advantage.h"

namespace Gaming {

    const char Advantage::ADVANTAGE_ID = 'D';

    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g,p,capacity)
    { }

    Advantage::~Advantage()
    {
        std::cout << "Calling destructor for derived class Food" << std::endl;
    }

    void Advantage::print(std::ostream &os) const
    {
        os<<ADVANTAGE_ID<<this->__id;
    }
};