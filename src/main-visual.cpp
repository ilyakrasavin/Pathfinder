
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>

#include <vector>
#include <memory>

#include "Interface.hpp"
#include "Graph.hpp"


#include "Algorithms/BFS.hpp"
#include "Algorithms/DFS.hpp"
#include "Algorithms/A-Star.hpp"

#include "Application.hpp"

// FIX: Button rendering seg. fault if encapsulated in a manager class (Pointers likely)


// TODO:

// 4. Verify BFS & DFS

// Random Walls

// OOP!
// Application class
// Interface (Add components)

// A* theory
// Another graph class with weight & edges support
// Add edges

// Add CMake functionality

// 3. Some Algorithm GUI & Basic info panel


// DOING:

// DONE:
// FIX THE WALLS BEING IGNORED & OVERWRITTEN! -> New objects created on stack produced a problem (copies located in a vector => No reference to actual object)
// 1. !! Decide on & implement the final interface !!
// 2. Implement Algorithm Selection AND proper restart feature


int main()
{

    Application app("Pathfinder");


    // // Main Rendering Window
    // sf::RenderWindow window(sf::VideoMode(1600, 1600), "Pathfinder");
    // window.setFramerateLimit(60);


    // Mouse Release Check
    bool mouseReleased = false;

    // Frame Rate Setup
    sf::Clock clock;


    // TODO: Buttons inaccessible if encapsulated. 
    /////////////////////////////////////////////////////////////

    sf::Font font;
    font.loadFromFile("../assets-static/Raleway-Regular.ttf");

    sf::Text text1("BFS", font, 45);
    text1.setColor(sf::Color::Yellow);
    text1.setPosition(80, 12);

    sf::Text text2("DFS", font, 45);
    text2.setColor(sf::Color::Yellow);
    text2.setPosition(200,12);


    sf::Text text3("A*", font, 45);
    text3.setColor(sf::Color::Yellow);
    text3.setPosition(330,12);

    sf::Text text4("Djkstra", font, 45);
    text4.setColor(sf::Color::Yellow);
    text4.setPosition(420,12);


    sf::Text textStart("Start", font, 45);
    textStart.setColor(sf::Color::Yellow);
    textStart.setPosition(80,1490);


    sf::Text textReset("Reset", font, 45);
    textReset.setColor(sf::Color::Yellow);
    textReset.setPosition(220,1490);

    sf::Text textRandom("Random Map", font, 45);
    textRandom.setColor(sf::Color::Yellow);
    textRandom.setPosition(1300,12);

    sf::Text textInfo("Hold 'W' to set the Walls (Or press Random)\nHold 'S' to set the Start\nHold 'F' to set the Target\nPress Esc to exit at any time", font, 30);
    textInfo.setColor(sf::Color::Yellow);
    textInfo.setPosition(920, 1448);

    ///////////////////////////////////////////////

    // Application State variables (To be moved into App class)

    bool isStartSet = false;
    bool isFinishSet = false;

    int startIdx = 0;
    int endIdx = 0;

    bool breadthFirstSearch = false;
    bool depthFirstSearch = false;
    bool aStar = false;
    bool djkstra = false;

    bool isAlgoChosen = false;
    bool isStartPressed = false;
    bool isRandomMap = false;
    bool isResetPressed = false;    


    // Rendering Window Outer loop
    while (app.getMainWindowRef()->isOpen())
    {
        // Declare an event to be handled later
        // Events put into a queue and processed one by ones
        sf::Event event;
        
        
        while (app.getMainWindowRef()->pollEvent(event))
        {
            // Compute the frame rate:
            float secCurrent = clock.restart().asSeconds();
            float fps = 1.0f / secCurrent;

            cout<<"FPS: "<<fps<<endl;

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
                app.getMainWindowRef()->close();
            }


            // Set the cell Attributes
            if(event.type == sf::Event::MouseButtonPressed){
                // Gets Positions in window coordinates

                int xPos = sf::Mouse::getPosition(*app.getMainWindowRef()).x;
                int yPos = sf::Mouse::getPosition(*app.getMainWindowRef()).y;
                cout<<xPos<<endl;
                cout<<yPos<<endl;

                // Choose BFS
                if(xPos >= 80 && xPos <= 160 && yPos >= 25 && yPos <= 60 && !app.getStateRef()->isAlgoChosen){

                    text2.setColor(sf::Color(169,169,169));
                    text3.setColor(sf::Color(169,169,169));
                    text4.setColor(sf::Color(169,169,169));

                    app.getStateRef()->breadthFirstSearch = true;
                    app.getStateRef()->isAlgoChosen = true;

                }
                // Choose DFS
                else if(xPos >= 200 && xPos <= 285 && yPos >= 25 && yPos <= 60 && !app.getStateRef()->isAlgoChosen){
                    text1.setColor(sf::Color(169,169,169));
                    text3.setColor(sf::Color(169,169,169));
                    text4.setColor(sf::Color(169,169,169));

                    app.getStateRef()->depthFirstSearch = true;
                    app.getStateRef()->isAlgoChosen = true;

                }

                else if(xPos >= 330 && xPos <= 380 && yPos >= 25 && yPos <= 60 && !app.getStateRef()->isAlgoChosen){
                    text1.setColor(sf::Color(169,169,169));
                    text2.setColor(sf::Color(169,169,169));
                    text4.setColor(sf::Color(169,169,169));
                    
                    app.getStateRef()->aStar = true;
                    app.getStateRef()->isAlgoChosen = true;

                }


                // Pressed Reset 
                else if(xPos >= 220 && xPos <= 340 && yPos >= 1490 && yPos <= 1535){

                    // Performs full State Reset on loop exit
                    // Move into an App class

                    app.getStateRef()->isResetPressed = true;

                }

                // Pressed Start
                else if(xPos >= 80 && xPos <= 180 && yPos >= 1490 && yPos <= 1535){
                    textStart.setColor(sf::Color(169,169,169));

                    app.getStateRef()->isStartPressed = true;
                }

                // Pressed Random Map
                else if(xPos >= 1300 && xPos <= 1580 && yPos >= 12 && yPos <= 57){
                    textReset.setColor(sf::Color(169,169,169));

                    app.getStateRef()->isRandomMap = true;
                    
                    // Generate Random walls
                    // 
                }


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

                    endIdx = cellIdx;

                    app.getStateRef()->isFinishSet = true;

                    app.getboardRef()->at(cellIdx)->resetAttributes();
                    app.getboardRef()->at(cellIdx)->setTexture("../assets-static/node-finish.jpg");
                    app.getboardRef()->at(cellIdx)->setTarget();

                    cout<<"Finish is set at position: "<<cellIdx<<endl;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !app.getStateRef()->isStartSet){
                    startIdx = cellIdx;

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

            app.getMainWindowRef()->draw(text1);
            app.getMainWindowRef()->draw(text2);
            app.getMainWindowRef()->draw(text3);
            app.getMainWindowRef()->draw(text4);
            app.getMainWindowRef()->draw(textStart);
            app.getMainWindowRef()->draw(textReset);
            app.getMainWindowRef()->draw(textInfo);
            app.getMainWindowRef()->draw(textRandom);


            app.displayInterface();


            cout<<"START INDEX IS: "<<startIdx<<endl;


            if(app.getStateRef()->isFinishSet == true && app.getStateRef()->breadthFirstSearch == true && app.getStateRef()->isStartPressed){

                // Initialize the Graph and pass it to the algorithm
                // Pass the reference to the window
                // Further Graph updates and rendering done within the algorithm

                vector<shared_ptr<mapCell>>* boardRef = (vector<shared_ptr<mapCell>>*)app.getboardRef();

                Graph graph(app.getboardRef(), app.getMainWindowRef(), startIdx, 20);

                bool SearchResult = BreadthFirstSearch(&graph, app.getMainWindowRef());

                app.getStateRef()->breadthFirstSearch = false;

                // Full state Reset on Reset Button Press

                // return EXIT_SUCCESS;
            }

            if(app.getStateRef()->isFinishSet == true && app.getStateRef()->depthFirstSearch == true && app.getStateRef()->isStartPressed){

                // Initialize the Graph and pass it to the algorithm
                // Pass the reference to the window
                // Further Graph updates and rendering done within the algorithm

                Graph graph(app.getboardRef(), app.getMainWindowRef(), startIdx, 20);
                bool SearchResult = DepthFirstSearch(&graph, app.getMainWindowRef());

                app.getStateRef()->depthFirstSearch = false;


                // Full state reset on Reset Button press

                // return EXIT_SUCCESS;
            }

            if(app.getStateRef()->isFinishSet == true && app.getStateRef()->aStar == true && app.getStateRef()->isStartPressed){

                // Initialize the Graph and pass it to the algorithm
                // Pass the reference to the window
                // Further Graph updates and rendering done within the algorithm

                GraphWeighted graph(app.getboardRef(), app.getMainWindowRef(), startIdx, 20, endIdx);
                bool SearchResult = AStar(&graph, app.getMainWindowRef());

                app.getStateRef()->aStar = false;


                // Full state reset on Reset Button press

                // return EXIT_SUCCESS;
            }


            // Put into App class
            if(app.getStateRef()->isResetPressed){
                // Perform full Application state reset

                    // breadthFirstSearch = false;
                    // depthFirstSearch = false;

                    // isStartSet = false;
                    // isFinishSet = false;

                    // isAlgoChosen = false;
                    // isStartPressed = false;
                    // isRandomMap = false;
                    // isResetPressed = false; 

                    app.resetState();

                    for(int i = 0; i < app.getboardRef()->size(); i++){
                        app.getboardRef()->at(i)->resetAttributes();
                        app.getboardRef()->at(i)->setTexture("../assets-static/node-empty.jpg");
                        app.getboardRef()->at(i)->render(app.getMainWindowRef());
                    }

                    
                    text1.setColor(sf::Color::Yellow);
                    text2.setColor(sf::Color::Yellow);
                    text3.setColor(sf::Color::Yellow);
                    text4.setColor(sf::Color::Yellow);
                    textStart.setColor(sf::Color::Yellow);
                    textReset.setColor(sf::Color::Yellow);
                    textInfo.setColor(sf::Color::Yellow);
                    textRandom.setColor(sf::Color::Yellow);


                    app.getMainWindowRef()->draw(text1);
                    app.getMainWindowRef()->draw(text2);
                    app.getMainWindowRef()->draw(text3);
                    app.getMainWindowRef()->draw(text4);
                    app.getMainWindowRef()->draw(textStart);
                    app.getMainWindowRef()->draw(textReset);
                    app.getMainWindowRef()->draw(textInfo);
                    app.getMainWindowRef()->draw(textRandom);


                    app.getMainWindowRef()->display();
    

                    break;

            }



        }

        // No Rendering / Display Updates for the actions done outside of Polling Loop
        // Main App updates HERE
        // Algortihm Updates / Checks etc...

    }

    return EXIT_SUCCESS;
}
