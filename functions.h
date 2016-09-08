#include <SFML/Graphics.hpp>
#include <vector>

bool collision(const sf::Shape&, const sf::Shape&);

bool collision(const sf::Shape&, const sf::Sprite&);

bool collision(const sf::Sprite&, const sf::Shape&);


bool collision(const sf::Shape&, std::vector<sf::RectangleShape>&);

bool collision(const sf::Sprite&, std::vector<sf::RectangleShape>&);


void giveRandomPosition(sf::Sprite&);

void giveRandomPosition(sf::Vector2f&);
