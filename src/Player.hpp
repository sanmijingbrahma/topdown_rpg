#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Player{
    public:
        Player(const std::string& texturePath,sf::Vector2f& spawnPos);
        void handleInput(float deltaTime);
        void collisionDetect(sf::FloatRect something);
        void draw(sf::RenderWindow& window);

    private:
        sf::Texture texture;
        sf::Sprite sprite;
        float speed = 200.f;
};
