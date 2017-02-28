#ifndef STDOUT_POLICY_HPP
#define STDOUT_POLICY_HPP

#include <ncurses.h> // use for characters (get actual symbols later)

// policy for outputing the maze to stdout
struct StdOutputPolicy
{
    void Initialize()
    {
    }

    void PrintOpen()
    {
        std::cout << ' ';
    }

    void PrintPlus()
    {
        std::cout << ACS_PLUS;
    }

    void PrintTopTee()
    {
        std::cout << ACS_TTEE;
    }

    void PrintBottomTee()
    {
        std::cout << ACS_BTEE;
    }

    void PrintLeftTee()
    {
        std::cout << ACS_LTEE;
    }

    void PrintRightTee()
    {
        std::cout << ACS_RTEE;
    }

    void PrintUpperLeftCorner()
    {
        std::cout << ACS_ULCORNER;
    }

    void PrintUpperRightCorner()
    {
        std::cout << ACS_URCORNER;
    }

    void PrintLowerLeftCorner()
    {
        std::cout << ACS_LLCORNER;
    }

    void PrintLowerRightCorner()
    {
        std::cout << ACS_LRCORNER;
    }

    void PrintHorizontalLine()
    {
        std::cout << ACS_HLINE;
    }

    void PrintVerticalLine()
    {
        std::cout << ACS_VLINE;
    }

    void EndRow()
    {
        std::cout << '\n';
    }

    std::string BlockingRead()
    {
        std::string str;
        std::cin >> str;
        return str;
    }

    void DisplayMessage(const std::string& msg)
    {
        std::cout << msg << '\n';
    }

    void Flush()
    {
        std::cout.flush();
    }
};
#endif // NCURSES_OUTPUT_POLICY_HPP

