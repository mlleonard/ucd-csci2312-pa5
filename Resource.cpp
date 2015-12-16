//
// Created by Madeline Leonard on 12/14/15.
//

#include "Resource.h"

namespace Gaming{

    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g,p)
    {
        __capacity = capacity;
    }

    Resource::~Resource()
    {
        std::cout << "Destructing Derived Class Resource" << std::endl;
    }
};
