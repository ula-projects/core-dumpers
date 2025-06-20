#include "Settings.hpp"
#include "PolarCoordinates.hpp"
class Camera
{
private:
    sf::View camera;
    bool is_centered;

public:
    Camera();
    Camera(sf::Vector2f center);
    ~Camera();

    void update(sf::Vector2f center, float delta_time, PolarCoordinates coordinates);
    void setCenter(sf::Vector2f center);
    sf::Vector2f getCenter();
    const sf::View &getCamera() const;
};
