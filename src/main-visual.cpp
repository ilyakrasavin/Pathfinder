#include <SFML/Graphics.hpp>

using namespace std;

#include <iostream>
// Setup (window, loop etc)
// Application Loop (Event creation, update handling, display/render)
// Cleanup


// EVENT-Driven programming

int main()
{


    // Main Board Image
    sf::Texture board;
    board.loadFromFile("../assets-static/tiles.jpg");

    // Void Sprite Structure taking a texture
    sf::Sprite mySprite(board);

    // Scale the Structure
    mySprite.setScale(3.0f, 2.0f);

    // Main Rendering Window 
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

    // Shape Examples
    sf::CircleShape shape(100.f);
    sf::RectangleShape secondShape(sf::Vector2f(180,180));

    secondShape.setPosition(sf::Vector2f(780, 780));
    secondShape.setFillColor(sf::Color::Red);

    shape.setFillColor(sf::Color::Magenta);

    
    // Set up fonts
    sf::Font font;
    if (!font.loadFromFile("../assets-static/Raleway-Regular.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);
    text.setColor(sf::Color::Blue);
    text.setPosition(sf::Vector2f(20, 50));

    // Mouse Release Check
    bool mouseReleased = false;


    // Frame Rate Setup
    sf::Clock clock;
    window.setFramerateLimit(60);

    // Rendering Window Outer loop
    while (window.isOpen())
    {
        // Declare an event to be handled later
        sf::Event event;
        
        // Events put into a queue and processed one by ones
        
        while (window.pollEvent(event))
        {
            // Compute the frame rate:
            float secCurrent = clock.restart().asSeconds();
            float fps = 1.0f / secCurrent;

            cout<<"FPS: "<<fps<<endl;


            // Some event handling examples

            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed){
                shape.move(3, 6);
                secondShape.move(-3, -6);
            }

            if(event.type == sf::Event::KeyReleased){
                cout<<"Key was pressed"<<endl;
                if(event.key.code == sf::Keyboard::D){
                    cout<<"KEY D!"<<endl;
                }
            }

            mouseReleased = false;

            if(event.type == sf::Event::MouseButtonReleased){
                mouseReleased = true;
                cout<<"Mouse button released"<<endl;
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mouseReleased){
                cout<<"Left mouse button pressed!"<<endl;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){

                cout<<"Z pressed"<<endl;
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mouseReleased){
                cout<<"Left mouse button pressed!"<<endl;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){

                cout<<"KOK"<<endl;
            }


            // Rendering

            window.clear();
            window.draw(mySprite);
            window.draw(shape);
            window.draw(text);
            window.draw(secondShape);
            window.display();

        }

        // No Rendering / Display Updates for the actions done outside of Polling Loop
        // Main App updates HERE
    
    }

    return 0;
}
