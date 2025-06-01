#include "Settings.hpp"
#include "Ground.hpp"

class Picaxe
{
private:
public:
    Picaxe();
    ~Picaxe();

    void update(sf::RenderWindow &window, vector<shared_ptr<Ground>> ground_list);
};
