
#ifndef DEPTH_FIRST_GENERATOR_HPP
#define DEPTH_FIRST_GENERATOR_HPP
#include "Maze.hpp"
// may be better named RecursiveBacktracker...
struct DepthFirstGenerator
{
    Maze& mMaze; ///< reference to the maze being generated
public:
    DepthFirstGenerator(Maze& maze) : mMaze(maze) {}
    void Generate(Maze::Coordinate&& start_postion) {}
    void VisitBorders() {}
    const Maze::Coordinate& NextCell(const Maze::Coordinate& current) { return current; };
};

#endif // DEPTH_FIRST_GENERATOR_HPP
