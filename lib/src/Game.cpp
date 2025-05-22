#include <Game.hpp>

Game::Game() : camera(player.getPosition()), ground(ground_texture), background(background_texture)
{
    world_center.setCoordinates(512, 512);
    world_boundary.setBoundary(world_center, 512, 512);

    qt.setBoundary(world_boundary);
    qt.generateWorld();

    if (!ground_texture.loadFromFile("./assets/textures/world_tileset.png"))
    {
    }
    ground.setTextureRect({{0, 16}, {16, 16}});
    ground.setOrigin({8, 8});
    ground_ptr = std::make_shared<sf::Sprite>(ground);
    if (!background_texture.loadFromFile("./assets/textures/nebula-3.png"))
    {
    }
    background.setTextureRect({{0, 0}, {1024, 1024}});

    view_boundary.setBoundary(XY(camera.getCenter().x, camera.getCenter().y), 160, 90);

    collision_boundary.setBoundary(XY(player.getPosition().x, player.getPosition().y), 16, 16);

    game_state = 0;
}

void Game::draw(sf::RenderWindow &window)
{

    if (game_state == 0)
    {
        menu.mainMenuDraw(window);
    }
    else if (game_state == 1)
    {
        window.draw(background);
        for (auto ground : ground_list)
        {
            ground->draw(window, ground_ptr);
        }
        window.setView(camera.getCamera());
        player.draw(window);
    }
}

void Game::update(float &delta_time, sf::RenderWindow &window)
{
    // sf::Mouse::getPosition(window);
    view_boundary.setBoundary(XY(camera.getCenter().x, camera.getCenter().y), view_boundary.half_width, view_boundary.half_height);
    collision_boundary.setBoundary(XY(player.getPosition().x, player.getPosition().y), collision_boundary.half_width, collision_boundary.half_height);

    // Menu Principal
    if (game_state == 0)
    {
        menu.mainMenuUpdate(window, game_state);
    }
    // Juego
    else if (game_state == 1)
    {
        ground_list = qt.queryRange(view_boundary);
        collision_list = qt.queryRange(collision_boundary);
        player.update(delta_time, collision_list);
        camera.setCenter(player.getPosition(), delta_time);
    }
}
