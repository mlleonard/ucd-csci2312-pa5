//
// Created by Madeline Leonard on 12/14/15.
//

#include "Agent.h"

namespace Gaming{


    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g,p)
    {
        __energy = energy;
    }


    Agent::~Agent()
    {
        std::cout << "Calling derived destructor" << std::endl;
    }

    void Agent::age()
    {
        double age;

        age = (__energy - AGENT_FATIGUE_RATE);

        if (age == 0)
        {
            finish();
        }
    }
};