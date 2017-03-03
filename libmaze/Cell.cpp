#include <iostream>
#include "Cell.hpp"

/// \brief Constructor. Cell is initalized as un-visited and closed
Cell::Cell()
: mValue(0)
{
}

/// \brief Check if a cell has been visited during generation
/// \returns true if the cell has been visited (during maze generation, for example)
bool Cell::Visited() const
{
    return mValue & VISITED;
}

/// \brief Set a cell as visited, during generation
/// \returns a reference to the cell
Cell& Cell::Visit()
{
    mValue |= VISITED;
    return *this;
}

/// \brief Check to see is a cell is open, ie can be entered
/// \returns true if the cell is open (ie - doesn't contain a wall)
bool Cell::Opened() const
{
    return mValue & OPENED;
}

/// \brief Set the cell as open
/// \returns a reference to the cell
Cell& Cell::Open()
{
    mValue |= OPENED;
    return *this;
}
