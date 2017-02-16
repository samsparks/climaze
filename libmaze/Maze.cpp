#include "Maze.hpp"
#include <stdexcept>

Maze::Maze(size_t row_count, size_t col_count)
: mRows(row_count),
  mColumns(col_count),
  mContent( mRows, std::vector<Cell>(mColumns) )
{
    if( ! row_count )
        throw std::invalid_argument("Cannot construct maze with zero rows");
    if( ! col_count )
        throw std::invalid_argument("Cannot construct maze with zero columns");
}

size_t Maze::Rows() const
{
    return mRows;
}

size_t Maze::Columns() const
{
    return mColumns;
}

Cell& Maze::At(size_t row, size_t col)
{
    return mContent.at(row).at(col);
}

const Cell& Maze::At(size_t row, size_t col) const
{
    return mContent.at(row).at(col);
}

Cell& Maze::At(const Coordinate& coord)
{
    return At(coord.first, coord.second);
}

const Cell& Maze::At(const Coordinate& coord) const
{
    return At(coord.first, coord.second);
}

bool Maze::Contains(size_t row, size_t col) const
{
    return (row < mRows ) && (col < mColumns);
}

bool Maze::Contains(const Coordinate& coord) const
{
    return Contains(coord.first,coord.second);
}
