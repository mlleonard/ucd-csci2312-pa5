//
// Created by Madeline Leonard on 12/14/15.
//

#include "DefaultAgentStrategy.h"

namespace Gaming{


    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const
    {
        int move;
        for(int i = 0; i < 9; i++)
        {
            if(s.array[i] == ADVANTAGE)
            {
                move = i;
            }
            else if(s.array[i] == FOOD)
            {
                move = i;
            }
            else if(s.array[i] == EMPTY)
            {
                move = i;
            }
            else if(s.array[i] == SIMPLE)
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
