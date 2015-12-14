//
// Created by Madeline Leonard on 12/14/15.
//

#include "Piece.h"


namespace Gaming{

    Piece::Piece(const Game &g, const Position &p) : __game(g)
    {
        __id = __idGen;
        __idGen++;
        __finished = false;
        __position = p;

    };
};