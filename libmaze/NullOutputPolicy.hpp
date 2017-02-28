#ifndef NULL_OUTPUT_POLICY_HPP
#define NULL_OUTPUT_POLICY_HPP

// policy for not outputing the maze
struct NullOutputPolicy
{
    void Initialize()
    {
    }

    void PrintOpen()
    {
    }

    void PrintPlus()
    {
    }

    void PrintTopTee()
    {
    }

    void PrintBottomTee()
    {
    }

    void PrintLeftTee()
    {
    }

    void PrintRightTee()
    {
    }

    void PrintUpperLeftCorner()
    {
    }

    void PrintUpperRightCorner()
    {
    }

    void PrintLowerLeftCorner()
    {
    }

    void PrintLowerRightCorner()
    {
    }

    void PrintHorizontalLine()
    {
    }

    void PrintVerticalLine()
    {
    }

    void EndRow()
    {
    }

    std::string BlockingRead()
    {
        return "";
    }

    void DisplayMessage(const std::string& msg)
    {
    }

    void Flush()
    {
    }
};
#endif // NULL_OUTPUT_POLICY_HPP

