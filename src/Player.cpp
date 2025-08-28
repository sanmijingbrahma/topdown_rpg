#include "Player.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <stdexcept>
#include <iostream>


Player::Player(const std::string& texturePath, sf::Vector2f& spawnPos){
    if(!texture.loadFromFile(texturePath)){
        throw std::runtime_error("Failed to load texture :"+ texturePath);
    };
    sprite.setTexture(texture);
    sprite.setPosition(spawnPos);
    sprite.setScale(2,2);

}


void Player::handleInput(float deltaTime){
    
    sf::Vector2f movement(0.f,0.f);
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -=1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y +=1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -=1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x +=1.f;

    //normalize

    if(movement != sf::Vector2f(0.f,0.f)){
        float length = std::sqrt(movement.x*movement.x + movement.y*movement.y);
        movement/=length;

        sf::Vector2f newPos = sprite.getPosition() + movement * speed * deltaTime;
        
        if (newPos.x < 0) newPos.x = 0;
        if (newPos.y < 0) newPos.y = 0;

        if(newPos.x > (800 - sprite.getGlobalBounds().width)){
            newPos.x = 800 - sprite.getGlobalBounds().width;
        }

        if(newPos.y > (600 - sprite.getGlobalBounds().height)){
            newPos.y = 600 - sprite.getGlobalBounds().height;
        }

        sprite.setPosition(newPos);
        std::cout<<"Player Position :"<<"("<<newPos.x<<","<<newPos.y<<")"<<std::endl;

    }

}


void Player::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

