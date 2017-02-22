#ifndef GENERATOR_HPP
#define GENERATOR_HPP
#include <stdexcept>

#include "Maze.hpp"

struct NoDisplayPolicy
{
    void Update(const Maze& maze) { }
    void GetUserInput() {}
};

///< template for policy-based design, so different output formats can be used
template <typename GenerationPolicy, typename DisplayPolicy = NoDisplayPolicy> 
class Display : private GenerationPolicy, DisplayPolicy
{
    Maze& mMaze; ///< reference to the maze being generated

    using GenerationPolicy::Initialize;
    using GenerationPolicy::NextStep;

    using DisplayPolicy::Update;
    using DisplayPolicy::GetUserInput;

public:
    void Build(const Maze& maze)
    {
        Initialize();
        while( NextStep(maze) )
        {
            Update();
            GetUserInput("");
        }
    }

};

#endif // GENERATOR_HPP
