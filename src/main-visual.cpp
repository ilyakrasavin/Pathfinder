
using namespace std;

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include <vector>
#include <unordered_map>

#include <memory>


// Base Interface for all components
class IComponent{

    public:

        // WHY NOT pure virtual?
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

            m_sprite.setScale(0.2, 0.2);

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

        void addComponent(string filename, float x, float y){
            shared_ptr<Sprite2DComponent> comp = make_shared<Sprite2DComponent>(filename);
            comp->SetPosition(x, y);
            m_components.push_back(comp);
        }

        // Render all drawable components
        void RenderComponents(sf::RenderWindow& ref){

            for(int i = 0; i < m_components.size(); i++){
                m_components[i]->render(ref);
            }

        }

        // Why setting positions for all entities????
        // void SetPosition(float x, float y){

        //     for(int i = 0; i < m_components.size(); i++){

        //         m_components[i]->SetPosition(x, y);
        //     }
        // }


    private:

        float m_x, m_y; // Game Entity positions
        string n_name; // Entity Name
        vector< shared_ptr<IComponent> > m_components; // Embedded Components

};


class Board{

};


struct hash_pair {
    
    size_t operator()(const pair<int, int>& p) const
    {
        auto hash1 = hash<int>{}(p.first);
        auto hash2 = hash<int>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;             
        }
         
        // If hash1 == hash2, their XOR is zero.
          return hash1;
    }
};


int main()
{
    // Main Rendering Window 
    sf::RenderWindow window(sf::VideoMode(2500, 2500), "Main Window!");
    window.setFramerateLimit(60);


    sf::RectangleShape cell(sf::Vector2f(60,60));
    cell.setPosition(sf::Vector2f(0, 0));
    cell.setFillColor(sf::Color::Black);
    cell.move(60, 60);

 


    // Mouse Release Check
    bool mouseReleased = false;


    // Frame Rate Setup
    sf::Clock clock;


    // Generate the Board:

    vector<shared_ptr<Sprite2DComponent>> boardCells;
    vector<shared_ptr<Sprite2DComponent>> wallCells;

    for(int i = 0; i < window.getSize().y;){

        for(int k = 0; k < window.getSize().x;){

            shared_ptr<Sprite2DComponent> test= make_shared<Sprite2DComponent>("../assets-static/cell.jpg");
            test->SetPosition(k, i);

            boardCells.push_back(test);

            k+=50;
        }

        i+=50;
    }





    // Set up fonts
    sf::Font font;
    if (!font.loadFromFile("../assets-static/Raleway-Regular.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);
    text.setColor(sf::Color::Blue);
    text.setPosition(sf::Vector2f(20, 50));


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

            // Colour the texture
            if(event.type == sf::Event::MouseButtonPressed){
                // Gets Positions in window coordinates
                int xPos = sf::Mouse::getPosition(window).x;
                int yPos = sf::Mouse::getPosition(window).y;
                cout<<xPos<<endl;
                cout<<yPos<<endl;

                // Calculate the Cell index & replace
                int cellIdx = (yPos/50) * 50 + xPos / 50;
                cout<<"Cell IDX is "<<cellIdx<<endl;

                boardCells[cellIdx] = make_shared<Sprite2DComponent>("../assets-static/cell-red.jpg");
                boardCells[cellIdx]->SetPosition(xPos - xPos%50, yPos - yPos%50);
                cout<<"Position set at "<<xPos - xPos%50<<" And :"<<yPos - yPos%50<<endl;
            }

            
            // Rendering
            window.clear();
            // board.render(window);

            // Draw all sprites
            for(int i = 0; i < boardCells.size(); i++){
                boardCells[i]->render(window);
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
