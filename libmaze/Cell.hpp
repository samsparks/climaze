
#ifndef CELL_HPP
#define CELL_HPP

class Cell
{
    static const unsigned VISITED = 0x00000001;
    static const unsigned OPENED  = 0x00000002;

    unsigned mValue; ///< value of the cell
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
    /// \brief Set the cell as open
    Cell& Close();
};

#endif // CELL_HPP
