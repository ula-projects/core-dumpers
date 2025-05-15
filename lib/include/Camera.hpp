#include <SFML/Graphics.hpp>
#include <cmath>

class Camera
{
private:
    sf::View camera;
    bool is_centered;

public:
    Camera();
    Camera(sf::Vector2f center);
    ~Camera();
    void setCenter(sf::Vector2f center, float delta_time);
    sf::Vector2f getCenter();
    void setRotation(float degrees);
    const sf::View &getCamera() const;
};
