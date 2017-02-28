#ifndef DEPTH_FIRST_POLICY
#define DEPTH_FIRST_POLICY
#include <stdexcept>
#include "Maze.hpp"

namespace Generator
{

/// \brief Policy to generate a maze using a depth-first algorithm. 
///        The Depth-First algorithm uses a stack to generate the maze. Each cell is
///        visited, and a neighbor candidate is randomly selected as the next cell. Once
///        there are no neighbor candidates, the stack is popped until an unvisited
///        neighbor cell is available, and that new path is then traversed to completion.
class DepthFirstPolicy
{
    std::vector<Maze::Coordinate> mVisitStack; ///< stack of previously visited cells

    /// \brief marks all borders as visted, to prevent them being opened
    /// \param[in] maze the maze whose borders should be visited
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

    /// \brief Returns a container of potential candidates for selection as the next cell to visit
    /// \param[in] maze reference to the maze being generated
    /// \param[in] current the current coordinate that neighbors are being chosen against
    /// \return container of valid candidates.
    std::vector<Maze::Coordinate> NextCandidates(const Maze& maze, const Maze::Coordinate& current)
    {
        std::vector<Maze::Coordinate> neighbors;
        
        // a neighboring cell is a candidate iff
        // 1. it has not yet been visited, AND
        // 2. it does not border an open cell

        for(int row : {-1, 0, 1} )
        {
            for( int col : {-1, 0, 1} )
            {
                // the current cell is not a candidate
                if( !row && !col )
                    continue;
                // diagonal cells are not candidates
                if( row && col )
                    continue;

                auto next_coord = std::make_pair(current.first+row, current.second+col);

                // previously visited cells are not candidates
                if( maze.At(next_coord).Visited() )
                    continue;

                // cells that border an open cell (besides this one) are not candidates
                if( col )
                {
                    if( maze.At(next_coord.first  , next_coord.second+col).Opened() || // check cell to the left/right
                        maze.At(next_coord.first-1, next_coord.second    ).Opened() || // check cell below
                        maze.At(next_coord.first+1, next_coord.second    ).Opened() || // check cell above
                        maze.At(next_coord.first-1, next_coord.second+col).Opened() || // check cell diagonal below
                        maze.At(next_coord.first+1, next_coord.second+col).Opened() )  // check cell diagonal above
                    {
                        continue;
                    }
                }
                else // row
                {
                    if( maze.At(next_coord.first+row, next_coord.second  ).Opened() || // check cell to the left/right
                        maze.At(next_coord.first    , next_coord.second-1).Opened() || // check cell below
                        maze.At(next_coord.first    , next_coord.second+1).Opened() || // check cell above
                        maze.At(next_coord.first+row, next_coord.second-1).Opened() || // check cell diagonal below
                        maze.At(next_coord.first+row, next_coord.second+1).Opened() )  // check cell diagonal above
                    {
                        continue;
                    }
                }
  
                neighbors.push_back(next_coord);
            }
        }
        return neighbors;
    }

public:

    void Initialize(Maze& maze, Maze::Coordinate& coord)
    {
        srand(time(NULL));
        VisitBorders(maze);
        maze.At(coord).Visit().Open();
        mVisitStack.push_back(coord);
    }

    bool NextStep(Maze& maze)
    {
        if( mVisitStack.empty() )
            return false;

        // if we don't have any neibhbors that haven't already been visited, we pop this cell off
        // the stack and check the prior cell
        auto available_neighbors = NextCandidates(maze, mVisitStack.back());
        if( available_neighbors.empty() )
        {
            mVisitStack.pop_back();
            return true;
        }
        
        // otherwise, we randomly choose one to visit, and push it on the stack for the next call
        auto itr = std::begin(available_neighbors);
        std::advance(itr, std::rand() % available_neighbors.size());
        maze.At(*itr).Visit().Open();
        mVisitStack.push_back(*itr);

        return true;
    }
};

}; // end namespace Generator
#endif // DEPTH_FIRST_POLICY
