#ifndef NCURSES_STREAM_HPP
#define NCURSES_STREAM_HPP

#include <string>
#include <ncurses.h>

#include "Character.hpp"

class NCursesStream
{
    /// \brief wrapper class around NCurses initialization and de-initialization methods
    struct NCurses
    {
        /// \brief constructor. Initializes ncurses
        NCurses()
        {
            initscr();
            cbreak();
            keypad(stdscr, TRUE);
            //noecho();
            refresh();
        }
        /// \brief destructor. tears down ncurses
        ~NCurses()
        {
            endwin();
        }
    };

    /// \brief parent class for all windows. Essentially an object oriented wrapper around the ncurses window
    class Window
    {
        int mHeight; ///< height of the window
        int mWidth; ///< width of the window
        int mStartY; ///< start row of the window (origin is top left)
        int mStartX; ///< start column of the window (origin is top left)

    protected:
        WINDOW* mAddress; ///< reference to ncurses window controlled by this object

    public:
        /// \brief Constructs a window with the given geometric position
        /// \param height the height of the window, in characters
        /// \param width the width of the window, in characters
        /// \param starty the start row of the window
        /// \param startx the start column of the window
        Window(int height, int width, int starty, int startx)
        : mHeight(height),
          mWidth(width),
          mStartY(starty),
          mStartX(startx),
          mAddress( newwin(mHeight, mWidth, mStartY, mStartX) )
        {
        }

        /// \brief Destroys a window
        ~Window()
        {
            delwin(mAddress);
            mAddress = nullptr;
        }

        // accessor method
        inline int Height() const { return mHeight; }
        inline int Width() const { return mWidth; }
        inline int StartX() const { return mStartX; }
        inline int StartY() const { return mStartY; }
        inline int EndX() const { return StartX() + Height(); }
        inline int EndY() const { return StartY() + Width(); }
    };

    /// \brief Window with a box on the outer edge
    struct BoxWindow : public Window
    {
        BoxWindow(int height, int width, int starty, int startx)
        : Window(height, width, starty, startx)
        {
            box(mAddress, 0, 0);
            wrefresh(mAddress);
        }
    };

    NCurses mNCurses; ///< structure for construction and destruction of the ncurses environment
    BoxWindow mOuterWindow; ///< outer window containing all game windows
    Window mDisplayWindow; ///< used to display map of current location
    BoxWindow mCharacterWindow; ///< used to display current character statistics
    BoxWindow mIOWindow; ///< used for input of command and output of game descriptions

public:
    NCursesStream(int display_height=30, int display_width=50, int io_window_height=5, int character_window_width=10)
    : mNCurses(),
      mOuterWindow(display_height+io_window_height+2, display_width+character_window_width+2, 0, 0),
      mDisplayWindow(display_height, display_width, 1, 1),
      mCharacterWindow(mDisplayWindow.Height(), character_window_width, mDisplayWindow.StartX(), mDisplayWindow.EndY()),
      mIOWindow(io_window_height, mOuterWindow.Width()-2, mDisplayWindow.EndX(), mDisplayWindow.StartY())
    {
    }

    ~NCursesStream()
    {
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

NCursesStream& operator<<(NCursesStream& out, const Character& character)
{
    //TODO
    return out;
}
NCursesStream& operator<<(NCursesStream& out, const std::string& narraration)
{
    //TODO
    return out;
}
NCursesStream& operator>>(NCursesStream& in, std::string& str)
{
    //TODO
    return in;
}
/*
NCursesStream& ostream<<(NCursesStream& out, const Dungeon& dungeon)
{
}
*/


#endif // NCURSES_STREAM_HPP
