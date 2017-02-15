#include <cstdlib>
#include <ctime>
#include "DepthFirstGenerator.hpp"

/// \brief Constructs the Generator for the given maze
DepthFirstGenerator::DepthFirstGenerator(Maze& maze)
: mMaze(maze)
{
    std::srand(std::time(0));
}

void DepthFirstGenerator::Generate(Maze::Coordinate& start_postion) {}

void DepthFirstGenerator::VisitBorders()
{
    for(size_t r = 0; r < mMaze.Rows(); ++r)
    {
        mMaze.At(r, 0).Visit();
        mMaze.At(r, mMaze.Columns()-1).Visit();
    }

    for(size_t c = 0; c < mMaze.Columns(); ++c)
    {
        mMaze.At(0, c).Visit();
        mMaze.At(mMaze.Rows()-1, c).Visit();
    }

}

const Maze::Coordinate& DepthFirstGenerator::NextCell(const Maze::Coordinate& current)
{
    // the next cell can be up, down, left, or right. Randomly pick one that hasn't been visited.
    std::vector<Maze::Coordinate> neighbors;

    auto next = current;
    --next.first;
    if( mMaze.Contains(next) && !mMaze.At(next).Visited() )
        neighbors.push_back(next);


    next = current;
    ++next.first;
    if( mMaze.Contains(next) && !mMaze.At(next).Visited() )
        neighbors.push_back(next);

    next = current;
    --next.second;
    if( mMaze.Contains(next) && !mMaze.At(next).Visited() )
        neighbors.push_back(next);

    next = current;
    ++next.second;
    if( mMaze.Contains(next) && !mMaze.At(next).Visited() )
        neighbors.push_back(next);

    if( neighbors.empty() )
        return current;
        
    auto itr = std::begin(neighbors);
    std::advance(itr, std::rand() % neighbors.size());
 
    return *itr;
}
