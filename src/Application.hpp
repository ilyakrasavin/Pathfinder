#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>

#include "Interface.hpp"
#include "Graph.hpp"
#include "GraphWeighted.hpp"


#include <memory>


using std::cout, std::endl, std::string, std::pair;


// Stores Application State Variables
struct AppState{

    bool isStartSet = false;
    bool isFinishSet = false;

    bool isAlgoChosen = false;
    bool isStartPressed = false;
    bool isRandomMap = false;
    bool isResetPressed = false;  

    int startIdx = 0;
    int tgtIdx = 0;

    bool breadthFirstSearch = false;
    bool depthFirstSearch = false;
    bool aStar = false;
    bool djkstra = false;

    bool astarMode = false;
    int astarModeSetting = 0;

};

// Algorithm Pointers
struct AlgorithmFactory{

    // void (*BreadthFirstSearch)(Application* appControl);
    // void (*DepthFirstSearch)(Graph*, shared_ptr<sf::RenderWindow>);
    // void (*AStar)(Graph*, shared_ptr<sf::RenderWindow>);

};


class Application{

    public:

        Application(const string name);

        void mainWindow(const int height, const int width);
        void mainFrameRate(const int limit);

        const void renderInterface() const;
        const void renderCells() const;
        const void displayInterface() const;

        const void drawMenu() const;
        const void drawMenuAStar() const;
        const void drawMenuDjkstra() const;

        void resetState();
        void resetBoard();

        ~Application();

    public:

        shared_ptr<sf::RenderWindow> getMainWindowRef() const;
        AppState* getStateRef();
        const vector<shared_ptr<mapCell>>* getboardRef() const;

        Graph* getGraphRef() const;
        GraphWeighted* getWGraphRef() const;

    public:

        void setGraph(Graph* graphRef);
        void setWGraph(GraphWeighted* graphWRef);

    public:
        void runDFS() const;
        void runBFS() const;
        void runAStar() const;

    private:

        // Main Program Window
        shared_ptr<sf::RenderWindow> mainWindowRef;

        // Active Window Components
        vector<shared_ptr<mapCell>> boardCells;

        // Static Window buffers
        sf::RectangleShape upperBuffer;
        sf::RectangleShape bottomBuffer;

        // Graph DSs
        Graph* graph = nullptr;
        GraphWeighted* graphWeighted = nullptr;

        AlgorithmFactory algoritms;

        // Program State Elements
        string appName;
        AppState state;

};

#endif