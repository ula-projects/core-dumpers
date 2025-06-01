#include <box2d/box2d.h>
#include "Settings.hpp"
#include "ContactListener.hpp"
#include "Planet.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "Picaxe.hpp"
#include "Enemy.hpp"

class Game
{
private:
    // este es obvio xd jaja
    GameState game_state;

    // Menus del juego
    Menu menu;

    // Box2d World
    b2World world;
    ContactListener contact_listener;

    // Game Components
    Planet planet;
    Player player;
    std::vector<std::shared_ptr<Enemy>> enemies;
    Camera camera;
    Picaxe picaxe;

    // Background Image
    sf::Sprite background;

public:
    Game();
    ~Game();

    // Methods
    void update(float delta_time, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
};
