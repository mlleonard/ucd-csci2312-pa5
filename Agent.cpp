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

    Piece &Agent::operator*(Piece &other)
    {
//        if(other.getType() == FOOD || other.getType() == ADVANTAGE)
//        {
//            other.getType()
//
//            Resource * ptr;
//            ptr = new Resource(this->__game, this->getPosition(), other.); // todo this should call to other default constructor
//            interact(ptr);
//        }
//        else if(other.getType() == SIMPLE || other.getType() == STRATEGIC)
//        {
//            Agent * ptr;
//            ptr = new Agent(this->__game, this->getPosition(), __energy);
//            interact(other.);
//
//        }
        return <#initializer#>;
    }
};