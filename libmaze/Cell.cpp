#include <iostream>
#include "Cell.hpp"

/// \brief Constructor
Cell::Cell()
{
}

/// \brief Check if a cell has been visited during generation
bool Cell::Visited() const
{
    return false;
}

/// \brief Set a cell as visited, during generation
Cell& Cell::Visit()
{
    return *this;
}

/// \brief Check to see is a cell is open, ie can be entered
bool Cell::Opened() const
{
    return false;
}

/// \brief Set the cell as open
Cell& Cell::Open()
{
    return *this;
}

/// \brief Check to see is a cell is closed, ie cannot be entered
bool Cell::Closed() const
{
    return false;
}

/// \brief Set the cell as closed
Cell& Cell::Close()
{
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Cell& cell)
{
    return out << "[v=" << cell.Visited() << ",o=" << cell.Opened() << "]";
}
