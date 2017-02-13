
#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <utility>
#include "Cell.hpp"

class Maze
{
    std::vector< std::vector< Cell > > mContent; ///< internal representation of a maze

public:
    typedef std::pair< size_t, size_t > Coordinate; ///< the row and column coordinate of a cell in the maze

    Maze(size_t row_count, size_t col_count)
    : mContent( row_count, std::vector<Cell>(col_count) )
    {
        if( ! row_count )
            throw std::invalid_argument("Cannot construct maze with zero rows");
        if( ! col_count )
            throw std::invalid_argument("Cannot construct maze with zero columns");
    }
    
    Cell& at(size_t row, size_t col)
    {
        return mContent.at(row).at(col);
    }

    Cell& at(const Coordinate& coord)
    {
        return mContent.at(coord.first).at(coord.second);
    }

    size_t size() const
    {
        return mContent.size() * mContent.at(0).size();
    }
};

#endif // MAZE_HPP
