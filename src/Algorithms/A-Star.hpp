#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <queue>
#include <iostream>

#include "../GraphWeighted.hpp"

using std::cout, std::endl, std::string;


struct exlporedAStar{

    int boardIdx;
    int parentIdx;

    int gScore; // Current path cost to element
    int hScore; // Current Heuristic estimation
    int fScore; // Current total cost of the node

};



bool AStar(GraphWeighted* graph, shared_ptr<sf::RenderWindow> windowRef){

    const shared_ptr<NodeExp> currentNode = graph->getStartNode();

    // Explore the element with (( Lowest Cost (Distance) + Heuristic Measure ))

    // PQueue or Min Heap
    // Visited, but not expanded (successors not explored yet)
    vector<shared_ptr<NodeExp>> openNodes;
    openNodes.push_back(currentNode);

    vector<exlporedAStar> traceback;


    // Visited and expanded
    // Successors already in the open list
    vector<int> exploredNodes;
    // Initialize the vector for all elements

    // Not found on empty list
    while(openNodes.size() > 0){

        // Get the node with lowest F score in the list
        currentNode = openNodes.pop_back();


        // Current is Target!
        if(currentNode->getCellRef()->checkIsTarget()){

            // Go backwards from target node following the parent nodes to start to find the path
            return true;
        }




        vector<shared_ptr<NodeExp>> neighbourNodes;

        neighbourNodes.push_back(currentNode->getNextRight());
        neighbourNodes.push_back(currentNode->getNext45up());
        neighbourNodes.push_back(currentNode->getNextUp());
        neighbourNodes.push_back(currentNode->getPrev45up());
        neighbourNodes.push_back(currentNode->getPrevLeft());
        neighbourNodes.push_back(currentNode->getPrev45down());
        neighbourNodes.push_back(currentNode->getNextDown());
        neighbourNodes.push_back(currentNode->getNext45down);

        for(auto neighbour: neighbourNodes){

            if(neighbour == nullptr) continue;

            // Node inaccessible or already closed for exlporation
            if(neighbour->getCellRef()->checkIsWall() || exploredNodes[neighbour->getIdx()]){
                continue;
            }   

            // If not in Open List     
            // Add to open list
            // Make current the parent  
            // Record G, H, F of the square  
            else if(!openNodes[neighbour->getIdx()]){
                openNodes.push_back(neighbour);
                traceback[neighbour->getIdx()].parentIdx = currentNode->getIdx(); 
            }

            // If already open
            else if(openNodes[neighbour->getIdx()]){

                // IF found path to neighbour is better via current node
                // Change parent of neighbour on OpenList to currentNode
                // Calculate G, F for the neighbour again
                if(traceback[neighbour->getIdx()].gScore > currentNode->getCurrent + currentNode->getNext45DownDistance())
                    traceback[neighbour->getIdx()].parentIdx = currentNode->getIdx();

            }

        }





        // Put the node into the explored list
        // Look at all neighbours:

            // Set current score as F= G(current) + w(current, neighbour)

            // If successor is in the OPEN list:
                // If G score of successor in the Open List is less than the cost to neighbour -> continue
                // If successor is also in the Closed list:
                    // If G score of successor in the Closed is less than the cost to neighbour -> continue
                    // Otherwise, move successor from Closed to Open list 

            // Otherwise if not in Open List
                // Add node_successor to the OPEN list
                // Set h(node_successor) to be the heuristic distance to node_goal

        

        // ----------------------------------


        // Traverse neighbours computing F = (G(current) + w(current, neighbour))
        // F < G(neighbour):
        // There is a shorter way to reach neighbour than reached before

            // cameFrom[neighbor] := current
            // gScore[neighbor] := tentative_gScore
            // fScore[neighbor] := tentative_gScore + h(neighbor)
            // if neighbor not in openSet
            //     openSet.add(neighbor)



    }



    return false;
}

#endif