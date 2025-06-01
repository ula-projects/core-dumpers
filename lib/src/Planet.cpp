#include "Planet.hpp"

Planet::Planet() : ground_sprite(Settings::textures["ground"])
{
}

Planet::~Planet()
{
}

void Planet::init(b2World &world)
{
    ground_sprite.setTextureRect({{0, 0}, {16, 16}});
    ground_body_def.type = b2_staticBody;
    ground_body_def.position.Set(0.f, 0.f); // Posición inicial (en píxeles)
    ground_body = world.CreateBody(&ground_body_def);
    generateFromImage();
    ground_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

void Planet::draw(sf::RenderWindow &window, sf::Vector2f _position)
{

    vector<shared_ptr<Ground>> tiles_to_draw = getTilesByRange(_position, Settings::VIEW_RANGE);

    for (auto tile : tiles_to_draw)
    {
        ground_sprite.setPosition({tile->getPosition().x * Settings::TILE_SIZE, tile->getPosition().y * Settings::TILE_SIZE});
        window.draw(ground_sprite);
    }
};

void Planet::generateFromImage()
{
    sf::Image planet;
    if (!planet.loadFromFile("./assets/textures/planet.png"))
    {
        throw std::runtime_error{"Error loading Planet's image"};
    }

    grid.clear();
    grid = std::vector(planet.getSize().x, std::vector(planet.getSize().y, (std::shared_ptr<Ground>)nullptr));

    for (size_t x = 0; x < grid.size(); x++)
    {
        for (size_t y = 0; y < grid[x].size(); y++)
        {
            sf::Color color = planet.getPixel({static_cast<unsigned int>(x), static_cast<unsigned int>(y)});

            if (color == sf::Color::White)
            {
                grid[x][y] = nullptr;
            }
            else if (color == sf::Color::Black)
            {
                grid[x][y] = std::make_shared<Ground>(GroundType::Rock, x, y);

                // auto ground = std::make_shared<Ground>(
                //     color == sf::Color::Black ? GroundType::Rock : GroundType::Core, x, y);

                // // Crear shape para ese tile
                b2PolygonShape shape;
                float tileSize = Settings::TILE_SIZE;
                float tileHalfSize = tileSize / 2.f;

                // // // Posición local relativa al body (que está en (0, 0))
                float worldX = x * tileSize;
                float worldY = y * tileSize;

                // // // Pasamos de píxeles a metros si lo necesitas (opcional)
                // // // Asegúrate que estés en las mismas unidades físicas en Box2D

                shape.SetAsBox(tileHalfSize, tileHalfSize,
                               b2Vec2(worldX + tileHalfSize, worldY + tileHalfSize), 0.f);

                b2FixtureDef fixture_def;
                fixture_def.shape = &shape;
                fixture_def.density = 1.f;
                fixture_def.friction = 1.f;
                // fixture_def.restitution = 0.3f;

                // ground->fixture =
                ground_body->CreateFixture(&fixture_def);

                // grid[x][y] = ground;
                // grid[x][y] = std::make_shared<Ground>(GroundType::Rock, x, y);
            }
            else if (color == sf::Color::Red)
            {
                grid[x][y] = std::make_shared<Ground>(GroundType::Core, x, y);
            }
        }
    }
};

vector<shared_ptr<Ground>> Planet::getTilesByRange(sf::Vector2f _position, unsigned int _range)
{
    unsigned int pos_x = _position.x / Settings::TILE_SIZE;
    unsigned int pos_y = _position.y / Settings::TILE_SIZE;

    long unsigned int x_begin = pos_x > _range ? pos_x - _range : 0;
    long unsigned int x_end = pos_x < Settings::PLANET_SIZE - _range ? pos_x + _range : Settings::PLANET_SIZE;
    long unsigned int y_begin = pos_y > _range ? pos_y - _range : 0;
    long unsigned int y_end = pos_y < Settings::PLANET_SIZE - _range ? pos_y + _range : Settings::PLANET_SIZE;

    vector<shared_ptr<Ground>> tile_list;

    for (size_t x = x_begin; x < x_end; ++x)
    {
        for (size_t y = y_begin; y < y_end; ++y)
        {
            auto cell = grid[x][y];
            if (cell)
            {
                tile_list.push_back(cell);
            }
        }
    }

    return tile_list;
};