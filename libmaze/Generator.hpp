#ifndef GENERATOR_HPP
#define GENERATOR_HPP
#include <stdexcept>
#include <algorithm>

#include "Maze.hpp"
#include "Display.hpp"

struct NullOutputPolicy
{
    void Initialize() {};
    void PrintOpen() {};
    void PrintPlus() {};
    void PrintTopTee() {};
    void PrintBottomTee() {};
    void PrintLeftTee() {};
    void PrintRightTee() {};
    void PrintUpperLeftCorner() {};
    void PrintUpperRightCorner() {};
    void PrintLowerLeftCorner() {};
    void PrintLowerRightCorner() {};
    void PrintHorizontalLine() {};
    void PrintVerticalLine() {};
    void EndRow() {};
    void DisplayMessage() {};
    void Flush() {};
    void BlockingRead() {};
};

///< template for policy-based design, so different output formats can be used
template <typename GenerationPolicy, typename OutputPolicy = NullOutputPolicy> 
class Generator : private GenerationPolicy
{
    using GenerationPolicy::Initialize;
    using GenerationPolicy::NextStep;

    Display<OutputPolicy> mDisplay;
public:
    Maze Build(size_t rows, size_t columns, size_t start_row, size_t start_column)
    {
        Maze maze(rows, columns);

        auto start = std::make_pair<size_t,size_t>(1, 1);
        Initialize(maze, start);
        while( NextStep(maze) )
        {
            mDisplay.Update(maze);
            mDisplay.GetUserInput();
        }

        return maze;
    }

};

#endif // GENERATOR_HPP
