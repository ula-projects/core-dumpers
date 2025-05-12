#include <Camera.hpp>
#include <iostream>
Camera::Camera()
{
    camera.setSize({640, 640});
    camera.setCenter({320, 320});
}

Camera::~Camera()
{
}

void Camera::setCenter(sf::Vector2f center, float delta_time)
{
    // const float safe_area = 100;
    sf::Vector2f view_center = camera.getCenter();
    sf::FloatRect safe_zone({view_center.x - 100, view_center.y - 100}, {200, 200});

    if (!safe_zone.contains(center))
    {
        sf::Vector2f offset = center - view_center;
        camera.setCenter(view_center + offset * 5.0f * delta_time);

        // std::cout << delta_time << std::endl;
    }
    // if (center.x < (camera.getCenter().x - safe_area))
    // {
    //     camera.setCenter({center.x - safe_area, center.y});
    // }
    // if (center.x > (camera.getCenter().x + safe_area))
    // {
    //     camera.setCenter({center.x + safe_area, center.y});
    // }
}

void Camera::setRotation(float degrees)
{
}

const sf::View &Camera::getCamera() const
{
    return camera;
}