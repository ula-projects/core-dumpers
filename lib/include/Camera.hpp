#include <SFML/Graphics.hpp>

class Camera
{
private:
    sf::View camera;

public:
    Camera();
    ~Camera();
    void setCenter(sf::Vector2f center, float delta_time);
    void setRotation(float degrees);
    const sf::View &getCamera() const;
};
