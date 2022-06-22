#ifndef TEXT_CPP
#define TEXT_CPP

#include <SFML/Graphics.hpp>

// Inline keyword assures the single memory address for variables defined in a Header file
// This solves the Multiple Definition Error while including HPP into multiple CPP files

inline sf::Font font;
inline sf::Text textBFS("BFS", font, 45);
inline sf::Text textDFS("DFS", font, 45);
inline sf::Text textAStar("A*", font, 45);
inline sf::Text textDjkstra("Djkstra", font, 45);
inline sf::Text textEuc("Euclidian", font, 45);
inline sf::Text textManh("Manhattan", font, 45);
inline sf::Text textCheb("Chebushev", font, 45);
inline sf::Text textStart("Start", font, 45);
inline sf::Text textReset("Reset", font, 45);
inline sf::Text textRandom("Random Map", font, 45);
inline sf::Text textInfo("Hold 'W' to set the Walls (Or press Random)\nHold 'S' to set the Start\nHold 'F' to set the Target\nPress Esc to exit at any time", font, 30);


inline void initializeButtons(){
    
    font.loadFromFile("../assets-static/Raleway-Regular.ttf");
    
    textBFS.setColor(sf::Color::Yellow);
    textBFS.setPosition(80, 12);

    textDFS.setColor(sf::Color::Yellow);
    textDFS.setPosition(200,12);

    textAStar.setColor(sf::Color::Yellow);
    textAStar.setPosition(330,12);

    textDjkstra.setColor(sf::Color::Yellow);
    textDjkstra.setPosition(420,12);

    textEuc.setColor(sf::Color::Yellow);
    textEuc.setPosition(460,12);

    textManh.setColor(sf::Color::Yellow);
    textManh.setPosition(700,12);

    textCheb.setColor(sf::Color::Yellow);
    textCheb.setPosition(970,12);
        
    textStart.setColor(sf::Color::Yellow);
    textStart.setPosition(80,1490);

    textReset.setColor(sf::Color::Yellow);
    textReset.setPosition(220,1490);

    textRandom.setColor(sf::Color::Yellow);
    textRandom.setPosition(1300,12);

    textInfo.setColor(sf::Color::Yellow);
    textInfo.setPosition(920, 1448);

}

#endif