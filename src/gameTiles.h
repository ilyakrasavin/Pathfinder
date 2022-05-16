#ifndef GAMETILE_H
#define GAMETILE_H

#include <SFML/Graphics.hpp>

class GameTile{

    public:

        bool isFree;
        bool isExit;

        sf::Vector2f pos;
        sf::Texture texture;
        sf::Sprite sprite;

        GameTile(std::string, float, float, bool, bool);

        bool setUpSprite(std::string);

};


#endif