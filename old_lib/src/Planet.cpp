#include <Planet.hpp>

Planet::Planet(b2World &world) : ground_sprite(Settings::textures.at("ground"))
{

    // int tile_size = Settings::TILE_SIZE;
    // float tile_half_size = tile_size / 2;
    // ground_sprite.setTextureRect({{0, tile_size}, {tile_size, tile_size}});
    // ground_sprite.setOrigin({tile_half_size, tile_half_size});

    // ground_body_def.type = b2_staticBody;
    // ground_body_def.position.Set(0, 0);
    // ground_body = world.CreateBody(&ground_body_def);
}

Planet::~Planet()
{
}

// update fixtures
void Planet::update(float _delta_time, b2World &world, sf::Vector2f _position)
{

    // std::vector<std::shared_ptr<Ground>> tiles = getTilesByRange(_position, Settings::VIEW_RANGE);

    // for (auto tile : tiles)
    // {
    // }
}

void Planet::draw(sf::RenderWindow &window, sf::Vector2f _position) {

    // std::vector<std::shared_ptr<Ground>> tiles_to_draw = getTilesByRange(_position, Settings::VIEW_RANGE);

    // for (auto tile : tiles_to_draw)
    // {
    //     ground_sprite.setPosition({static_cast<float>(tile->x * Settings::TILE_SIZE), static_cast<float>(tile->y * Settings::TILE_SIZE)});
    //     window.draw(ground_sprite);
    // }
};

std::vector<std::shared_ptr<Ground>> Planet::getTilesByRange(sf::Vector2f _position, unsigned int _range)
{
    // unsigned int pos_x = _position.x / Settings::TILE_SIZE;
    // unsigned int pos_y = _position.y / Settings::TILE_SIZE;

    // long unsigned int x_begin = pos_x > _range ? pos_x - _range : 0;
    // long unsigned int x_end = pos_x < Settings::PLANET_RADIUS * 2 ? pos_x + _range : Settings::PLANET_RADIUS * 2;
    // long unsigned int y_begin = pos_y > _range ? pos_y - _range : 0;
    // long unsigned int y_end = pos_y < Settings::PLANET_RADIUS * 2 ? pos_y + _range : Settings::PLANET_RADIUS * 2;

    std::vector<std::shared_ptr<Ground>> tile_list;

    // for (size_t x = x_begin; x < x_end; ++x)
    // {
    //     for (size_t y = y_begin; y < y_end; ++y)
    //     {
    //         auto cell = grid[x][y];
    //         if (cell)
    //         {
    //             tile_list.push_back(cell);
    //         }
    //     }
    // }

    return tile_list;
};

void Planet::generateFromImage(b2World &world)
{
    // sf::Image planet;
    // if (!planet.loadFromFile("./assets/textures/planet.png"))
    // {
    //     throw std::runtime_error{"Error loading Planet's image"};
    // }

    // grid.clear();
    // grid = std::vector(planet.getSize().x, std::vector(planet.getSize().y, (std::shared_ptr<Ground>)nullptr));

    // for (size_t x = 0; x < grid.size(); x++)
    // {
    //     for (size_t y = 0; y < grid[x].size(); y++)
    //     {
    //         sf::Color color = planet.getPixel({static_cast<unsigned int>(x), static_cast<unsigned int>(y)});

    //         if (color == sf::Color::White)
    //         {
    //             grid[x][y] = nullptr;
    //         }
    //         else if (color == sf::Color::Black)
    //         {
    //             auto ground = std::make_shared<Ground>(
    //                 color == sf::Color::Black ? GroundType::Rock : GroundType::Core, x, y);

    //             // Crear shape para ese tile
    //             b2PolygonShape shape;
    //             float tileSize = static_cast<float>(Settings::TILE_SIZE);
    //             float tileHalfSize = tileSize / 2.f;

    //             // Posición local relativa al body (que está en (0, 0))
    //             float worldX = x * tileSize;
    //             float worldY = y * tileSize;

    //             // Pasamos de píxeles a metros si lo necesitas (opcional)
    //             // Asegúrate que estés en las mismas unidades físicas en Box2D

    //             shape.SetAsBox(tileHalfSize, tileHalfSize,
    //                            b2Vec2(worldX + tileHalfSize, worldY + tileHalfSize), 0.f);

    //             b2FixtureDef fixtureDef;
    //             fixtureDef.shape = &shape;
    //             fixtureDef.density = 1.f;
    //             fixtureDef.friction = 0.3f;

    //             ground->fixture = ground_body->CreateFixture(&fixtureDef);

    //             grid[x][y] = ground;
    //             // grid[x][y] = std::make_shared<Ground>(GroundType::Rock, x, y);
    //         }
    //         else if (color == sf::Color::Red)
    //         {
    //             grid[x][y] = std::make_shared<Ground>(GroundType::Core, x, y);
    //         }
    //     }
    // }
}