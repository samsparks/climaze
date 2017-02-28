
#ifndef NCURSES_OUTPUT_POLICY_HPP
#define NCURSES_OUTPUT_POLICY_HPP

#include <ncurses.h>

namespace Display
{

// policy for outputing the maze to ncurses
struct NCursesOutputPolicy
{
    NCursesOutputPolicy()
    {
        initscr();
    }
    ~NCursesOutputPolicy()
    {
        endwin();
    }

    void Initialize()
    {
        move(0,0);
    }

    void PrintOpen()
    {
        addch(' ');
    }

    void PrintPlus()
    {
        addch(ACS_PLUS);
    }

    void PrintTopTee()
    {
        addch(ACS_TTEE);
    }

    void PrintBottomTee()
    {
        addch(ACS_BTEE);
    }

    void PrintLeftTee()
    {
        addch(ACS_LTEE);
    }

    void PrintRightTee()
    {
        addch(ACS_RTEE);
    }

    void PrintUpperLeftCorner()
    {
        addch(ACS_ULCORNER);
    }

    void PrintUpperRightCorner()
    {
        addch(ACS_URCORNER);
    }

    void PrintLowerLeftCorner()
    {
        addch(ACS_LLCORNER);
    }

    void PrintLowerRightCorner()
    {
        addch(ACS_LRCORNER);
    }

    void PrintHorizontalLine()
    {
        addch(ACS_HLINE);
    }

    void PrintVerticalLine()
    {
        addch(ACS_VLINE);
    }

    void EndRow()
    {
        printw("\n");
    }

    std::string BlockingRead()
    {
        return std::string(1, getch());
    }

    void DisplayMessage(const std::string& msg)
    {
        printw((msg + '\n').c_str());
    }

    void Flush()
    {
        refresh();
    }
};

}; // end namespace Display
#endif // NCURSES_OUTPUT_POLICY_HPP

