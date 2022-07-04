#include "Application.hpp"

#include "textButtons.hpp"


#include "Algorithms/A-Star.hpp"
#include "Algorithms/BFS.hpp"
#include "Algorithms/DFS.hpp"
#include "Algorithms/Djkstra.hpp"

Application::Application(const string name){

    cout<<"Application Created"<<endl;

    //////////////////////////////////
    // State Setup
    appName = name;

    state.startIdx = int();
    state.tgtIdx = int();
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
    //////////////////////////////////

    //////////////////////////////////
    // Window Setup

    mainWindow(1600, 1600);
    mainFrameRate(60);

    // Static Window buffers
    upperBuffer = sf::RectangleShape(sf::Vector2f(1600, 80));
    upperBuffer.setPosition(0, 0);
    upperBuffer.setFillColor(sf::Color(65,105,225));

    bottomBuffer = sf::RectangleShape(sf::Vector2f(1600, 160));
    bottomBuffer.setPosition(0, 1440);
    bottomBuffer.setFillColor(sf::Color(65,105,225));

    initializeButtons();

    //////////////////////////////////

    //////////////////////////////////
    // Board Initialization
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
    //////////////////////////////////


}

// Main Window Initialization
void Application::mainWindow(const int height, const int width){ mainWindowRef = make_shared<sf::RenderWindow>(sf::VideoMode(1600, 1600), this->appName); }

// Frame Rate Limiter Initialization
void Application::mainFrameRate(const int limit){ mainWindowRef->setFramerateLimit(limit); }

// Main window Reference
shared_ptr<sf::RenderWindow> Application::getMainWindowRef() const{ return mainWindowRef; }


// Renders and Draws Interface AND Cells
const void Application::renderInterface() const{

    mainWindowRef->clear();

    // Draw the cells 
    // Cell's Render method does the drawing
    for(auto each: boardCells){
        each->render(mainWindowRef);
    }

    // Draw the buffers
    mainWindowRef->draw(upperBuffer);
    mainWindowRef->draw(bottomBuffer);

}

// Renders Cells Only (Used while Running an algorithm)
const void Application::renderCells() const{
    for(auto each: boardCells){
        each->render(mainWindowRef);
    }
}

const void Application::displayInterface() const{ mainWindowRef->display(); }



void Application::runBFS() const{
    Application* appControls = const_cast<Application*>(this);
    BreadthFirstSearch(appControls);
}

void Application::runDFS() const{
    Application* appControls = const_cast<Application*>(this);
    DepthFirstSearch(appControls);
}

void Application::runAStar() const{
    Application* appControls = const_cast<Application*>(this);
    AStar(appControls);
}

void Application::runDjkstra() const{
    Application* appControls = const_cast<Application*>(this);
    Djkstra(appControls);
}

// Resets Application State Variables
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



const void Application::drawMenu() const{

    mainWindowRef->draw(textBFS);
    mainWindowRef->draw(textDFS);
    mainWindowRef->draw(textAStar);
    mainWindowRef->draw(textDjkstra);
    mainWindowRef->draw(textStart);
    mainWindowRef->draw(textReset);
    mainWindowRef->draw(textInfo);
    mainWindowRef->draw(textRandom);

}

const void Application::drawMenuAStar() const{
    mainWindowRef->draw(textEuc);
    mainWindowRef->draw(textManh);
    mainWindowRef->draw(textCheb);

    mainWindowRef->draw(textAStar);
    mainWindowRef->draw(textStart);
    mainWindowRef->draw(textReset);
    mainWindowRef->draw(textInfo);
    mainWindowRef->draw(textRandom);
}

const void Application::drawMenuDjkstra() const{

}


// Resets Board Attributes and Textures
void Application::resetBoard(){

    // Reset the Cell Attributes and Textures
    for(int i = 0; i < boardCells.size(); i++){
        boardCells.at(i)->resetAttributes();
        boardCells.at(i)->setTexture("../assets-static/node-empty.jpg");
        boardCells.at(i)->setScore(-1, i);
        boardCells.at(i)->resetScore8Way();
        boardCells.at(i)->render(mainWindowRef);
    }

    // Reset Button Colours
    textBFS.setColor(sf::Color::Yellow);
    textDFS.setColor(sf::Color::Yellow);
    textAStar.setColor(sf::Color::Yellow);
    textDjkstra.setColor(sf::Color::Yellow);
    textStart.setColor(sf::Color::Yellow);
    textReset.setColor(sf::Color::Yellow);
    textRandom.setColor(sf::Color::Yellow);

    textCheb.setColor(sf::Color::Yellow);
    textManh.setColor(sf::Color::Yellow);
    textEuc.setColor(sf::Color::Yellow);

    drawMenu();

}



AppState* Application::getStateRef(){return &this->state;}

const vector<shared_ptr<mapCell>>* Application::getboardRef() const {return &boardCells;}

Graph* Application::getGraphRef() const {return this->graph;}

GraphWeighted* Application::getWGraphRef() const{return this->graphWeighted;}



void Application::setGraph(Graph* graphRef){this->graph = graphRef;}

void Application::setWGraph(GraphWeighted* graphWRef){this->graphWeighted = graphWRef;}


Application::~Application(){}
