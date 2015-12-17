//
// Created by Madeline Leonard on 12/14/15.
//

#include "Agent.h"

namespace Gaming{

    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g,p)
    {
        __energy = energy;
    }


    Agent::~Agent()
    {
//        std::cout << "Calling derived destructor" << std::endl;
    }

    void Agent::age()
    {
        __energy = (__energy - AGENT_FATIGUE_RATE);

        if (__energy == 0)
        {
            finish();
            delete this;
        }
    }

    Piece &Agent::operator*(Piece &other)
    {
        return other.interact(this);
    }

    Piece &Agent::interact(Agent *agent)
    {

        if(agent->__energy == this->__energy)
        {
            this->finish();
            agent->finish();
        }
        else if( agent->__energy < this->__energy)
        {
            this->addEnergy(agent->__energy);
            agent->finish();
        }
        else
        {
            agent->addEnergy(this->__energy);
            this->finish();
        }
        return *this;
    }

    Piece &Agent::interact(Resource *resource)
    {
        this->addEnergy(resource->consume());
        return *this;
    }
};