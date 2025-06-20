#include "Camera.hpp"

Camera::Camera()
{
    camera.setSize({320, 180});
    camera.setCenter({0, 0});
    is_centered = true;
}

Camera::~Camera()
{
}

void Camera::update(sf::Vector2f center, float delta_time, PolarCoordinates coordinates)
{
    camera.setRotation(-sf::Angle(sf::degrees(coordinates.deg_angle - 90)));
    sf::Vector2f camera_center = camera.getCenter();
    sf::Vector2f offset = center - camera_center;

    float safe_zone_half_x = 40.0f;
    float safe_zone_half_y = 25.0f;

    sf::FloatRect safe_zone({camera_center.x - safe_zone_half_x, camera_center.y - safe_zone_half_y}, {safe_zone_half_x * 2, safe_zone_half_y * 2});

    if (!is_centered && std::abs(offset.x) <= 1 && std::abs(offset.y) <= 1)
    {
        is_centered = true;
    }

    if (std::abs(offset.x) > safe_zone_half_x || std::abs(offset.y) > safe_zone_half_y)
    {
        is_centered = false;
    }

    if (!is_centered)
    {
        sf::Vector2f movement({0.0f, 0.0f});

        if (offset.x < -1)
        {
            movement.x = -1;
        }
        if (offset.x > 1)
        {
            movement.x = 1;
        }
        if (offset.y < -1)
        {
            movement.y = -1;
        }
        if (offset.y > 1)
        {
            movement.y = 1;
        }

        // Ajustamos la magnitud del vector
        if (movement.x != 0.0f || movement.y != 0.0f)
        {
            float magnitude = std::sqrt(std::pow(movement.x, 2) + std::pow(movement.y, 2));
            movement /= magnitude;
        }

        // Aumentamos la velocidad si se esta mas lejos del centro
        if (std::abs(offset.x) > safe_zone_half_x * 2 || std::abs(offset.y) > safe_zone_half_y * 2)
        {
            camera.move(movement * 80.0f * delta_time);
        }
        else if (std::abs(offset.x) > safe_zone_half_x / 5 || std::abs(offset.y) > safe_zone_half_y / 5)
        {
            camera.move(movement * 25.0f * delta_time);
        }
        else
        {
            camera.move(movement * 5.0f * delta_time);
        }
    }
};

const sf::View &Camera::getCamera() const
{
    return camera;
}

void Camera::setCenter(sf::Vector2f center)
{
    camera.setCenter(center);
}

sf::Vector2f Camera::getCenter()
{
    return camera.getCenter();
}