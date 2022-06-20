#include <SFML/Graphics.hpp>


sf::Font font;
sf::Text text1("BFS", font, 45);
sf::Text text2("DFS", font, 45);
sf::Text text3("A*", font, 45);
sf::Text text4("Djkstra", font, 45);
sf::Text textEuc("Euclidian", font, 45);
sf::Text textManh("Manhattan", font, 45);
sf::Text textCheb("Chebushev", font, 45);
sf::Text textStart("Start", font, 45);
sf::Text textReset("Reset", font, 45);
sf::Text textRandom("Random Map", font, 45);
sf::Text textInfo("Hold 'W' to set the Walls (Or press Random)\nHold 'S' to set the Start\nHold 'F' to set the Target\nPress Esc to exit at any time", font, 30);

void initializeButtons(){
    
    font.loadFromFile("../assets-static/Raleway-Regular.ttf");

    text1.setColor(sf::Color::Yellow);
    text1.setPosition(80, 12);

    text2.setColor(sf::Color::Yellow);
    text2.setPosition(200,12);

    text3.setColor(sf::Color::Yellow);
    text3.setPosition(330,12);

    text4.setColor(sf::Color::Yellow);
    text4.setPosition(420,12);

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