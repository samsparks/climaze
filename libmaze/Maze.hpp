
#ifndef MAZE_HPP
#define MAZE_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

#include "Coordinate.hpp"

template< typename Cell >
class Maze
{
    const size_t mRows;
    const size_t mColumns;
    std::vector< std::vector< Cell > > mContent; ///< internal representation of a maze

public:
    typedef Cell value_type;

    Maze(size_t row_count, size_t col_count)
    : mRows(row_count),
      mColumns(col_count),
      mContent( mRows, std::vector<Cell>(mColumns) )
    {
        if( ! row_count )
            throw std::invalid_argument("Cannot construct maze with zero rows");
        if( ! col_count )
            throw std::invalid_argument("Cannot construct maze with zero columns");
    }

    size_t Rows() const { return mRows; }
    size_t Columns() const { return mColumns; }

    Cell& At(size_t row, size_t col) { return mContent.at(row).at(col); }
    const Cell& At(size_t row, size_t col) const { return mContent.at(row).at(col); }
    Cell& At(const Coordinate& coord) { return At(coord.Row(), coord.Column()); }
    const Cell& At(const Coordinate& coord) const { return At(coord.Row(), coord.Column()); }
    bool Contains(size_t row, size_t col) const { return (row < mRows ) && (col < mColumns); }
    bool Contains(const Coordinate& coord) const { return Contains(coord.Row(),coord.Column()); }
};

#endif // MAZE_HPP
