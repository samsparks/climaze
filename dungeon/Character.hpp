#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

class Character
{
    std::string mName;
    bool mAlive;
public:
    Character(std::string name = "Player 1")
    : mName(name),
      mAlive(true)
    {
    }

    std::string Name() const { return mName; } ///TODO: fixme -will be replaced with operator<<

    void SetAlive(bool alive)
    {
        mAlive = alive;
    }

    bool IsAlive() const
    {
        return mAlive;
    }
};

#endif // CHARACTER_HPP
