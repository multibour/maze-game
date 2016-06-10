#include <SFML/Graphics.hpp>
#include <vector>

class Entity{
    private:
        sf::Sprite entity;

        sf::Vector2f velocity;
        sf::Vector2f acceleration;

    public:
        Entity(const sf::Texture&, sf::Vector2f, sf::Vector2f, sf::Vector2f)
        ~Entity();

        void update(std::vector<sf::RectangleShape>);
        void update(std::vector<sf::FloatRect>);
};

