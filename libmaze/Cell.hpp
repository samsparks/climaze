
#ifndef MAZE_HPP
#define MAZE_HPP
#include <iosfwd>

class Cell
{
    int mValue; ///< value of the cell
public:
    /// \brief Constructor
    explicit Cell();

    /// \brief Check if a cell has been visited during generation
    bool Visited() const;
    /// \brief Set a cell as visited, during generation
    Cell& Visit();

    /// \brief Check to see is a cell is open, ie can be entered
    bool Opened() const;
    /// \brief Set the cell as open
    Cell& Open();

    /// \brief Check to see is a cell is open, ie can be entered
    bool Closed() const;
    /// \brief Set the cell as open
    Cell& Close();
};

std::ostream& operator<<(std::ostream& out, const Cell& cell);
#endif // MAZE_HPP
