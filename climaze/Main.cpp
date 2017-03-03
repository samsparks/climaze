#include <iostream>

#include "Cell.hpp"
#include "Maze.hpp"
#include "Generator.hpp"
#include "Display.hpp"
#include "DepthFirstPolicy.hpp"

int main()
{
    Display::Display<Maze<Cell>, Display::NCursesOutputPolicy> display;
    Generator::Generator<Maze<Cell>,
                         Generator::DepthFirstPolicy<Maze<Cell>>,
                         Display::NCursesOutputPolicy> generator(boost::posix_time::milliseconds(10));

    auto maze = generator.Build(30, 30, 1, 1);

    display.Update(maze, "Enter any character to exit");
    display.GetUserInput();
}
