#include <iostream>

#include "Maze.hpp"
#include "DepthFirstGenerator.hpp"
#include "NCursesOutputPolicy.hpp"
#include "Display.hpp"

int main()
{
    Maze maze(20,40);
    Display<NCursesOutputPolicy> display;
    display.Update(maze);
    display.GetUserInput();
    DepthFirstGenerator generator(maze);

    auto start = std::make_pair<size_t,size_t>(1,1);
    generator.Generate(start);

    display.Update(maze);
    display.GetUserInput();
}
