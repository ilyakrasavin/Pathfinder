#ifndef APP
#define APP

#include <SFML/Graphics.hpp>
#include "Interface.hpp"
#include "Graph.hpp"
#include "GraphWeighted.hpp"

#include <memory>

using namespace std;


class Application{

    public:

        Application();

        void setMainWindow();
        sf::RenderWindow& getMainWindowRef();


        ~Application();

    private:

        sf::RenderWindow& mainWindow;
        IComponent& board;

        // Pointers to Algorithms

        Graph& graph;
        GraphWeighted& graph;

        vector<sf::Text&> infoBuffers;

};

#endif