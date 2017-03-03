
#ifndef CELL_HPP
#define CELL_HPP

/// \brief Minimal Cell class. Base class for any cell type in a maze
class Cell
{
    static const unsigned VISITED = 0x00000001;
    static const unsigned OPENED  = 0x00000002;

    unsigned mValue; ///< value of the cell
public:
    explicit Cell();

    bool Visited() const;
    Cell& Visit();

    bool Opened() const;
    Cell& Open();
};

#endif // CELL_HPP
