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
            curs_set(0); // hide the cursor
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
    protected:
        int mHeight; ///< height of the window
        int mWidth; ///< width of the window
        int mStartRow; ///< start row of the window (origin is top left)
        int mStartCol; ///< start column of the window (origin is top left)

        WINDOW* mAddress; ///< reference to ncurses window controlled by this object

    public:
        /// \brief Constructs a window with the given geometric position
        /// \param height the height of the window, in characters
        /// \param width the width of the window, in characters
        /// \param start_row the start row of the window
        /// \param start_col the start column of the window
        Window(int height, int width, int start_row, int start_col)
        : mHeight(height),
          mWidth(width),
          mStartRow(start_row),
          mStartCol(start_col),
          mAddress( newwin(mHeight, mWidth, mStartRow, mStartCol) )
        {
            //std::cerr << "Window(" << height << "," << width << "," << start_row << "," << start_col << ")\n"; // XXX
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
        inline int StartRow() const { return mStartRow; }
        inline int EndRow() const { return StartRow() + Height(); }
        inline int StartColumn() const { return mStartCol; }
        inline int EndColumn() const { return StartColumn() + Width(); }
        inline void Refresh() { wrefresh(mAddress); }
    };

    /// \brief Window with a box on the outer edge
    struct BoxWindow : public Window
    {
        BoxWindow(int height, int width, int start_row, int start_col)
        : Window(height, width, start_row, start_col)
        {
            box(mAddress, 0, 0);
        }
    };

    class InputWindow : public Window
    {
        const std::string mPrompt = "> ";
        const int mMaxInputLength;
        
    public:
        InputWindow(int height, int width, int start_row, int start_col)
        : Window(height, width, start_row, start_col),
          mPrompt("> "),
          mMaxInputLength(Width() - mPrompt.length())
        {
            mvwprintw(mAddress, 0, 0, "%s", mPrompt.c_str());
        }

        std::string Read()
        {
            bool enter_received = false;
            std::string msg(mMaxInputLength, ' ');
            int index = 0;

            while( !enter_received )
            {
                auto c = wgetch(mAddress);
                switch( c )
                {
                case 0x08: // backspace
                case 0x7F: // delete
                    if( !msg.empty() )
                        msg[index--] = ' ';
                    break;
                case '\n':
                case '\r':
                    enter_received = true;
                    break;
                default:
                    if( std::isprint(c) )
                        msg[index++] = c;
                }
                mvwprintw(mAddress, 0, mPrompt.length(), "%s", msg.c_str());
                wrefresh(mAddress);

                //TODO: we could make this more intelligent
                /*
                if(index == MAX_INPUT_LENGTH)
                    enter_received = true;
                */
            }
            wmove(mAddress, 0, mPrompt.length());
            for(auto i=0; i<index; ++i)
                waddch(mAddress, ' ');
                
            wrefresh(mAddress);
            return msg;
        }
    };

    struct OutputWindow : public BoxWindow
    {
        OutputWindow(int height, int width, int start_row, int start_col)
        : BoxWindow(height, width, start_row, start_col)
        {
            box(mAddress, 0, 0);
        }

        void Write(const std::string& msg)
        {
            mvwprintw(mAddress, 1, 1, "%s", msg.c_str());
            wrefresh(mAddress);
        }
    };

    NCurses mNCurses; ///< structure for construction and destruction of the ncurses environment
    Window mDisplayWindow; ///< used to display map of current location
    BoxWindow mCharacterWindow; ///< used to display current character statistics
    OutputWindow mOutputWindow; ///< used for output game narraration
    InputWindow mInputWindow; ///< used for input of commands
    BoxWindow mOuterWindow; ///< outer window containing all game windows

public:
    NCursesStream(int display_height=30, int display_width=50, int output_window_height=5, int character_window_width=10)
    : mNCurses(),
      mDisplayWindow(display_height, display_width, 1, 1),
      mCharacterWindow(mDisplayWindow.Height(), character_window_width, mDisplayWindow.StartRow(), mDisplayWindow.EndColumn()+1),
      mOutputWindow(output_window_height, mCharacterWindow.EndColumn()-mDisplayWindow.StartColumn(), mDisplayWindow.EndRow()+1, mDisplayWindow.StartColumn()),
      mInputWindow(1,                     mOutputWindow.Width(), mOutputWindow.EndRow()+1, mDisplayWindow.StartColumn()),
      mOuterWindow(mInputWindow.EndRow()+1, mInputWindow.EndColumn()+1, 0, 0)
    {
        mOuterWindow.Refresh();
        mDisplayWindow.Refresh();
        mCharacterWindow.Refresh();
        mOutputWindow.Refresh();
        mInputWindow.Refresh();
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
    friend NCursesStream& operator<<(NCursesStream& out, const Character& character);
    friend NCursesStream& operator<<(NCursesStream& out, const std::string& narraration);
    friend NCursesStream& operator>>(NCursesStream& in, std::string& str);
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
    out.mOutputWindow.Write(narraration);
    return out;
}
NCursesStream& operator>>(NCursesStream& in, std::string& str)
{
    str = in.mInputWindow.Read();
    return in;
}
/*
NCursesStream& ostream<<(NCursesStream& out, const Dungeon& dungeon)
{
}
*/


#endif // NCURSES_STREAM_HPP
