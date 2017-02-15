
#ifndef MAZE_HPP
#define MAZE_HPP

#include <cstddef>
#include <vector>
#include <utility>
#include "Cell.hpp"

class Maze
{
    const size_t mRows;
    const size_t mColumns;
    std::vector< std::vector< Cell > > mContent; ///< internal representation of a maze

public:
    typedef std::pair< size_t, size_t > Coordinate; ///< the row and column coordinate of a cell in the maze

    Maze(size_t row_count, size_t col_count);
    size_t Rows() const;
    size_t Columns() const;

    Cell& At(size_t row, size_t col);
    Cell& At(const Coordinate& coord);
    bool Contains(size_t row, size_t col) const;
    bool Contains(const Coordinate& coord) const;
};

#endif // MAZE_HPP
