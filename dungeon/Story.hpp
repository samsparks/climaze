#ifndef STORY_HPP
#define STORY_HPP

#include <memory>
#include "Character.hpp"

class Story
{
protected:
    typedef std::unique_ptr<Story> story_ptr; ///< convience typedef used for declaring child stories
    Story* mParentPtr; ///< reference to parent story, which is executed when this one ends
    Character mCharacter;

    //TODO: dungeon
public:
    Story(Story* parent, Character& character)
    : mParentPtr(parent),
      mCharacter(character)
    {
    }

    virtual std::string Narraration() = 0;
    virtual Story* ProcessResponse(std::string&) = 0;
};

#endif // STORY_HPP
