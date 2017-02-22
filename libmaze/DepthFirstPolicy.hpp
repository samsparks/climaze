#ifndef DEPTH_FIRST_POLICY
#define DEPTH_FIRST_POLICY
#include "Maze.hpp"

class DepthFirstPolicy
{
    std::vector<Maze::Coordinate> mVisitStack;
private:

    void Initialize(Maze::Coordinate& coord)
    {
        mMaze.At(coord).Visit().Open();
        mVisitStack.push_back(coord);
    }

    bool NextStep(Maze& maze)
    {
    }
};

#endif // DEPTH_FIRST_POLICY
