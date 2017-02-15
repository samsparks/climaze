#include <iostream>
#include "Cell.hpp"

/// \brief Constructor
Cell::Cell()
: mValue(0)
{
}

/// \brief Check if a cell has been visited during generation
bool Cell::Visited() const
{
    return mValue & VISITED;
}

/// \brief Set a cell as visited, during generation
Cell& Cell::Visit()
{
    mValue |= VISITED;
    return *this;
}

/// \brief Check to see is a cell is open, ie can be entered
bool Cell::Opened() const
{
    return mValue & OPENED;
}

/// \brief Set the cell as open
Cell& Cell::Open()
{
    mValue |= OPENED;
    return *this;
}

/// \brief Set the cell as closed
Cell& Cell::Close()
{
    mValue ^= OPENED;
    return *this;
}
