
using namespace std;

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <vector>

#include <memory>


// Base Interface for all components
class IComponent{

    public:

        // WHY NOT pure virtual
        virtual void render(sf::RenderWindow& ref){};
        virtual void SetPosition(float x, float y){};

        // Releases Base Resources
        virtual ~IComponent(){};

};


class Sprite2DComponent : public IComponent{

    public:

        Sprite2DComponent(std::string filepath){
            m_texture.loadFromFile(filepath);
            m_sprite.setTexture(m_texture);
        }

        void SetPosition(float x, float y){
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


// Entitites such as Start / End Markers, Current / Searching Algo Positions 
class GameEntity{
    public:
        GameEntity(string name){
            n_name = name;
        }

        ~GameEntity(){}

        float getXPos() const{return m_x;}
        float getYPos() const{return m_y;}

        void addComponent(string filename){
            
            shared_ptr<Sprite2DComponent> comp = make_shared<Sprite2DComponent>(filename);
            m_components.push_back(comp);
        }

        // Render all drawable components
        void RenderComponents(sf::RenderWindow& ref){

            for(int i = 0; i < m_components.size(); i++){
                m_components[i]->render(ref);
            }

        }

        // Why setting positions for all entities?
        void SetPosition(float x, float y){

            for(int i = 0; i < m_components.size(); i++){

                m_components[i]->SetPosition(x, y);

            }

        }


    private:

        float m_x, m_y; // Game Entity positions
        string n_name; // Entity Name
        vector< shared_ptr<IComponent> > m_components; // Embedded Components

};


class Board{

};



int main()
{
    // Main Rendering Window 
    sf::RenderWindow window(sf::VideoMode(1200, 1200), "Main Window!");
    window.setFramerateLimit(60);


    Sprite2DComponent board("../assets-static/tiles.jpg");

    sf::RectangleShape cell(sf::Vector2f(60,60));
    cell.setPosition(sf::Vector2f(0, 0));
    cell.setFillColor(sf::Color::Black);
    cell.move(60, 60);

 
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


    vector<GameEntity> entities;

    for(int i = 0; i < 50; i++){
        GameEntity test("ghost" + to_string(i));
        test.addComponent("../assets-static/ghost.jpg");
        test.SetPosition(400 + i, 700 + i);
        entities.push_back(test);
    }


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
                cout<<sf::Mouse::getPosition().x<<endl;
                cout<<sf::Mouse::getPosition().y<<endl;
            }

            
            // Rendering
            window.clear();
            board.render(window);

            // Draw all sprites
            for(int i = 0; i < entities.size(); i++){
                entities[i].RenderComponents(window);
            }

            window.draw(text);
            window.draw(cell);
            window.display();

        }

        // No Rendering / Display Updates for the actions done outside of Polling Loop
        // Main App updates HERE
        // Algortihm Updates / Checks etc...

    }

    return EXIT_SUCCESS;
}
