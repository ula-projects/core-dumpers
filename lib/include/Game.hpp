#include <box2d/box2d.h>
#include "Settings.hpp"
#include "Planet.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "Camera.hpp"

class Game
{
private:
    GameState game_state;

    // Box2d World
    b2Vec2 gravity;
    b2World world;

    // Menus
    Menu menu;

    // Game Components
    Planet planet;
    Player player;
    Camera camera;

    // Background Image
    sf::Sprite background;

public:
    Game();
    ~Game();

    // Methods
    void update(float delta_time, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    // GameState getGameState();
    // void setGameState(GameState _state);
};
