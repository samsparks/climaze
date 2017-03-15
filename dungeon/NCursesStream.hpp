#ifndef NCURSES_STREAM_HPP
#define NCURSES_STREAM_HPP

#include <string>
#include <ncurses.h>
#include <boost//algorithm/string.hpp>

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
        size_t mHeight; ///< height of the window
        size_t mWidth; ///< width of the window
        size_t mStartRow; ///< start row of the window (origin is top left)
        size_t mStartCol; ///< start column of the window (origin is top left)

        WINDOW* mAddress; ///< reference to ncurses window controlled by this object

    public:
        /// \brief Constructs a window with the given geometric position
        /// \param height the height of the window, in characters
        /// \param width the width of the window, in characters
        /// \param start_row the start row of the window
        /// \param start_col the start column of the window
        Window(size_t height, size_t width, size_t start_row, size_t start_col)
        : mHeight(height),
          mWidth(width),
          mStartRow(start_row),
          mStartCol(start_col),
          mAddress( newwin(static_cast<int>(mHeight), static_cast<int>(mWidth), static_cast<int>(mStartRow), static_cast<int>(mStartCol)) )
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
        inline size_t Height() const { return mHeight; }
        inline size_t Width() const { return mWidth; }
        inline size_t StartRow() const { return mStartRow; }
        inline size_t EndRow() const { return StartRow() + Height(); }
        inline size_t StartColumn() const { return mStartCol; }
        inline size_t EndColumn() const { return StartColumn() + Width(); }
        inline void Refresh() { wrefresh(mAddress); }
    };

    /// \brief Window with a box on the outer edge
    struct BoxWindow : public Window
    {
        BoxWindow(size_t height, size_t width, size_t start_row, size_t start_col)
        : Window(height, width, start_row, start_col)
        {
            box(mAddress, 0, 0);
        }
    };

    class InputWindow : public Window
    {
        const std::string mPrompt = "> ";
        const size_t mMaxInputLength;
        
    public:
        InputWindow(size_t height, size_t width, size_t start_row, size_t start_col)
        : Window(height, width, start_row, start_col),
          mPrompt("> "),
          mMaxInputLength(Width() - mPrompt.length())
        {
            mvwprintw(mAddress, 0, 0, "%s", mPrompt.c_str());
        }

        std::string Read()
        {
            bool enter_received = false;
            std::string msg;

            while( !enter_received )
            {
                auto c = wgetch(mAddress);
                switch( c )
                {
                case 0x08: // backspace
                case 0x7F: // delete
                    if( !msg.empty() )
                        msg.pop_back();
                    break;
                case '\n':
                case '\r':
                    enter_received = true;
                    break;
                default:
                    if( std::isprint(c) )
                        msg.push_back(c);
                }
                mvwprintw(mAddress, 0, mPrompt.length(), "%s", msg.c_str());
                wclrtoeol(mAddress);
                wrefresh(mAddress);
            }
            wmove(mAddress, 0, mPrompt.length());
            wclrtoeol(mAddress);
                
            wrefresh(mAddress);
            return msg;
        }
    };

    class OutputWindow : public BoxWindow
    {
    public:
        OutputWindow(size_t height, size_t width, size_t start_row, size_t start_col)
        : BoxWindow(height, width, start_row, start_col)
        {
            box(mAddress, 0, 0);
        }

        void Write(const std::string& msg)
        {
        //std::cerr << "Msg: " << msg << '\n';// XXX
            // put the message into the history, splitting lines that are longer than the window or have a newline

            // split on newlines
            std::vector<std::string> lines;
            boost::split(lines, msg, boost::is_any_of("\r\n"));

            // split long-lines into two lines
            for(auto itr=lines.begin(); itr!=lines.end(); ++itr)
            {
                if( itr->size() > Width() - 2 )
                {
                    lines.insert(itr, itr->substr(0, Width()-2));
                    itr->erase(Width()-2);
                }
            }

            //TODO: handle messages longer than Height()-2 lines long
            //TODO: add ability to scroll up and see history

            if(lines.size() > Height()-2)
            {
                mvwprintw(mAddress, 1, 1, "ERROR: Message too long (%d lines)", lines.size());
            }
            else
            {
                for(size_t i=1; i<(Height()-2); ++i)
                {
                    wmove(mAddress, i, 1);
                    if( lines.size() >= i )
                        wprintw(mAddress, "%s", lines.at(i-1).c_str());
                    wclrtoeol(mAddress);
                }
            }        
            box(mAddress, 0, 0);
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
    NCursesStream(size_t display_height=30, size_t display_width=50, size_t output_window_height=5, size_t character_window_width=10)
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
