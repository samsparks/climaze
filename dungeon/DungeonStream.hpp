#ifndef DUNGEON_STREAM_HPP
#define DUNGEON_STREAM_HPP

#include <iostream>

//FIXME: use iostream for read of user input and write of the maze, player, and story text
struct DungeonStream : public std::iostream
{
    DungeonStream()
    : std::iostream()
    {
        //TODO: initialize ncurses
    }

    ~DungeonStream()
    {
        //TODO: close out ncurses
    }
};

/* TODO
1. if not specialized, just write content story pane using ncurses
2. endl and flush need to be overridden to call ncurses content

Speciallize the following
DungeonStream& ostream<<(DungeonStream& out, const Player& player) // writes the player stats to the player pane
DungeonStream& ostream<<(DungeonStream& out, const Dungeon& dungeon) // write the dungeon (maze) to the maze pane

*/

#endif // DUNGEON_STREAM_HPP
