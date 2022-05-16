
using namespace std;

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include <vector>
#include <memory>


// Base Interface for all components
class IComponent{

    public:

        // Pure Virtual: Need to be implemented in Inheriting classes
        virtual void render(sf::RenderWindow& ref) = 0;
        virtual void SetPosition(float x, float y) = 0;

        // Releases Base Resources
        virtual ~IComponent(){};
};


class Sprite2DComponent : public IComponent{

    public:

        Sprite2DComponent(){}

        Sprite2DComponent(std::string filepath){
            m_texture.loadFromFile(filepath);
            m_sprite.setTexture(m_texture);

            m_sprite.setScale(0.2, 0.2);
        }

        virtual void SetPosition(float x, float y) override{
            m_sprite.setPosition(x, y);
        }

        void render(sf::RenderWindow& ref) override{
            ref.draw(m_sprite);
        }


        // Releases Derived Class Resources
        ~Sprite2DComponent(){}
        // i.e. 
        // IComponent* b = new Sprite2DComponent
        // delete b - makes virtual f. call to ~IComponent()
        // Since it's virtual -> Calls ~Sprite2DComponent() -> ~IComponent()

    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;

};


class mapCell : public Sprite2DComponent{

    public:

        mapCell(string filepath, bool isTgt, bool isWall, bool isStart, bool isExplored){

            m_texture.loadFromFile(filepath);
            m_sprite.setTexture(m_texture);

            m_sprite.setScale(0.2, 0.2);

            isTarget = isTgt;
            isWall = isWall;
            isStart = isStart;
            isExplored = isExplored;

        }

        void SetPosition(float x, float y) override{
            m_sprite.setPosition(x, y);
        }

        void render(sf::RenderWindow& ref) override{
            ref.draw(m_sprite);
        }

        void setTexture(string filepath){
            m_texture.loadFromFile(filepath);
            m_sprite.setTexture(m_texture);
            m_sprite.setScale(0.2, 0.2);
        }

        ~mapCell(){}


    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        bool isTarget;
        bool isWall;
        bool isStart;
        bool isExplored;

};



int main()
{
    // Main Rendering Window 
    sf::RenderWindow window(sf::VideoMode(2025, 2025), "Main Window!");
    window.setFramerateLimit(60);

    // sf::RectangleShape cell(sf::Vector2f(60,60));
    // cell.setPosition(sf::Vector2f(0, 0));
    // cell.setFillColor(sf::Color::Black);
    // cell.move(60, 60);

 
    // Mouse Release Check
    bool mouseReleased = false;


    // Frame Rate Setup
    sf::Clock clock;


    // Generate the Board:

    vector<shared_ptr<mapCell>> boardCells;

    for(int i = 0; i < window.getSize().y;){

        for(int k = 0; k < window.getSize().x;){

            shared_ptr<mapCell> test= make_shared<mapCell>("../assets-static/cell.jpg", false, false, false, false);
            test->SetPosition(k, i);

            boardCells.push_back(test);

            k+=45;
        }

        i+=45;
    }


    // Set up fonts
    sf::Font font;
    if (!font.loadFromFile("../assets-static/Raleway-Regular.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);
    text.setColor(sf::Color::Blue);
    text.setPosition(sf::Vector2f(20, 50));


    bool isStartSet = false;
    bool isFinishSet = false; // Run the algorithm on true

    bool depthFirstSearch = false;
    bool breadthFirstSearch = false;


    // Rendering Window Outer loop
    while (window.isOpen())
    {
        // Declare an event to be handled later
        // Events put into a queue and processed one by ones
        sf::Event event;
        

        while (window.pollEvent(event))
        {
            // Compute the frame rate:
            float secCurrent = clock.restart().asSeconds();
            float fps = 1.0f / secCurrent;

            cout<<"FPS: "<<fps<<endl;

            // Some event handling examples
            if (event.type == sf::Event::Closed)
                window.close();


            // Set the Walls
            if(event.type == sf::Event::MouseButtonPressed){
                // Gets Positions in window coordinates
                int xPos = sf::Mouse::getPosition(window).x;
                int yPos = sf::Mouse::getPosition(window).y;
                cout<<xPos<<endl;
                cout<<yPos<<endl;

                // Calculate the Cell index & replace
                int cellIdx = (yPos/45) * 45 + xPos / 45;
                cout<<"Cell IDX is "<<cellIdx<<endl;

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
                    boardCells[cellIdx] = make_shared<mapCell>("../assets-static/cell-red.jpg", false, true, false, false);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)){
                    boardCells[cellIdx] = make_shared<mapCell>("../assets-static/cell-finish.jpg", true, false, false, false);
                    isFinishSet = true;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
                    boardCells[cellIdx] = make_shared<mapCell>("../assets-static/cell-start.jpg", true, false, false, false);
                    isStartSet = true;
                }
                else{
                    continue;
                }


                boardCells[cellIdx]->SetPosition(xPos - xPos%45, yPos - yPos%45);
                cout<<"Position set at "<<xPos - xPos%45<<" And :"<<yPos - yPos%45<<endl;

            }


            // Rendering
            window.clear();

            // Draw Board Cells
            for(int i = 0; i < boardCells.size(); i++){
                boardCells[i]->render(window);
            }

            window.draw(text);
            window.display();

            if(isFinishSet){
                return EXIT_SUCCESS;
            }

        }

        // No Rendering / Display Updates for the actions done outside of Polling Loop
        // Main App updates HERE
        // Algortihm Updates / Checks etc...

    }

    return EXIT_SUCCESS;
}
