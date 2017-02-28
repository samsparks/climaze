#include <iostream>

#include "Maze.hpp"
#include "Generator.hpp"
#include "Display.hpp"
#include "NCursesOutputPolicy.hpp"
#include "StdOutPolicy.hpp"
#include "DepthFirstPolicy.hpp"

int main()
{
    //Display<NCursesOutputPolicy> display;
    Display<StdOutputPolicy> display;
    Generator<DepthFirstPolicy, StdOutputPolicy> generator;

    auto maze = generator.Build(20, 30, 1, 1);

    display.Update(maze);
    display.GetUserInput();
}
