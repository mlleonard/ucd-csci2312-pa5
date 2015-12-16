//
// Created by Madeline Leonard on 12/14/15.
//

#include "Simple.h"

namespace Gaming{

    const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g ,p ,energy)
    { }

    Simple::~Simple()
    {
        std::cout << "Calling destructor for derived class Simple" << std::endl;
    }
};