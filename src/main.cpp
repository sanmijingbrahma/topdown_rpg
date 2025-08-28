#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <ctime>
#include "Player.hpp"

int main(){

    sf::RenderWindow window(sf::VideoMode(800,600),"Top Down RPG");
    sf::Vector2f swanPos(400,300);
    Player player("assets/player.png",swanPos);

    sf::Clock clock;


    // Game Loop
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        float deltaTime = clock.restart().asSeconds();

        player.handleInput(deltaTime);


        window.clear();
        player.draw(window);
        window.display();
    }

    return 0;

}
