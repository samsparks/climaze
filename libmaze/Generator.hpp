#ifndef GENERATOR_HPP
#define GENERATOR_HPP
#include <stdexcept>
#include <algorithm>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/thread/thread.hpp>

#include "Maze.hpp"
#include "Display.hpp"
#include "DepthFirstPolicy.hpp"

namespace Generator
{

///< template for policy-based design, so different output formats can be used
template <typename Maze, typename GenerationPolicy, typename OutputPolicy = Display::NullOutputPolicy> 
class Generator : private GenerationPolicy
{
    using GenerationPolicy::Initialize;
    using GenerationPolicy::NextStep;

    const boost::posix_time::time_duration mUpdateDelay; ///< amount of time to delay between steps.
    Display::Display<Maze, OutputPolicy> mDisplay;

public:
    Generator(boost::posix_time::time_duration update_delay = boost::posix_time::not_a_date_time)
    : mUpdateDelay(update_delay)
    {
    }

    Maze Build(size_t rows, size_t columns, size_t start_row, size_t start_column)
    {
        Maze maze(rows, columns);

        Coordinate start(1, 1);
        Initialize(maze, start);

        do
        {
            mDisplay.Update(maze);
            if( !mUpdateDelay.is_special() )
            {
                boost::this_thread::sleep( mUpdateDelay );
            }
            else
            {
                mDisplay.GetUserInput();
            }
        } while( NextStep(maze) );

        return maze;
    }

};

}; // end namespace Generator

#endif // GENERATOR_HPP
