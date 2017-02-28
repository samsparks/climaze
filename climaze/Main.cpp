#include <iostream>

#include "Maze.hpp"
#include "Generator.hpp"
#include "Display.hpp"
#include "NCursesOutputPolicy.hpp"
#include "StdOutPolicy.hpp"
#include "DepthFirstPolicy.hpp"

int main()
{
    //Generator<DepthFirstPolicy, StdOutputPolicy> generator;
    Generator<DepthFirstPolicy, NullOutputPolicy> generator;

    auto maze = generator.Build(30, 30, 1, 1);

    Display<NCursesOutputPolicy> display;
    display.Update(maze);
    display.GetUserInput();
}
