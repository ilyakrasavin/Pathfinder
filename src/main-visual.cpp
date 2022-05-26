
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

// 1. !! Decide on & implement the final interface !!
// 2. Implement Algorithm Selection AND proper restart feature
// 3. Some Algorithm GUI & Basic info panel
// 4. Verify BFS & DFS

// Random Walls

// OOP!
// Application class
// Interface (Add components)

// A* theory
// Another graph class with weight & edges support
// Add edges



// DONE:
// FIX THE WALLS BEING IGNORED & OVERWRITTEN! -> New objects created on stack produced a problem (copies located in a vector => No reference to actual object)


int main()
{
    // Main Rendering Window 
    sf::RenderWindow window(sf::VideoMode(1600, 1600), "Main Window!");
    window.setFramerateLimit(60);


    sf::RectangleShape upperBuffer(sf::Vector2f(1600, 80));
    upperBuffer.setPosition(0, 0);
    upperBuffer.setFillColor(sf::Color(65,105,225));


    sf::RectangleShape bottomBuffer(sf::Vector2f(1600, 160));
    bottomBuffer.setPosition(0, 1440);
    bottomBuffer.setFillColor(sf::Color(65,105,225));

    // Set up fonts
    sf::Font font;
    if (!font.loadFromFile("../assets-static/Raleway-Regular.ttf"))
        return EXIT_FAILURE;
    sf::Text text1("BFS", font, 45);
    text1.setColor(sf::Color::Yellow);
    text1.setPosition(sf::Vector2f(80, 12));

    sf::Text text2("DFS", font, 45);
    text2.setColor(sf::Color::Yellow);
    text2.setPosition(sf::Vector2f(200, 12));

    sf::Text text3("A*", font, 45);
    text3.setColor(sf::Color::Yellow);
    text3.setPosition(sf::Vector2f(360, 12));

    sf::Text text4("Djkstra", font, 45);
    text4.setColor(sf::Color::Yellow);
    text4.setPosition(sf::Vector2f(500, 12));


    sf::Text textStart("Start", font, 45);
    textStart.setColor(sf::Color::Yellow);
    textStart.setPosition(sf::Vector2f(80, 1455));

    sf::Text textReset("Reset", font, 45);
    textReset.setColor(sf::Color::Yellow);
    textReset.setPosition(sf::Vector2f(200, 1455));

    sf::Text textRandom("Random Map", font, 45);
    textRandom.setColor(sf::Color::Yellow);
    textRandom.setPosition(sf::Vector2f(600, 1455));

    sf::Text textInfo("Hold 'W' to set the Walls (Or press Random)\nHold 'S' to set the Start\nHold 'F' to set the Target", font, 30);
    textInfo.setColor(sf::Color::Yellow);
    textInfo.setPosition(sf::Vector2f(920, 1455));



    // Mouse Release Check
    bool mouseReleased = false;

    // Frame Rate Setup
    sf::Clock clock;


    // Generate the Board:
    vector<shared_ptr<mapCell>> boardCells;

    // Initialize the board of cells

    for(int i = 80; i < window.getSize().y - 160;){

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
    bool depthFirstSearch = true;
    bool aStar = true;
    bool djkstra = true;

    bool isAlgoChosen = false;
    bool isStartPressed = false;
    bool isRandomMap = false;
    





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
                int cellIdx = ((yPos - 80)/80) * 20 + xPos / 80;
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


            window.draw(upperBuffer);
            window.draw(bottomBuffer);
            window.draw(text1);
            window.draw(text2);
            window.draw(text3);
            window.draw(text4);
            window.draw(textStart);
            window.draw(textReset);
            window.draw(textInfo);
            window.draw(textRandom);
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
