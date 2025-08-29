#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <ctime>
#include "Player.hpp"


const int TILE_SIZE = 32;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;


enum Tiletype{
    WALKABLE = 0,
    WALL= 1,
    WATER= 2,
};

struct Tile{
    Tiletype type;
    bool isWalkable;
};

int main(){

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Top Down RPG");
    sf::Vector2f swanPos(400,300);
    Player player("assets/player.png",swanPos);

    sf::Clock clock;

    Tile wall = {WALL,false};
    Tile ground= {WALKABLE,true};
    Tile water= {WATER,false};


    // map
    std::vector<std::vector<Tile>> map = {
        {wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall},
        {wall,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,water,water,water,water,water,water,water,water,water,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,water,water,water,water,water,water,water,water,water,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,water,water,water,water,water,water,water,water,water,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,water,water,water,water,water,water,water,water,water,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,water,water,water,water,water,water,water,water,water,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,water,water,water,water,water,water,water,water,water,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,ground,wall},
        {wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall},
    };


    sf::Texture groundTexture;
    if(!groundTexture.loadFromFile("assets/ground.png")){
        throw std::runtime_error("Failed to load groundTexture");
    }

    sf::Texture wallTexture;
    if(!wallTexture.loadFromFile("assets/wall.png")){
        throw std::runtime_error("Failed to load wallTexture");
    }
    sf::Sprite wallSprite;
    wallSprite.setTexture(wallTexture);

    sf::Texture waterTexture;
    if(!waterTexture.loadFromFile("assets/water.png")){
        throw std::runtime_error("Failed to load waterTexture");
    }


    sf::FloatRect wallBound = wallSprite.getGlobalBounds();

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

        for (int y = 0; y < map.size(); y++) {
            for (int x = 0; x < map[y].size(); x++) {
                sf::Sprite tile;
                switch (map[y][x].type) {
                    case WALKABLE:{
                        tile.setTexture(groundTexture);
                        break;
                    } 
                    case WALL:{
                        tile.setTexture(wallTexture);
                        player.collisionDetect(wallBound);
                        break;

                    };                     
                    case WATER:{
                        tile.setTexture(waterTexture); 
                        break;

                    } 
                }
                tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                window.draw(tile);
                
                if(map[y][x].type == WALL){
                    player.collisionDetect(tile.getGlobalBounds());
                }
            }
        }

        player.draw(window);
        window.display();
    }

    return 0;

}
