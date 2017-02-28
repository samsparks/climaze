#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <stdexcept>
#include "NCursesPolicy.hpp"
#include "StdOutPolicy.hpp"
#include "NullPolicy.hpp"

namespace Display {
///< template for policy-based design, so different output formats can be used
/// \brief Responsible for rendering a maze and conditionally blocking on user input according to
///        a specified User-Interface policy.
template <typename UIPolicy>
class Display : private UIPolicy
{
    using UIPolicy::Initialize;
    using UIPolicy::PrintOpen;
    using UIPolicy::PrintPlus;
    using UIPolicy::PrintTopTee;
    using UIPolicy::PrintBottomTee;
    using UIPolicy::PrintLeftTee;
    using UIPolicy::PrintRightTee;
    using UIPolicy::PrintUpperLeftCorner;
    using UIPolicy::PrintUpperRightCorner;
    using UIPolicy::PrintLowerLeftCorner;
    using UIPolicy::PrintLowerRightCorner;
    using UIPolicy::PrintHorizontalLine;
    using UIPolicy::PrintVerticalLine;
    using UIPolicy::EndRow;
    using UIPolicy::DisplayMessage;
    using UIPolicy::Flush;
    using UIPolicy::BlockingRead;

public:
    /// \brief Updates the display with the given maze and message.
    /// \param[in] maze the maze to show
    /// \param[in] msg an optional string to display to the user. Empty strings are ignored
    void Update(const Maze& maze, const std::string msg = "")
    {
        Initialize();
        for(unsigned row=0; row<maze.Rows(); ++row)
        {
            for(unsigned col=0; col<maze.Columns(); ++col)
            {
                if( maze.At(row, col).Opened() )
                {
                    PrintOpen();
                }
                else
                {
                    bool closed_above = maze.Contains(row-1,col) && !maze.At(row-1,col).Opened();
                    bool closed_below = maze.Contains(row+1,col) && !maze.At(row+1,col).Opened();
                    bool closed_left  = maze.Contains(row,col-1) && !maze.At(row,col-1 ).Opened();
                    bool closed_right = maze.Contains(row,col+1) && !maze.At(row,col+1).Opened();
                  
                    if( closed_above && closed_below && closed_right && closed_left )
                        PrintPlus();
                    else if( closed_below && closed_right && closed_left )
                        PrintTopTee();
                    else if( closed_above && closed_right && closed_left )
                        PrintBottomTee();
                    else if( closed_above && closed_below && closed_left )
                        PrintRightTee();
                    else if( closed_above && closed_below && closed_right)
                        PrintLeftTee();
                    else if( closed_below && closed_right )
                        PrintUpperLeftCorner();
                    else if( closed_below && closed_left )
                        PrintUpperRightCorner();
                    else if( closed_above && closed_right )
                        PrintLowerLeftCorner();
                    else if( closed_above && closed_left )
                        PrintLowerRightCorner();
                    else if( closed_left || closed_right )
                        PrintHorizontalLine();
                    else if( closed_above || closed_below )
                        PrintVerticalLine();
                    else
                        throw std::runtime_error("Display: Unhandled cell detected");
                }
            }
            EndRow();
        }
       
        if(!msg.empty())
        {
            DisplayMessage(msg);
        }
       
        Flush();
    }

    /// \brief Returns the value obtained by a blocking read
    /// \returns a string representation of the value returend by the UI Policy's blocking read
    std::string GetUserInput()
    {
        return BlockingRead();
    }
};

};
#endif // DISPLAY_HPP
