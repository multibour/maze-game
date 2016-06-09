#include <SFML/Graphics.hpp>
#include <vector>

bool collision(const sf::Shape&, const sf::Shape&);

bool collision(const sf::Shape&, const sf::Sprite&);

bool collision(const sf::Shape&, sf::FloatRect);

bool collision(const sf::Shape&, std::vector<sf::RectangleShape>&);



