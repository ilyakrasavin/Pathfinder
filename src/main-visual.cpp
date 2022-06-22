
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>

#include <vector>
#include <memory>

#include "Interface.hpp"
#include "Graph.hpp"
#include "GraphWeighted.hpp"

#include "Application.hpp"
#include "textButtons.hpp"

#include "Algorithms/BFS.hpp"
#include "Algorithms/DFS.hpp"
#include "Algorithms/A-Star.hpp"


using std::string, std::cout, std::endl, std::shared_ptr;


// TODO:

// DJkstra

// Verify BFS & DFS
// Verify AStar

// REPLACE Repeated code (State resets / window rendering loops etc.)

// Fix AStar being trapped by a 90 degree wall

// Add CMake functionality

// Change and review all colour textures to better quality

// FIX: Button rendering seg. fault if encapsulated in a manager class (Pointers likely)

// FIX All warnings. They are potential errors


///////////////////////////////////////////////////

// DONE:

// Another graph class with weight & edges support
// Add edges
// 3. Some Algorithm GUI & Basic info panel
// A* theory
// FIX THE WALLS BEING IGNORED & OVERWRITTEN! -> New objects created on stack produced a problem (copies located in a vector => No reference to actual object)
// 1. !! Decide on & implement the final interface !!
// 2. Implement Algorithm Selection AND proper restart feature
// Random Walls Generation 
// Persistent Estimator Board for AStar


///////////////////////////////////////////////////



int main()
{

    Application app("Pathfinder");
    Application* appRef = &app;

    // Rendering Window Outer loop
    while (app.getMainWindowRef()->isOpen())
    {
        // Declare an event to be handled later
        // Events put into a queue and processed one by ones
        sf::Event event;
        
        
        while (app.getMainWindowRef()->pollEvent(event))
        {

            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
                app.getMainWindowRef()->close();
            }


            // Set the cell Attributes
            if(event.type == sf::Event::MouseButtonPressed){
                // Gets Positions in window coordinates

                int xPos = sf::Mouse::getPosition(*app.getMainWindowRef()).x;
                int yPos = sf::Mouse::getPosition(*app.getMainWindowRef()).y;

                // Choose BFS
                if(xPos >= 80 && xPos <= 160 && yPos >= 25 && yPos <= 60 && !app.getStateRef()->isAlgoChosen){

                    textDFS.setColor(sf::Color(169,169,169));
                    textAStar.setColor(sf::Color(169,169,169));
                    textDjkstra.setColor(sf::Color(169,169,169));

                    app.getStateRef()->breadthFirstSearch = true;
                    app.getStateRef()->isAlgoChosen = true;

                }

                // Choose DFS
                else if(xPos >= 200 && xPos <= 285 && yPos >= 25 && yPos <= 60 && !app.getStateRef()->isAlgoChosen){

                    textBFS.setColor(sf::Color(169,169,169));
                    textAStar.setColor(sf::Color(169,169,169));
                    textDjkstra.setColor(sf::Color(169,169,169));

                    app.getStateRef()->depthFirstSearch = true;
                    app.getStateRef()->isAlgoChosen = true;

                }

                // Choose AStar
                else if(xPos >= 330 && xPos <= 380 && yPos >= 25 && yPos <= 60 && !app.getStateRef()->isAlgoChosen){

                    textBFS.setColor(sf::Color(169,169,169));
                    textDFS.setColor(sf::Color(169,169,169));
                    textDjkstra.setColor(sf::Color(169,169,169));
                    
                    app.getStateRef()->aStar = true;
                    app.getStateRef()->isAlgoChosen = true;

                    app.getStateRef()->astarMode = true;

                }

                // AStar: Euclidian
                else if(xPos >= 460 && xPos <= 646 && yPos >= 20 && yPos <= 65 && app.getStateRef()->isAlgoChosen && app.getStateRef()->aStar){

                    textEuc.setColor(sf::Color::Yellow);
                    textManh.setColor(sf::Color(169,169,169));
                    textCheb.setColor(sf::Color(169,169,169));
                    app.getStateRef()->astarModeSetting = 0;
                }

                // AStar: Manhattan
                else if(xPos >= 700 && xPos <= 920 && yPos >= 20 && yPos <= 65 && app.getStateRef()->isAlgoChosen && app.getStateRef()->aStar){
                    textEuc.setColor(sf::Color(169,169,169));
                    textCheb.setColor(sf::Color(169,169,169));
                    textManh.setColor(sf::Color::Yellow);
                    app.getStateRef()->astarModeSetting = 1;
                }

                // AStar: Chebushev
                else if(xPos >= 970 && xPos <= 1200 && yPos >= 20 && yPos <= 65 && app.getStateRef()->isAlgoChosen && app.getStateRef()->aStar){
                    textManh.setColor(sf::Color(169,169,169));
                    textEuc.setColor(sf::Color(169,169,169));
                    textCheb.setColor(sf::Color::Yellow);
                    app.getStateRef()->astarModeSetting = 2;
                }


                // Reset Pressed 
                else if(xPos >= 220 && xPos <= 340 && yPos >= 1490 && yPos <= 1535){

                    // Performs full State Reset on loop exit
                    app.resetState();
                    app.resetBoard();

                    app.drawMenu();

                    app.displayInterface();

                    break;

                }

                // Pressed Start
                else if(xPos >= 80 && xPos <= 180 && yPos >= 1490 && yPos <= 1535){
                    textStart.setColor(sf::Color(169,169,169));

                    app.getStateRef()->isStartPressed = true;
                }

                // Pressed Random Map
                else if(xPos >= 1300 && xPos <= 1580 && yPos >= 12 && yPos <= 57){
                    
                    // Reset Field Only
                    for(int i = 0; i < app.getboardRef()->size(); i++){

                        if(app.getboardRef()->at(i)->checkIsStart() || app.getboardRef()->at(i)->checkIsTarget()){
                            continue;
                        }

                        app.getboardRef()->at(i)->resetAttributes();
                        app.getboardRef()->at(i)->setTexture("../assets-static/node-empty.jpg");
                        app.getboardRef()->at(i)->setScore(-1, i);
                        app.getboardRef()->at(i)->render(app.getMainWindowRef());
                    }

                    app.getStateRef()->isRandomMap = true;
                    
                    // Generate Random walls
                    random_device randomNum;
                    for(int i = 0; i < app.getboardRef()->size(); i++){

                        if(app.getboardRef()->at(i)->checkIsStart() || app.getboardRef()->at(i)->checkIsTarget()){
                            continue;
                        }

                        int randomSeed = randomNum();
                        
                        // Example of Random decision...
                        if(randomSeed % 3 == 0){

                            app.getboardRef()->at(i)->setWall();
                            app.getboardRef()->at(i)->setTexture("../assets-static/node-wall.jpg");
                            app.getboardRef()->at(i)->render(app.getMainWindowRef());

                        }

                    }

                    app.displayInterface();

                }

                // Handle mouse presses all over the interface (out of bounds)
                // With or without the key pressed
                // else if(xPos){
                // }

                // Calculate the Cell index & replace
                int cellIdx = ((yPos - 80)/80) * 20 + xPos / 80;
                cout<<"Cell IDX is "<<cellIdx<<endl;

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
                    app.getboardRef()->at(cellIdx)->resetAttributes();
                    app.getboardRef()->at(cellIdx)->setTexture("../assets-static/node-wall.jpg");
                    app.getboardRef()->at(cellIdx)->setWall();
                    cout<<"Put a WALL @"<<cellIdx<<endl;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && !app.getStateRef()->isFinishSet){

                    app.getStateRef()->tgtIdx = cellIdx;

                    app.getStateRef()->isFinishSet = true;

                    app.getboardRef()->at(cellIdx)->resetAttributes();
                    app.getboardRef()->at(cellIdx)->setTexture("../assets-static/node-finish.jpg");
                    app.getboardRef()->at(cellIdx)->setTarget();

                    cout<<"Finish is set at position: "<<cellIdx<<endl;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !app.getStateRef()->isStartSet){
                    app.getStateRef()->startIdx = cellIdx;

                    app.getStateRef()->isStartSet = true;


                    app.getboardRef()->at(cellIdx)->resetAttributes();
                    app.getboardRef()->at(cellIdx)->setTexture("../assets-static/node-start.jpg");
                    app.getboardRef()->at(cellIdx)->setStart();


                }
                else{
                    continue;
                }

                app.getboardRef()->at(cellIdx)->SetPosition(xPos - xPos%80, yPos - yPos%80);
                cout<<"Position set at "<<xPos - xPos%80<<" And :"<<yPos - yPos%80<<endl;

            }


            app.renderInterface();
            if(app.getStateRef()->astarMode){
                app.drawMenuAStar();
            }
            else{
                app.drawMenu();
            }
            app.displayInterface();


            if(app.getStateRef()->isFinishSet == true && app.getStateRef()->breadthFirstSearch == true && app.getStateRef()->isStartPressed){

                Graph graph(app.getboardRef(), app.getMainWindowRef(), app.getStateRef()->startIdx, 20);
                app.setGraph(&graph);

                BreadthFirstSearch(&graph, app.getMainWindowRef());

                app.getStateRef()->breadthFirstSearch = false;

            }

            if(app.getStateRef()->isFinishSet == true && app.getStateRef()->depthFirstSearch == true && app.getStateRef()->isStartPressed){

                Graph graph(app.getboardRef(), app.getMainWindowRef(), app.getStateRef()->startIdx, 20);
                
                DepthFirstSearch(&graph, app.getMainWindowRef());

                app.getStateRef()->depthFirstSearch = false;

            }

            if(app.getStateRef()->isFinishSet == true && app.getStateRef()->aStar == true){

                GraphWeighted graph(app.getboardRef(), app.getMainWindowRef(), app.getStateRef()->startIdx, 20, app.getStateRef()->tgtIdx, app.getStateRef()->astarModeSetting);

                // Resolve the Heuristic mode for A*
                if(app.getStateRef()->isStartPressed){

                    bool SearchResult = AStar(&graph, app.getMainWindowRef());

                    app.getStateRef()->aStar = false;
                }

            }

            // if(app.getStateRef()->isResetPressed){

            //     // Resets Application state variables / Board Textures & Attributes
            //     app.resetState();
            //     app.resetBoard();

            //     app.drawMenu();

            //     app.displayInterface();

            //     break;
            // }

        }

        // No Rendering / Display Updates for the actions done outside of Polling Loop
        // Main App updates HERE
        // Algortihm Updates / Checks etc...

    }

    return EXIT_SUCCESS;
}
