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
//        std::cout << "Calling destructor for derived class Simple" << std::endl;
    }

    void Simple::print(std::ostream &os) const
    {
        os<<SIMPLE_ID<<this->__id;
    }


    ActionType Simple::takeTurn(const Surroundings &s) const
    {
        int move;
        for( int i = 0; i< 9; i++)
        {
            if(s.array[i] == FOOD || s.array[i] == ADVANTAGE)
            {
                move = i;
            }
            else if(s.array[i] == EMPTY)
            {
                move = i;
            }

        }

        switch(move)
        {
            case 0:
                return NW;

            case 1:
                return N;

            case 2:
                return NE;

            case 3:
                return W;

            case 4:
                return STAY;

            case 5:
                return E;

            case 6:
                return SW;

            case 7:
                return S;

            case 8:
                return SE;
        }

        return STAY;
    }
};