//
// Created by Madeline Leonard on 12/14/15.
//

#include <iosfwd>
#include "Exceptions.h"

namespace Gaming{


    void GamingException::setName(std::string name) {

    }

    std::ostream& operator<<(std::ostream &os, const GamingException &ex)
    {
        os<<ex.__name;
        return os;
    }

    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height)
    {

    }

    unsigned DimensionEx::getExpWidth() const
    {
        return 0;
    }

    unsigned DimensionEx::getExpHeight() const
    {
        return 0;
    }

    unsigned DimensionEx::getWidth() const
    {
        return 0;
    }

    unsigned DimensionEx::getHeight() const
    {
        return 0;
    }

    void InsufficientDimensionsEx::__print_args(std::ostream &os) const
    {

    }

    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width,
                                                       unsigned height) : DimensionEx(minWidth, minHeight, width, height)
    {

    }

    void OutOfBoundsEx::__print_args(std::ostream &os) const
    {

    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height): DimensionEx(maxWidth ,maxHeight, width, height)
    {

    }
};
