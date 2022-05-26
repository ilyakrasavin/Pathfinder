
using namespace std;

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include <vector>
#include <memory>

#include "Interface.hpp"
#include "Graph.hpp"


#include "Algorithms/BFS.hpp"
#include "Algorithms/DFS.hpp"



// TODO:

// FIX THE WALLS BEING IGNORED & OVERWRITTEN!

// 1. !! Decide on & implement the final interface !!
// 2. Implement Algorithm Selection AND proper restart feature
// 3. Some Algorithm GUI & Basic info panel
// 4. Verify BFS & DFS

// OOP!
// Application class
// Interface (Add components)

// A* theory
// Another graph class with weight & edges support
// Add edges



int main()
{
    // Main Rendering Window 
    sf::RenderWindow window(sf::VideoMode(1600, 1600), "Main Window!");
    window.setFramerateLimit(60);


    // Mouse Release Check
    bool mouseReleased = false;


    // Frame Rate Setup
    sf::Clock clock;


    // Generate the Board:
    vector<shared_ptr<mapCell>> boardCells;

    // Initialize the board of cells

    for(int i = 0; i < window.getSize().y;){

        for(int k = 0; k < window.getSize().x;){

            shared_ptr<mapCell> test = make_shared<mapCell>("../assets-static/node-empty.jpg", false, false, false, false);
            test->SetPosition(k, i);

            boardCells.push_back(test);

            k+=80;
        }

        i+=80;
    }


    // Set up fonts
    // sf::Font font;
    // if (!font.loadFromFile("../assets-static/Raleway-Regular.ttf"))
    //     return EXIT_FAILURE;
    // sf::Text text("Hello SFML", font, 50);
    // text.setColor(sf::Color::Blue);
    // text.setPosition(sf::Vector2f(20, 50));


    bool isStartSet = false;
    bool isFinishSet = false; // Run the algorithm on true

    int startIdx = 0;

    bool breadthFirstSearch = true;


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

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();


            // Set the cell Attributes
            if(event.type == sf::Event::MouseButtonPressed){
                // Gets Positions in window coordinates
                int xPos = sf::Mouse::getPosition(window).x;
                int yPos = sf::Mouse::getPosition(window).y;
                cout<<xPos<<endl;
                cout<<yPos<<endl;

                // Calculate the Cell index & replace
                int cellIdx = (yPos/80) * 20 + xPos / 80;
                cout<<"Cell IDX is "<<cellIdx<<endl;

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
                    boardCells[cellIdx]->resetAttributes();
                    boardCells[cellIdx]->setTexture("../assets-static/node-wall.jpg");
                    boardCells[cellIdx]->setWall();
                    cout<<"Put a WALL @"<<cellIdx<<endl;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && !isFinishSet){
                    isFinishSet = true;

                    boardCells[cellIdx]->resetAttributes();
                    boardCells[cellIdx]->setTexture("../assets-static/node-finish.jpg");
                    boardCells[cellIdx]->setTarget();

                    cout<<"Finish is set at position: "<<cellIdx<<endl;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !isStartSet){
                    isStartSet = true;
                    startIdx = cellIdx;

                    boardCells[cellIdx]->resetAttributes();
                    boardCells[cellIdx]->setTexture("../assets-static/node-start.jpg");
                    boardCells[cellIdx]->setStart();

                }
                else{
                    continue;
                }

                boardCells[cellIdx]->SetPosition(xPos - xPos%80, yPos - yPos%80);
                cout<<"Position set at "<<xPos - xPos%80<<" And :"<<yPos - yPos%80<<endl;

            }


            // Rendering
            window.clear();

            // Draw Board Cells
            for(int i = 0; i < boardCells.size(); i++){
                boardCells[i]->render(window);
            }

            // window.draw(text);
            window.display();

            cout<<"START INDEX IS: "<<startIdx<<endl;


            if(isFinishSet == true && breadthFirstSearch == true){

                // Initialize the Graph and pass it to the algorithm
                // Pass the reference to the window
                // Further Graph updates and rendering done within the algorithm

                Graph graph(&boardCells, window, startIdx, 20);
                bool SearchResult = BreadthFirstSearch(&graph, window);

                breadthFirstSearch = false;

                // return EXIT_SUCCESS;
            }

            if(breadthFirstSearch == false){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)){
                    breadthFirstSearch = true;

                    for(int i = 0; i < boardCells.size(); i++){
                        boardCells[i]->resetAttributes();
                        boardCells[i]->setTexture("../assets-static/node-empty.jpg");
                        boardCells[i]->render(window);
                    }
                    window.display();

                    isStartSet = false;
                    isFinishSet = false;

                    break;
                }

            }




        }

        // No Rendering / Display Updates for the actions done outside of Polling Loop
        // Main App updates HERE
        // Algortihm Updates / Checks etc...

    }

    return EXIT_SUCCESS;
}
