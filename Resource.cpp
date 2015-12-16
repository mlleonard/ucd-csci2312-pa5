//
// Created by Madeline Leonard on 12/14/15.
//

#include "Resource.h"

namespace Gaming{


    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g,p)
    {
        __capacity = capacity;
    }

    Resource::~Resource()
    {
        std::cout << "Destructing Derived Class Resource" << std::endl;
    }
};
