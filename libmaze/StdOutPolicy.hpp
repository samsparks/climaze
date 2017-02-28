#ifndef STDOUT_POLICY_HPP
#define STDOUT_POLICY_HPP

namespace Display
{

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
        std::cout << '#';
    }

    void PrintTopTee()
    {
        std::cout << '#';
    }

    void PrintBottomTee()
    {
        std::cout << '#';
    }

    void PrintLeftTee()
    {
        std::cout << '#';
    }

    void PrintRightTee()
    {
        std::cout << '#';
    }

    void PrintUpperLeftCorner()
    {
        std::cout << '#';
    }

    void PrintUpperRightCorner()
    {
        std::cout << '#';
    }

    void PrintLowerLeftCorner()
    {
        std::cout << '#';
    }

    void PrintLowerRightCorner()
    {
        std::cout << '#';
    }

    void PrintHorizontalLine()
    {
        std::cout << '#';
    }

    void PrintVerticalLine()
    {
        std::cout << '#';
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

}; // end namespace Display
#endif // NCURSES_OUTPUT_POLICY_HPP

