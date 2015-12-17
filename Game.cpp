//
// Created by Madeline Leonard on 12/14/15.
//

#include "Game.h"
#include "Strategic.h"
#include "Simple.h"
#include "Advantage.h"
#include "Food.h"
#include <iterator>
#include <sstream>

namespace Gaming{

    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

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
                numSimple --;
            }
        }

        //populate Advantages
        while(numAdvantages >0)
        {
            int i = d(gen); // random index in the grid vector
            if(__grid[i] == nullptr) //is position empty
            {
                Position pos(i/__width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
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
                __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }
    }

    Game::Game(): __width(MIN_WIDTH), __height(MIN_HEIGHT) ,__grid(__width*__height, nullptr)
    {
//        __width = MIN_WIDTH;
//        __height = MIN_HEIGHT;
        __round = 0;
        //int size = (__width*__height);


       // __grid.assign(size, nullptr);


    }

    Game::Game(unsigned width, unsigned height, bool manual): __width(width), __height(height),__grid(__width*__height, nullptr)
    {
//        __width = width;
//        __height = height;
//        int size = (__width*__height);

        //__grid.assign(size, nullptr);
        populate();
    }

    Game::Game(const Game &another)
    {
        __verbose = another.__verbose;
    }


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
        vectorPos = (__width*((position.x))+(position.y+1));
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

    bool Game::addSimple(unsigned x, unsigned y)
    {
        unsigned int vectorPos;
        vectorPos = (__width*x+(y+1));
        if(__grid[vectorPos] != nullptr)
        {
            return false;
        }
        else
        {
            Position p(x,y);
            new Simple(*this, p, STARTING_AGENT_ENERGY);
        }
        return true;
    }


    bool Game::addStrategic(const Position &position, Strategy *s)
    {
        unsigned int vectorPos;
        vectorPos = (__width*((position.x))+(position.y+1));
        if(__grid[vectorPos] != nullptr)
        {
            return false;
        }
        else
        {
            new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
        }
        return true;
    }


    bool Game::addStrategic(unsigned x, unsigned y, Strategy *s)
    {
        unsigned int vectorPos;
        vectorPos = (__width*x+(y+1));
        if(__grid[vectorPos] != nullptr)
        {
            return false;
        }
        else
        {
            Position p(x,y);
            new Strategic(*this, p, STARTING_AGENT_ENERGY, s);
        }
        return true;
    }

    bool Game::addFood(const Position &position)
    {
        unsigned int vectorPos;
        vectorPos = (__width*((position.x))+(position.y+1));
        if(__grid[vectorPos] != nullptr)
        {
            return false;
        }
        else
        {
            new Food(*this, position, STARTING_RESOURCE_CAPACITY);
        }
        return true;
    }

    bool Game::addFood(unsigned x, unsigned y)
    {
        unsigned int vectorPos = 0;
        vectorPos = ((__width * x)+(y+1));
        if(__grid[vectorPos] != nullptr)
        {
            return false;
        }
        else
        {
            Position p(x,y);
            new Food(*this, p, STARTING_RESOURCE_CAPACITY);
        }
        return true;
    }

    bool Game::addAdvantage(const Position &position)
    {
        unsigned int vectorPos;
        vectorPos = (__width*((position.x))+(position.y+1));
        if(__grid[vectorPos] != nullptr)
        {
            return false;
        }
        else
        {
            new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
        }
        return true;
    }

    bool Game::addAdvantage(unsigned x, unsigned y)
    {
        unsigned int vectorPos;
        vectorPos = (__width*(x)+(y+1));
        if(__grid[vectorPos] != nullptr)
        {
            return false;
        }
        else
        {
            Position p(x,y);
            new Food(*this, p, STARTING_RESOURCE_CAPACITY);
        }
        return true;
    }

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings s;
        int count = 0;
        unsigned int vectorPos;
        unsigned int newPos;
        int x = pos.x;
        int y = pos.y;
        int w = __width;
        int h = __height;


        Position p(pos.x-1, pos.y);
        vectorPos = (this->__width*pos.x+(pos.y+1));
        newPos = ((vectorPos)-(__width+1));

        //auto it = __grid[(vectorPos-(__width+1))];

//        if( vectorPos < ((x+1)*(y+1)))
//        {
//            for( int i = 0; i < (__width*__height); i++ )
//            {
//                s.array[i] = PieceType::INACCESSIBLE;
//            }
//            return s;
//        }


//        if(pos.x == 0)
//        {
//            if(pos.y == 0 )
//            {
//                s.array[0] = PieceType::INACCESSIBLE;
//                s.array[1] = PieceType::INACCESSIBLE;
//                s.array[2] = PieceType::INACCESSIBLE;
//
//                newPos = (vectorPos-1);
//                if(__grid[newPos] != nullptr)
//                {
//                    s.array[3] = PieceType::INACCESSIBLE;
//                }
//                else{ s.array[3] == PieceType::EMPTY; }
//                newPos++;
//                s.array[4] = PieceType::SELF;
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[5] = __grid[newPos]->getType();}
//                else{ s.array[5] == PieceType::EMPTY; }
//
//                newPos = (vectorPos+(__width-1));
//                s.array[6] = PieceType::INACCESSIBLE;
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[7] = __grid[newPos]->getType();}
//                else{ s.array[7] == PieceType::EMPTY; }
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[8] = __grid[newPos]->getType();}
//                else{ s.array[8] == PieceType::EMPTY; }
//
//            }
//            else if( ((pos.y)+1) == __width)
//            {
//                s.array[0] = PieceType::INACCESSIBLE;
//                s.array[1] = PieceType::INACCESSIBLE;
//                s.array[2] = PieceType::INACCESSIBLE;
//
//                newPos = (vectorPos-1);
//                if(__grid[newPos] != nullptr)
//                {s.array[3] = __grid[newPos]->getType();}
//                else{ s.array[3] == PieceType::EMPTY; }
//                newPos++;
//                s.array[4] = PieceType::SELF;
//                newPos++;
//                s.array[5] = PieceType::INACCESSIBLE;
//
//                newPos = (vectorPos+(__width-1));
//                if(__grid[newPos] != nullptr)
//                {s.array[6] = __grid[newPos]->getType();}
//                else{ s.array[3] == PieceType::EMPTY; }
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[7] = __grid[newPos]->getType();}
//                else{ s.array[3] == PieceType::EMPTY; }
//                newPos++;
//                s.array[8] = PieceType::INACCESSIBLE ;
//            }
//            else
//            {
//                s.array[0] = PieceType::INACCESSIBLE;
//                s.array[1] = PieceType::INACCESSIBLE;
//                s.array[2] = PieceType::INACCESSIBLE;
//
//                newPos = (vectorPos-1);
//                if(__grid[newPos] != nullptr)
//                {s.array[3] = __grid[newPos]->getType();}
//                else{ s.array[3] == PieceType::EMPTY; }
//                newPos++;
//                s.array[4] = PieceType::SELF;
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[5] = __grid[newPos]->getType();}
//                else{ s.array[5] == PieceType::EMPTY; }
//
//                newPos = (vectorPos+(__width-1));
//                if(__grid[newPos] != nullptr)
//                {s.array[6] = __grid[newPos]->getType();}
//                else{ s.array[6] == PieceType::EMPTY; }
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[7] = __grid[newPos]->getType();}
//                else{ s.array[7] == PieceType::EMPTY; }
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[8] = __grid[newPos]->getType();}
//                else{ s.array[8] == PieceType::EMPTY; }
//
//            }
//        }
//        else if(pos.y == 0)
//        {
//            if(pos.x == 0)
//            {
//                s.array[0] = PieceType::INACCESSIBLE;
//                s.array[1] = PieceType::INACCESSIBLE;
//                s.array[2] = PieceType::INACCESSIBLE;
//
//                newPos = (vectorPos-1);
//                s.array[3] = PieceType::INACCESSIBLE;
//                newPos++;
//                s.array[4] = PieceType::SELF;
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[5] = __grid[newPos]->getType();}
//                else{ s.array[5] == PieceType::EMPTY; }
//
//                newPos = (vectorPos+(__width-1));
//                s.array[6] = PieceType::INACCESSIBLE;
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[7] = __grid[newPos]->getType();}
//                else{ s.array[7] == PieceType::EMPTY; }
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[8] = __grid[newPos]->getType();}
//                else{ s.array[8] == PieceType::EMPTY; }
//
//            }
//            else if(((pos.x)+1) == __height)
//            {
//                s.array[0] = PieceType::INACCESSIBLE;
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[1] = __grid[newPos]->getType();}
//                else{ s.array[1] == PieceType::EMPTY; }
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[2] = __grid[newPos]->getType();}
//                else{ s.array[2] == PieceType::EMPTY; }
//
//                newPos = (vectorPos-1);
//                s.array[3] = PieceType::INACCESSIBLE;
//                newPos++;
//                s.array[4] = PieceType::SELF;
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[5] = __grid[newPos]->getType();}
//                else{ s.array[5] == PieceType::EMPTY; }
//
//                newPos = (vectorPos+(__width-1));
//                s.array[6] = PieceType::INACCESSIBLE;
//                s.array[7] = PieceType::INACCESSIBLE;
//                s.array[8] = PieceType::INACCESSIBLE;
//            }
//            else
//            {
//                s.array[0] = PieceType::INACCESSIBLE;
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[1] = __grid[newPos]->getType();}
//                else{ s.array[1] == PieceType::EMPTY; }
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[2] = __grid[newPos]->getType();}
//                else{ s.array[2] == PieceType::EMPTY; }
//
//                newPos = (vectorPos-1);
//                s.array[3] = PieceType::INACCESSIBLE;
//                newPos++;
//                s.array[4] = PieceType::SELF;
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[5] = __grid[newPos]->getType();}
//                else{ s.array[5] == PieceType::EMPTY; }
//
//                newPos = (vectorPos+(__width-1));
//                s.array[6] = PieceType::INACCESSIBLE;
//                newPos++;
//                {s.array[7] = __grid[newPos]->getType();}
//                newPos++;
//                if(__grid[newPos] != nullptr)
//                {s.array[8] = __grid[newPos]->getType();}
//                else{ s.array[8] == PieceType::EMPTY; }
//
//
//            }
//
//        }
//
//        else
//        {
//            if(__grid[newPos] != nullptr)
//            {s.array[0] = __grid[newPos]->getType();}
//            else{ s.array[0] == PieceType::EMPTY; }
//            newPos++;
//            if(__grid[newPos] != nullptr)
//            {s.array[1] = __grid[newPos]->getType();}
//            else{ s.array[1] == PieceType::EMPTY; }
//            newPos++;
//            if(__grid[newPos] != nullptr)
//            {s.array[2] = __grid[newPos]->getType() ;}
//            else{ s.array[2] == PieceType::EMPTY; }
//
//            newPos = (vectorPos-1);
//            if(__grid[newPos] != nullptr)
//            {s.array[3] = __grid[newPos]->getType();}
//            else{ s.array[3] == PieceType::EMPTY; }
//            newPos++;
//            s.array[4] = PieceType::SELF ;
//            newPos++;
//            if(__grid[newPos] != nullptr)
//            {s.array[5] = __grid[newPos]->getType() ;}
//            else{ s.array[5] == PieceType::EMPTY; }
//
//            newPos = (vectorPos+(__width-1));
//            if(__grid[newPos] != nullptr)
//            {s.array[6] = __grid[newPos]->getType();}
//            else{ s.array[6] == PieceType::EMPTY; }
//            newPos++;
//            if(__grid[newPos] != nullptr)
//            {s.array[7] = __grid[newPos]->getType();}
//            else{ s.array[7] == PieceType::EMPTY; }
//            newPos++;
//            if(__grid[newPos] != nullptr)
//            {s.array[8] = __grid[newPos]->getType() ;}
//            else{ s.array[8] == PieceType::EMPTY; }
//        }
//





        for(count; count < 3; count++)
        {
            if( vectorPos <= __width  )
            {
                s.array[count] = PieceType::INACCESSIBLE ;
            }

            else if(__grid[newPos] != nullptr)
            {
               // s.array[count] = it->getType();
                s.array[count] = __grid[newPos]->getType();
            }
            else
            {
                s.array[count] = PieceType::EMPTY ;
            }

            ++newPos;
        }

        newPos = (vectorPos-1);

        for(count; count < 6; count++)
        {
            if( count == 4 )
            {
                s.array[count] = PieceType::SELF;
            }

            else if(((vectorPos)-1)%(__width) == 0 && count == 3)
            {
                s.array[count] = PieceType::INACCESSIBLE ;
            }
            else if( newPos%__width == 0 && count == 5)
            {
                s.array[count] = PieceType::INACCESSIBLE;
            }

            else if(__grid[newPos] != nullptr)
            {
                s.array[count] = __grid[newPos]->getType();
            }
            else
            {
                s.array[count] = PieceType::EMPTY ;
            }
            newPos++;
        }

       newPos = (vectorPos+(__width-1));

        for(count; count < 9; count++)
        {
            if(newPos > ((__height*__width)-__width))
            {
                s.array[count] = PieceType::INACCESSIBLE ;
            }
            else if(__grid[newPos] != nullptr)
            {
                s.array[count] = __grid[newPos]->getType();

            }
            else
            {
                s.array[count] = PieceType::EMPTY;
            }
            newPos++;
        }


        return s;
    }

    const ActionType Game::reachSurroundings(const Position &from, const Position &to)
    {
        if(to.x == ((from.x)-1))
        {
            if(to.y == ((from.y)-1))
            {
                return NW;
            }
            else if( to.y == from.y)
            {
                return N;
            }
            else
            {
                return NE;
            }
        }

        if(to.x == ((from.x)+1))
        {
            if(to.y == ((from.y)-1))
            {
                return SW;
            }
            else if( to.y == from.y)
            {
                return S;
            }
            else
            {
                return SE;
            }
        }

        else if(to.x == from.x)
        {
            if(to.y == ((from.y)-1))
            {
                return W;
            }
            else if(to.y == from.y)
            {
                return STAY;
            }
            else
            {
                return E;
            }
        }

        return STAY;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const
    {
        if (pos.x == 1 )
        {
            if( ac == NW || ac == N || ac == NE)
            {
                return false;
            }
        }

        if (pos.x == __width)
        {
            if( ac == SW || ac == S || ac == SE)
            {
                return false;
            }
        }

        if (pos.y == 1)
        {
            if( ac == NW || ac == W || ac == SW)
            {
                return false;
            }
        }

        if (pos.y == __height)
        {
            if( ac == NE || ac == E || ac == SE)
            {
                return false;
            }
        }

        return true;
    }

    const Position Game::move(const Position &pos, const ActionType &ac) const
    {
        Position *ptr;

        if( isLegal(ac, pos) )
        {
            unsigned int vecPos = (__width*(pos.x-1)+pos.y);
            //auto it = __grid[vecPos];
            if( ac == NW )
            {
                ptr = new Position(((pos.x)-1), ((pos.y) - 1));
            }
            else if( ac == N )
            {
                ptr = new Position(((pos.x)-1), pos.y);
            }
            else if( ac == NE)
            {
                ptr = new Position(((pos.x)-1), ((pos.y)+1));
            }
            else if( ac == W )
            {
                ptr = new Position((pos.x), ((pos.y)-1));
            }
            else if( ac == STAY )
            {
                ptr = new Position(pos.x, pos.y);
            }
            else if( ac == E )
            {
                ptr = new Position(pos.x, ((pos.y)+1));
            }
            else if( ac == SW )
            {
                ptr = new Position(((pos.x)+1), ((pos.y)-1));
            }
            else if( ac == S )
            {
                ptr = new Position(((pos.x)+1), pos.y);
            }
            else if( ac == SE )
            {
                ptr = new Position(((pos.x)+1), ((pos.y)+1));
            }

        }
        return *ptr;
    }

    void Game::round()
    {
        Surroundings s;
        auto it = __grid.begin();


        for(; it != __grid.end(); it++)
        {
            s = (getSurroundings((*it)->getPosition()));
            ActionType ac;
            if( *it != nullptr || (*it)->isViable())
            {
                if((*it)->getTurned() == false)
                {
                    (*it)->setTurned(true);
                    ac = (*it)->takeTurn(s);
                }

                if ((*it)->isViable() == false) {
                    delete (*it);
                }
            }

        }
        for(; it != __grid.end(); it++)
        {
            if(*it != nullptr)
            {
                (*it)->age();
                (*it)->setTurned(true);

            }
        }


    }

    void Game::play(bool verbose)
    {
        __status = Status::PLAYING;

        while(getNumAgents()!= 0)
        {
            round();
        }
        __round++;

        __status = Status::OVER;

    }

    std::ostream& operator<<(std::ostream &os, const Game &game)
    {
        int count = 0;
        os<<"Round " << game.__round << std::endl;
        for( int i = 0; i < (game.__height*game.__width); i++)
        {
            os << "[";
            if(game.__grid[i] == nullptr)
            {
                os << "       ";
                count ++;
            }
            else
            {

                std::cout << *game.__grid[i] << "   ";
                count++;
            }
            os << "]";

            if(count == game.__width)
            {
                std::cout << std::endl;
                count = 0;
            }

        }
        return os;
    }
};