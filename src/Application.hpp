#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>

#include "Interface.hpp"
#include "Graph.hpp"
#include "GraphWeighted.hpp"

#include "Algorithms/A-Star.hpp"
#include "Algorithms/BFS.hpp"
#include "Algorithms/DFS.hpp"

#include <memory>

using std::cout, std::endl, std::string;


struct AppState{

    bool isStartSet = false;
    bool isFinishSet = false;

    bool isAlgoChosen = false;
    bool isStartPressed = false;
    bool isRandomMap = false;
    bool isResetPressed = false;  

    int startIdx = 0;

    bool breadthFirstSearch = false;
    bool depthFirstSearch = false;
    bool aStar = false;
    bool djkstra = false;

    bool astarMode = false;
    int astarModeSetting = 0;

};


struct AlgorithmFactory{

    void runBFS();
    void runDFS();
    void runAStar();

};


void AlgorithmFactory::runBFS(){

}

void AlgorithmFactory::runDFS(){

}

void AlgorithmFactory::runAStar(){

}

class Application{

    public:

        Application(const string name);

        shared_ptr<sf::RenderWindow> getMainWindowRef();
        void mainWindow(const int height, const int width);
        void mainFrameRate(const int limit);

        const void renderInterface();
        const void displayInterface();

        void resetState();

        AppState* getStateRef(){return &this->state;}

        const vector<shared_ptr<mapCell>>* getboardRef(){return &boardCells;}

        ~Application();

    private:

        // Main Program Window
        shared_ptr<sf::RenderWindow> mainWindowRef;

        // Active Window Components
        vector<shared_ptr<mapCell>> boardCells;
        vector<shared_ptr<Button>> bufferButtons;
        void AddButton(const sf::Color colour, const sf::Font font, const string Text, const pair<int, int> pos);

        // Static Window buffers
        sf::RectangleShape upperBuffer;
        sf::RectangleShape bottomBuffer;

        // Graph DS for algorithm use
        Graph* graph;
        GraphWeighted* graphWeighted;

        AlgorithmFactory algoritms;

        // Program State Elements
        string appName;
        AppState state;

};


Application::Application(const string name){

    cout<<"Created an app!"<<endl;

    appName = name;

    state.startIdx = 0;
    state.isStartSet = false;
    state.isFinishSet = false;

    state.isStartPressed = false;
    state.isResetPressed = false;
    state.isAlgoChosen = false;
    
    state.breadthFirstSearch = false;
    state.depthFirstSearch = false;
    state.aStar = false;
    state.djkstra = false;

    state.astarMode = false;
    state.astarModeSetting = 0;

    mainWindow(1600, 1600);
    mainFrameRate(60);

    // Set up fonts
    sf::Font font;
    font.loadFromFile("../assets-static/Raleway-Regular.ttf");

    // AddButton(sf::Color::Yellow, font, "DFS", make_pair<int, int>(200,12));
    // AddButton(sf::Color::Yellow, font, "A*", make_pair<int, int>(330,12));
    // AddButton(sf::Color::Yellow, font, "Djkstra", make_pair<int, int>(420,12));
    // AddButton(sf::Color::Yellow, font, "Start", make_pair<int, int>(80,1490));
    // AddButton(sf::Color::Yellow, font, "Reset", make_pair<int, int>(220,1490));
    // AddButton(sf::Color::Yellow, font, "Random Map", make_pair<int, int>(1300,12));

    // AddButton(sf::Color::Yellow, font, "Hold 'W' to set the Walls (Or press Random)\nHold 'S' to set the Start\nHold 'F' to set the Target\nPress Esc to exit at any time", make_pair<int, int>(920, 1448));


    upperBuffer = sf::RectangleShape(sf::Vector2f(1600, 80));
    upperBuffer.setPosition(0, 0);
    upperBuffer.setFillColor(sf::Color(65,105,225));

    bottomBuffer = sf::RectangleShape(sf::Vector2f(1600, 160));
    bottomBuffer.setPosition(0, 1440);
    bottomBuffer.setFillColor(sf::Color(65,105,225));


    
    // Initialize the board of cells
    cout<<"Initializing cells"<<endl;

    for(int i = 80; i < mainWindowRef->getSize().y - 160;){

        for(int k = 0; k < mainWindowRef->getSize().x;){

            cout<<"Initialized cell: "<<i<<k<<endl;

            shared_ptr<mapCell> test = make_shared<mapCell>("../assets-static/node-empty.jpg", false, false, false, false);
            test->SetPosition(k, i);

            boardCells.push_back(test);

            k+=80;
        }

        i+=80;
    }


    graph = nullptr;
    graphWeighted = nullptr;



}

void Application::mainWindow(const int height, const int width){

    mainWindowRef = make_shared<sf::RenderWindow>(sf::VideoMode(1600, 1600), this->appName);

}

void Application::mainFrameRate(const int limit){
    mainWindowRef->setFramerateLimit(limit);
}

shared_ptr<sf::RenderWindow> Application::getMainWindowRef(){
    return mainWindowRef;
}


void Application::AddButton(const sf::Color colour, const sf::Font font, const string text, const pair<int, int> pos){
    shared_ptr<Button> newButton = make_shared<Button>(colour, font, text, pos);
    bufferButtons.push_back(newButton);
}


const void Application::renderInterface(){

    cout<<"Rendering started"<<endl;

    mainWindowRef->clear();
    cout<<"Window cleaned"<<endl;

    // Draw the cells
    for(auto each: boardCells){
        each->render(mainWindowRef);
    }

    cout<<"Cells drawn"<<endl;

    // Draw the buffers
    mainWindowRef->draw(upperBuffer);
    mainWindowRef->draw(bottomBuffer);

    cout<<"Window Buffers drawn"<<endl;

    for(auto buttons: bufferButtons){
        cout<<"Rendering Buttons"<<endl;
        // buttons->render(this->getMainWindowRef());
        // cout<<buttons->getButton().getString()<<endl;

    }

    cout<<"Buttons drawn"<<endl;

    cout<<"Rendering done"<<endl;

}


const void Application::displayInterface(){
    mainWindowRef->display();
}


void Application::resetState(){

    state.startIdx = 0;
    state.isStartSet = false;
    state.isFinishSet = false;

    state.isStartPressed = false;
    state.isResetPressed = false;
    state.isAlgoChosen = false;
    
    state.breadthFirstSearch = false;
    state.depthFirstSearch = false;
    state.aStar = false;
    state.djkstra = false;

    state.astarMode = false;
    state.astarModeSetting = 0;

}


Application::~Application(){}

#endif