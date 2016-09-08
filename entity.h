#include <SFML/Graphics.hpp>
#include <vector>

enum MovementMode{STILL = 0, CUSTOM, UPDOWN, LEFTRIGHT, SMART, STALKER};
//Smart: entity walks around the maze randomly
//Stalker: entity tries to get to the player with a path finding algorithm
//These 2 modes shall be implemented in the future


class Entity{
    private:
        sf::Sprite entity;

        sf::Vector2f velocity;

        MovementMode mode;

    public:
        Entity(sf::Texture&);
        Entity(sf::Texture&, sf::Vector2f, sf::Vector2f);
        ~Entity();

        void setMode(MovementMode);
        void resetTexture(sf::Texture&);
        sf::Sprite& getEntity();

        void randomizePosition();

        void update(std::vector<sf::RectangleShape>&);
        void update(float, std::vector<sf::RectangleShape>&);
};

