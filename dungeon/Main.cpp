/*
#include "Cell.hpp"
#include "Maze.hpp"
#include "Generator.hpp"
#include "Display.hpp"
#include "DepthFirstPolicy.hpp"
*/

#include <boost/algorithm/string/predicate.hpp>
#include <iostream>

#include "NCursesStream.hpp"
#include "Character.hpp"
#include "Story.hpp"

class CreationStory : public Story
{
public:
    explicit CreationStory( Story* parent, Character& character)
    : Story( parent, character )
    {
        //TODO: character.Reset();
    }

    virtual std::string Narraration()
    {
        return "Your character is named " + mCharacter.Name() + "\nPress enter to continue";
    }

    virtual Story* ProcessResponse(std::string&)
    {
        return mParentPtr;
    }
};

class ReplayStory : public Story
{
    bool mFailedToProcess;
    story_ptr mCreationStoryPtr;

public:
    explicit ReplayStory( Character& character )
    : Story( nullptr, character ),
      mFailedToProcess(false),
      mCreationStoryPtr(new CreationStory(this, mCharacter))
    {
    }

    virtual std::string Narraration()
    {
        if( mCreationStoryPtr )
            mCreationStoryPtr.release();

        std::string start = mFailedToProcess ? "Unknown response. Please try again\n" : "";
            
        return start + "Care to retry? [yes/no]";
    }

    virtual Story* ProcessResponse(std::string& response)
    {
        if( boost::starts_with(response, "y") )
        {
            mCreationStoryPtr.reset(new CreationStory(this, mCharacter));
            return mCreationStoryPtr.get();
        }

        if( boost::starts_with(response, "n") )
            return mParentPtr;

        mFailedToProcess = true;
        return this;
    }

    Story* GetStoryStartingPoint() const
    {
        return mCreationStoryPtr.get();
    }
};

/*
class DungeonCrawler
{
    enum class GameState
    {
        CREATION,   ///< initializes the dungeon crawler, creating the player, dungeon, etc
        TOWN,       ///< town story
        DUNGEON,    ///< dungeon story
        REPLAY,     ///< simple story where the user is prompted to play again or quit
        QUIT        ///< place-holder story indicating the user is quitting
    };

    const std::vector< std::unique_ptr<Story> > mStories; ///< the story to play at each state of the game
    GameState mGameState;

    
public:
    DungeonCrawler dungeon_crawler( std::unique_ptr<Story> creation_story, std::unique_ptr<Story> town_story, std::unique_ptr<Story> dungeon_story, std::unique_ptr<Story> replay_story )
    : mStories({creation_story, town_story, dungeon_story, replay_story),
      mGameState(CREATION)
    {
    }

    void advance()
    {
        
    }

    bool end() const
    {
        return mState == QUIT;
    }
    
}; */

// architecture:
//  - Display: renders the location, executes a story, shows player statistics
//  - Locations:
//    - Creation, containing
//      - Story - the creation account
//    - Town, containing
//      - shops
//      - Story - the story executed in the Village
//    - Dungeon, containing
//      - Maze: the maze to be solved, including
//        - Start & End postions
//        - Player position    
//        - Non-playable characters
//        - Rooms
//  - Player: object representing the player stats;
int main()
{
    // TODO: load game configuration file
    // TODO: I would like to build this on the CAF framework https://actor-framework.org
    NCursesStream nstream;
    Character player1;

    ReplayStory replay_story(player1);
    Story* story_ptr = replay_story.GetStoryStartingPoint();

    std::string response;
    while( story_ptr )
    {
        nstream //<< TODO: player1
                << story_ptr->Narraration()
                ; // TODO: << std::endl;
        nstream.flush();
        nstream >> response;

        story_ptr = story_ptr->ProcessResponse(response);
    }
}
