//
// Created by Madeline Leonard on 12/14/15.
//

#include "Strategic.h"

namespace Gaming{

    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) : Agent(g,p,energy)
    {
        __strategy = s;
    }

    Strategic::~Strategic()
    {
        std::cout << "Calling destructor for derived class Strategic" << std::endl;
    }
};