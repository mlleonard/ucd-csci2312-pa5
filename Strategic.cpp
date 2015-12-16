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
//        std::cout << "Calling destructor for derived class Strategic" << std::endl;
    }

    void Strategic::print(std::ostream &os) const
    {
        os<<STRATEGIC_ID<<this->__id;
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const
    {
        return (*__strategy)(s);
    }
};