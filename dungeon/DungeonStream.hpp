#ifndef DUNGEON_STREAM_HPP
#define DUNGEON_STREAM_HPP

#include <string>
#include <ncurses.h>

#include "Character.hpp"

class DungeonStream
{
    //TODO: make the read-pane a vector with a scrollable history
    size_t mDungeonPaneHeight; ///< specifies the number of characters that fit laterally within the dungeon pane
    size_t mDungeonPaneWidth; ///< specifies the number of characters that fit vertically within the dungeon pane
    size_t mCharacterPaneWidth; ///< specifies the number of characters that fit laterally within the dungeon pane
    size_t mIOPaneHeight; ///< specifies the number of characters that fit vertically within the dungeon pane

public:
    DungeonStream()
    :  mDungeonPaneHeight(20),
       mDungeonPaneWidth(20),
       mCharacterPaneWidth(10),
       mIOPaneHeight(10)
    {
        initscr();
        Reset(); 
    }

    ~DungeonStream()
    {
        endwin();
    }

    void Reset()
    {
        // top line
        move(0,0);
        addch(ACS_ULCORNER);
        for(size_t i = 0; i < mDungeonPaneWidth; ++i)
            addch(ACS_HLINE);
        addch(ACS_TTEE);
        for(size_t i = 0; i < mCharacterPaneWidth; ++i)
            addch(ACS_HLINE);
        addch(ACS_URCORNER);
        printw("\n");

        // empty dungeon and character panes
        for(size_t r = 0; r < mDungeonPaneHeight; ++r)
        {
            addch(ACS_VLINE);
            for(size_t c = 0; c < mDungeonPaneWidth; ++c)
                addch(' ');
            addch(ACS_VLINE);
            for(size_t c = 0; c < mCharacterPaneWidth; ++c)
                addch(' ');
            addch(ACS_VLINE);
            printw("\n");
        }

        // seperator between dungeon/character panes and the io pane
        addch(ACS_LTEE);
        for(size_t i = 0; i< mDungeonPaneWidth; ++i)
            addch(ACS_HLINE);
        addch(ACS_BTEE);
        for(size_t i = 0; i< mCharacterPaneWidth; ++i)
            addch(ACS_HLINE);
        addch(ACS_RTEE);
        printw("\n");
        
        // empty io pane
        for(size_t r = 0; r < mIOPaneHeight; ++r)
        {
            addch(ACS_VLINE);
            for(size_t c = 0; c < mDungeonPaneWidth+mCharacterPaneWidth+1; ++c)
                addch(' ');
            addch(ACS_VLINE);
            printw("\n");
        }

        //bottom of the display
        addch(ACS_LLCORNER);
        for(size_t c = 0; c < mDungeonPaneWidth+mCharacterPaneWidth+1; ++c)
            addch(ACS_HLINE);
        addch(ACS_LRCORNER);
        printw("\n");

        refresh();
    }

    void flush()
    {
        refresh();
    }

    // TODO: add iomanip methods:
    // SetMazePaneHeight
    // SetMazePaneWidth
    // SetCharacterPaneHeight
    // SetCharacterPaneWidth
    // SetIOPaneHeight
    // SetIOPaneWidth
};

/* TODO
1. if not specialized, just write content story pane using ncurses
2. endl and flush need to be overridden to call ncurses content

Speciallize the following
*/

DungeonStream& operator<<(DungeonStream& out, const Character& character)
{
    //TODO
    return out;
}
DungeonStream& operator<<(DungeonStream& out, const std::string& narraration)
{
    //TODO
    return out;
}
DungeonStream& operator>>(DungeonStream& in, std::string& str)
{
    //TODO
    return in;
}
/*
DungeonStream& ostream<<(DungeonStream& out, const Dungeon& dungeon)
{
}
*/


#endif // DUNGEON_STREAM_HPP
