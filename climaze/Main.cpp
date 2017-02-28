#include <iostream>

#include "Maze.hpp"
#include "Generator.hpp"
#include "Display.hpp"
#include "DepthFirstPolicy.hpp"

int main()
{
    Generator::Generator<Generator::DepthFirstPolicy, Display::NCursesOutputPolicy> generator(boost::posix_time::milliseconds(10));

    auto maze = generator.Build(30, 30, 1, 1);

    Display::Display<Display::NCursesOutputPolicy> display;
    display.Update(maze, "Enter any character to exit");
    display.GetUserInput();
}
