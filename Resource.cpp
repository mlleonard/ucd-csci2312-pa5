//
// Created by Madeline Leonard on 12/14/15.
//

#include "Resource.h"
#include "Advantage.h"

namespace Gaming{

    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g,p)
    {
        __capacity = capacity;
    }

    Resource::~Resource()
    {
//        std::cout << "Destructing Derived Class Resource" << std::endl;
    }

    double Resource::consume()
    {
        double consume = (__capacity*Advantage::ADVANTAGE_MULT_FACTOR);
        __capacity = 0;
        finish();

        return consume;
    }

    void Resource::age()
    {

        if(__capacity == 0)
        {
            finish();
            delete this;
        }

        else
        {
            __capacity = (__capacity/RESOURCE_SPOIL_FACTOR);
        }


    }

    ActionType Resource::takeTurn(const Surroundings &s) const
    {
        return STAY;
    }

    Piece &Resource::operator*(Piece &other)
    {
        return *this;
    }

    Piece &Resource::interact(Agent *agent)
    {
        this->finish();
        this->__capacity = 0;
        return *this;
    }

    Piece &Resource::interact(Resource *resource) {
        return *this;
    }
};
