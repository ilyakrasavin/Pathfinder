
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

int main()
{
    // Main Rendering Window 
    sf::RenderWindow window(sf::VideoMode(900, 900), "Main Window!");
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

            shared_ptr<mapCell> test= make_shared<mapCell>("../assets-static/cell.jpg", false, false, false, false);
            test->SetPosition(k, i);

            boardCells.push_back(test);

            k+=30;
        }

        i+=30;
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

            // Some event handling examples
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();


            // Set the Walls
            if(event.type == sf::Event::MouseButtonPressed){
                // Gets Positions in window coordinates
                int xPos = sf::Mouse::getPosition(window).x;
                int yPos = sf::Mouse::getPosition(window).y;
                cout<<xPos<<endl;
                cout<<yPos<<endl;

                // Calculate the Cell index & replace
                int cellIdx = (yPos/30) * 30 + xPos / 30;
                cout<<"Cell IDX is "<<cellIdx<<endl;

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
                    boardCells[cellIdx] = make_shared<mapCell>("../assets-static/cell-red.jpg", false, true, false, false);
                    cout<<"Put a WALL @"<<cellIdx<<endl;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && !isFinishSet){
                    boardCells[cellIdx] = make_shared<mapCell>("../assets-static/cell-finish.jpg", true, false, false, false);
                    isFinishSet = true;
                    cout<<"Finish is set at position: "<<cellIdx<<endl;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !isStartSet){
                    boardCells[cellIdx] = make_shared<mapCell>("../assets-static/cell-start.jpg", false, false, true, false);
                    isStartSet = true;
                    startIdx = cellIdx;
                }
                else{
                    continue;
                }


                boardCells[cellIdx]->SetPosition(xPos - xPos%30, yPos - yPos%30);
                cout<<"Position set at "<<xPos - xPos%30<<" And :"<<yPos - yPos%30<<endl;

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

                Graph graph(&boardCells, window, startIdx);
                bool SearchResult = DepthFirstSearch(&graph, window);

                breadthFirstSearch = false;

                // return EXIT_SUCCESS;
            }

            if(breadthFirstSearch == false){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)){
                    breadthFirstSearch = true;

                    for(int i = 0; i < boardCells.size(); i++){
                        boardCells[i]->resetAttributes();
                        boardCells[i]->setTexture("../assets-static/cell.jpg");
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
