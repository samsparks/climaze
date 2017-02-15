#ifndef DEPTH_FIRST_GENERATOR_HPP
#define DEPTH_FIRST_GENERATOR_HPP
#include "Maze.hpp"

/// \brief Builds the given maze using a recursive backtracker algorithm.
/// \see https://en.wikipedia.org/wiki/Maze_generation_algorithm
struct DepthFirstGenerator
{
    Maze& mMaze; ///< reference to the maze being generated
public:
    DepthFirstGenerator(Maze& maze);
    void Generate(Maze::Coordinate& start_postion);
    void VisitBorders();
    const Maze::Coordinate& NextCell(const Maze::Coordinate& current);
};

#endif // DEPTH_FIRST_GENERATOR_HPP
