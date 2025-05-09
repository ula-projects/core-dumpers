#pragma once

#include <Player.hpp>

class Game
{
public:
    Game() noexcept;
    void update();

private:
    int game_status;
};