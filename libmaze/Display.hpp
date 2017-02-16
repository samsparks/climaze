#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <stdexcept>

///< template for policy-based design, so different output formats can be used
template <typename OutputPolicy>
class Display : private OutputPolicy
{
    using OutputPolicy::Initialize;
    using OutputPolicy::PrintOpen;
    using OutputPolicy::PrintPlus;
    using OutputPolicy::PrintTopTee;
    using OutputPolicy::PrintBottomTee;
    using OutputPolicy::PrintLeftTee;
    using OutputPolicy::PrintRightTee;
    using OutputPolicy::PrintUpperLeftCorner;
    using OutputPolicy::PrintUpperRightCorner;
    using OutputPolicy::PrintLowerLeftCorner;
    using OutputPolicy::PrintLowerRightCorner;
    using OutputPolicy::PrintHorizontalLine;
    using OutputPolicy::PrintVerticalLine;
    using OutputPolicy::EndRow;
    using OutputPolicy::DisplayMessage;
    using OutputPolicy::Flush;
    using OutputPolicy::BlockingRead;

public:
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
    std::string GetUserInput()
    {
        return BlockingRead();
    }

};

#endif // DISPLAY_HPP
