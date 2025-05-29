#include <SFML/Graphics.hpp>
#include <Game.hpp>

int main()
{
    // SFML Window
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Core Dumpers!", sf::Style::Close);
    window.setFramerateLimit(60);

    // Game
    Game game;

    // Clock
    sf::Clock clock;
    float delta_time = 0.0f;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Update
        delta_time = clock.restart().asSeconds();
        game.update(delta_time, window);

        // Update Graphics
        window.clear();
        game.draw(window);
        window.display();
    }
}

// #include <SFML/Graphics.hpp>
// #include <box2d/box2d.h>
// #include <vector>

// constexpr float SCALE = 16.f; // 30 píxeles por metro (convención para dibujar)

// struct Entity
// {
//     b2Body *body;
//     b2Vec2 gravity;
//     sf::RectangleShape shape;
// };

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode({1280, 720}), "Core Dumpers");
//     window.setFramerateLimit(60);

//     // Mundo con gravedad
//     // b2Vec2 gravity(10.f, 10.f); // Gravedad hacia abajo
//     // b2World world(gravity);

//     // // // --- Crear suelo (estático) ---
//     // b2BodyDef groundBodyDef;
//     // groundBodyDef.type = b2_staticBody;
//     // groundBodyDef.position.Set(400.f / SCALE, 200.f / SCALE); // posición en metros
//     // b2Body *groundBody = world.CreateBody(&groundBodyDef);

//     // b2PolygonShape groundBox;
//     // groundBox.SetAsBox(25.f / SCALE, 25.f / SCALE); // mitad del ancho y alto

//     // groundBody->CreateFixture(&groundBox, 0.f); // densidad 0 → cuerpo estático

//     // sf::RectangleShape groundRect(sf::Vector2f(50.f, 50.f));
//     // groundRect.setOrigin({25.f, 25.f});
//     // groundRect.setPosition({400.f, 200.f});
//     // groundRect.setFillColor(sf::Color::Green);

//     // // // --- Crear caja dinámica ---
//     // b2BodyDef boxBodyDef;
//     // boxBodyDef.type = b2_dynamicBody;
//     // boxBodyDef.position.Set(200.f / SCALE, 0.f / SCALE); // posición inicial
//     // b2Body *boxBody = world.CreateBody(&boxBodyDef);

//     // b2PolygonShape boxShape;
//     // boxShape.SetAsBox(25.f / SCALE, 25.f / SCALE); // mitad del tamaño

//     // b2FixtureDef boxFixtureDef;
//     // boxFixtureDef.shape = &boxShape;
//     // boxFixtureDef.density = 1.f;
//     // boxFixtureDef.friction = 0.3f;
//     // boxBody->CreateFixture(&boxFixtureDef);

//     // sf::RectangleShape boxRect(sf::Vector2f(50.f, 50.f));
//     // boxRect.setOrigin({25.f, 25.f});
//     // boxRect.setFillColor(sf::Color::Red);

//     // // --- Bucle principal ---
//     // while (window.isOpen())
//     // {
//     //     while (const std::optional event = window.pollEvent())
//     //     {
//     //         if (event->is<sf::Event::Closed>())
//     //             window.close();
//     //     }

//     //     // Simular física
//     //     world.Step(1.f / 60.f, 8, 3);

//     //     // Obtener posición de la caja desde Box2D
//     //     b2Vec2 pos = boxBody->GetPosition();
//     //     float angle = boxBody->GetAngle();

//     //     boxRect.setPosition({pos.x * SCALE, pos.y * SCALE});
//     //     sf::Angle rotation_angle = sf::degrees(angle * 180 / b2_pi);
//     //     boxRect.setRotation(rotation_angle);

//     //     // Dibujar
//     //     window.clear(sf::Color::Black);
//     //     window.draw(groundRect);
//     //     window.draw(boxRect);
//     //     window.display();
//     // }
//     b2World world(b2Vec2(0.0f, 0.0f));

//     std::vector<Entity> entities;

//     for (int i = 0; i < 2; ++i)
//     {
//         // Crear cuerpo dinámico
//         b2BodyDef bodyDef;
//         bodyDef.type = b2_dynamicBody;
//         bodyDef.position.Set((i * 5.0f + 5.0f), 5.0f); // en metros
//         b2Body *body = world.CreateBody(&bodyDef);

//         // Forma
//         b2PolygonShape shape;
//         shape.SetAsBox(1.0f, 1.0f); // 2x2 metros

//         b2FixtureDef fixtureDef;
//         fixtureDef.shape = &shape;
//         fixtureDef.density = 1.0f;
//         fixtureDef.friction = 0.3f;
//         body->CreateFixture(&fixtureDef);

//         // Gravedad individual
//         b2Vec2 g = (i == 0) ? b2Vec2(0.0f, 9.8f) : b2Vec2(-9.8f, 0.0f);

//         // Representación gráfica
//         sf::RectangleShape rect(sf::Vector2f(2.0f * SCALE, 2.0f * SCALE));
//         rect.setOrigin(rect.getSize() / 2.0f);
//         rect.setFillColor((i == 0) ? sf::Color::Green : sf::Color::Red);

//         entities.push_back({body, g, rect});
//     }

//     // Bucle principal
//     while (window.isOpen())
//     {
//         while (const std::optional event = window.pollEvent())
//         {
//             if (event->is<sf::Event::Closed>())
//                 window.close();
//         }

//         // Aplicar gravedad personalizada
//         for (auto &e : entities)
//         {
//             b2Vec2 force = e.body->GetMass() * e.gravity;
//             e.body->ApplyForceToCenter(force, true);
//         }

//         // Simular física
//         world.Step(1.0f / 60.0f, 6, 2);

//         // Dibujar
//         window.clear(sf::Color::Black);
//         for (auto &e : entities)
//         {
//             b2Vec2 pos = e.body->GetPosition();
//             sf::Angle rotation_angle = sf::degrees(e.body->GetAngle() * 180 / b2_pi);
//             e.shape.setPosition({pos.x * SCALE, pos.y * SCALE});
//             e.shape.setRotation(rotation_angle);
//             window.draw(e.shape);
//         }
//         window.display();
//     }

//     return 0;
// }
