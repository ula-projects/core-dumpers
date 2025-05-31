#include "Settings.hpp"

class Menu
{
private:
    sf::Font font;
    sf::Text game_title;
    sf::Text game_start;

public:
    Menu();
    ~Menu();
    void mainMenuDraw(sf::RenderWindow &window);
    void mainMenuUpdate(sf::RenderWindow &window, GameState &game_state);
    void settingsMenu(sf::RenderWindow window);
};
