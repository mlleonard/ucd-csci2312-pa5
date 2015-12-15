//
// Created by Madeline Leonard on 12/14/15.
//

#include "Game.h"
#include "Strategic.h"
#include "Simple.h"
#include "Advantage.h"
#include "Food.h"
#include <iterator>

namespace Gaming{


    void Game::populate()
    {

        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;

        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);

        // populate Strategic agents
        while (numStrategic > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic --;
            }
        }

        // populate Simple agents
        while(numSimple > 0)
        {
            int i = d(gen); // random index in the grid vector
            if(__grid[i] == nullptr) //is position empty
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic --;
            }
        }

        //populate Advantages
        while(numAdvantages >0)
        {
            int i = d(gen); // random index in the grid vector
            if(__grid[i] == nullptr) //is position empty
            {
                Position pos(i/__width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_AGENT_ENERGY);
                numAdvantages--;
            }
        }

        //populate Foods
        while(numFoods > 0)
        {
            int i = d(gen); //random index in the frid vector
            if(__grid[i] == nullptr) //is position empty
            {
                Position pos(i / __width, i% __width);
                __grid[i] = new Food(*this, pos, Game::STARTING_AGENT_ENERGY);
                numFoods--;
            }
        }
    }

    Game::Game()
    {
        __width = MIN_WIDTH;
        __height = MIN_HEIGHT;
        int size = (__width*__height);

        __grid.assign(size, nullptr);
        populate();

    }

    Game::Game(unsigned width, unsigned height, bool manual)
    {
        __width = width;
        __height = height;
        int size = (__width*__height);

        __grid.assign(size, nullptr);
    }

    Game::Game(const Game &another)
    {

    }


//    Game::~Game()
//    {
//        delete Game;
//    }
    unsigned int Game::getNumPieces() const
    {
        unsigned int numPieces = 0;

        //std::vector<Piece *>::iterator it;
        //it = __grid.begin();

        auto it = __grid.begin();

        for(; it!=__grid.end(); it++)
        {
            if(*it != nullptr)
            {
                numPieces++;
            }
        }

        return 0;
    }

    Game::~Game()
    {
        auto it = __grid.begin();

        for(; it!=__grid.end(); it++)
        {
            if(*it != nullptr)
            {
                delete *it;
            }
        }

    }

    unsigned int Game::getNumAgents() const
    {
        unsigned int count = 0;
        auto it = __grid.begin();

        for(; it!=__grid.end(); it++)
        {
            if((*it)->getType() == SIMPLE || (*it)->getType() == STRATEGIC)
            {
                count ++;
            }

        }
        return count;
    }

    unsigned int Game::getNumSimple() const
    {
        unsigned int count = 0;
        auto it = __grid.begin();

        for(; it!=__grid.end(); it++)
        {
            if((*it)->getType() == SIMPLE)
            {
                count ++;
            }

        }
        return count;
    }


    unsigned int Game::getNumStrategic() const
    {
        unsigned int count = 0;
        auto it = __grid.begin();

        for(; it!=__grid.end(); it++)
        {
            if((*it)->getType() == STRATEGIC)
            {
                count ++;
            }

        }
        return count;
    }


    unsigned int Game::getNumResources()
    {
        unsigned int count = 0;
        auto it = __grid.begin();

        for(; it!=__grid.end(); it++)
        {
            if((*it)->getType() == FOOD || (*it)->getType() == ADVANTAGE)
            {
                count ++;
            }

        }
        return count;
    }

    bool Game::addSimple(const Position &position)
    {
        unsigned int vectorPos;
        vectorPos = (__width*((position.x)-1)+(position.y));
        if(__grid[vectorPos] != nullptr)
        {
            return false;
        }
        else
        {
            new Simple(*this, position, STARTING_AGENT_ENERGY);
        }
        return true;
    }
};