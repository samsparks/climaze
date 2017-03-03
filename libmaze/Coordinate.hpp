#ifndef COORDINATE_HPP
#define COORDINATE_HPP

/// \brief class used to capture the row and column of a cell in the Maze
class Coordinate
{
    const size_t mRow; ///< the row 
    const size_t mColumn; ///< the column

public:
    /// \brief Constructs a coordinate
    /// \param row the row of the coordinate
    /// \param col the column of the coordinate
    explicit Coordinate(size_t row, size_t col)
    : mRow(row), mColumn(col)
    {
    }

    /// \brief Accessor for the coordinate's row
    /// \returns the row
    inline size_t Row() const
    {
        return mRow;
    }

    /// \brief Accessor for the coordinate's column
    /// \returns the row
    inline size_t Column() const
    {
        return mColumn;
    }
};

#endif // COORDINATE_HPP
