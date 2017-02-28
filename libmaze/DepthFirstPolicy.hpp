#ifndef DEPTH_FIRST_POLICY
#define DEPTH_FIRST_POLICY
#include <stdexcept>
#include "Maze.hpp"

class DepthFirstPolicy
{
    std::vector<Maze::Coordinate> mVisitStack;
public:

    // marks all borders as visted, to prevent them being opened
    void VisitBorders(Maze& maze)
    {
        for(size_t r = 0; r < maze.Rows(); ++r)
        {
            maze.At(r, 0).Visit();
            maze.At(r, maze.Columns()-1).Visit();
        }
        
        for(size_t c = 0; c < maze.Columns(); ++c)
        {
            maze.At(0, c).Visit();
            maze.At(maze.Rows()-1, c).Visit();
        }
    }


    std::vector<Maze::Coordinate> UnvisitedNeighbors(const Maze& maze, const Maze::Coordinate& current)
    {
        std::vector<Maze::Coordinate> neighbors;
        
        auto next = current;
        --next.first;
        if( maze.Contains(next) && !maze.At(next).Visited() )
            neighbors.push_back(next);
        
        
        next = current;
        ++next.first;
        if( maze.Contains(next) && !maze.At(next).Visited() )
            neighbors.push_back(next);
        
        next = current;
        --next.second;
        if( maze.Contains(next) && !maze.At(next).Visited() )
            neighbors.push_back(next);
        
        next = current;
        ++next.second;
        if( maze.Contains(next) && !maze.At(next).Visited() )
            neighbors.push_back(next);

        return neighbors;
    }

    void Initialize(Maze& maze, Maze::Coordinate& coord)
    {
        VisitBorders(maze);
        maze.At(coord).Visit().Open();
        mVisitStack.push_back(coord);
    }

    bool NextStep(Maze& maze)
    {
        if( mVisitStack.empty() )
            throw std::runtime_error(std::string(__PRETTY_FUNCTION__) + " called with an empty stack");

        // if we don't have any neibhbors that haven't already been visited, we pop this cell off
        // the stack and check the prior cell
        auto available_neighbors = UnvisitedNeighbors(maze, mVisitStack.back());
        if( available_neighbors.empty() )
        {
            mVisitStack.pop_back();
            return false;
        }
        
        // otherwise, we randomly choose one to visit, and push it on the stack for the next call
        auto itr = std::begin(available_neighbors);
        std::advance(itr, std::rand() % available_neighbors.size());
        maze.At(*itr).Visit().Open();
        mVisitStack.push_back(*itr);

        return true;
    }
};

#endif // DEPTH_FIRST_POLICY
