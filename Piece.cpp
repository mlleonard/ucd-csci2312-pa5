//
// Created by Madeline Leonard on 12/14/15.
//

#include "Piece.h"


namespace Gaming{

    unsigned int Piece::__idGen = 0;

    Piece::Piece(const Game &g, const Position &p) : __game(g)
    {
        __idGen++;
        __id = __idGen;
        __finished = false;
        __position = p;

    };

    Piece::~Piece()
    {
//        std::cout<< "Base destructor called" << std::endl;

    }

    std::ostream& operator<<(std::ostream &os, const Piece &piece)
    {
        piece.print(os);
        //os << piece.__id ;
        return os;
    }
};