#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <queue>
#include <iostream>
#include <queue>
#include "../GraphWeighted.hpp"

using std::cout, std::endl, std::string;




// TODO
// Fix being trapped in the corner with 90 degree wall???








struct exlporedAStar{

    int boardIdx;
    int parentIdx;

    int gScore; // Current path cost to element
    int hScore; // Current Heuristic estimation
    int fScore; // Current total cost of the node

};


struct CompareFScore {
    bool operator()(shared_ptr<NodeExp> p1, shared_ptr<NodeExp> p2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return p1->getFScore() > p2->getFScore();
    }
};



bool AStar(GraphWeighted* graph, shared_ptr<sf::RenderWindow> windowRef){

    shared_ptr<NodeExp> startNode = graph->getStartNode();

    // Explore the element with (( Lowest Cost (Distance) + Heuristic Measure ))

    // PQueue or Min Heap
    // Visited, but not expanded (successors not explored yet)

    priority_queue<shared_ptr<NodeExp>, vector<shared_ptr<NodeExp>>, CompareFScore> openNodes;
    openNodes.push(startNode);


    cout<<"Inserted the first element"<<endl;

    // Initialize the vectors for all elements
    vector<int> exploredNodesIdx;
    vector<int> openNodesIdx;

    // Used to traceBack the path
    vector<exlporedAStar> traceback;

    for(int i = 0; i < graph->getMatrixSize(); i++){
        exploredNodesIdx.push_back(0);
        openNodesIdx.push_back(0);
        exlporedAStar newExplored;
        traceback.push_back(newExplored);

		// TODO: MARK HEURISTIC ESTIMATES
		// graph->nodeMatrix.at(i)->getCellRef()->setScore(graph->nodeMatrix.at(i)->getEstimate(), i);

    }


    // Not found on empty list
    while(openNodes.size() > 0){

        cout<<"Processing open nodes"<<endl;

        // Get the node with lowest F score in the list
        shared_ptr<NodeExp> currentNode = openNodes.top();
        openNodes.pop();

        openNodesIdx[currentNode->getIdx()] = 1;

        cout<<"Processing the starting node "<<endl;

        cout<<"Is target?: "<<currentNode->getCellRef()->checkIsTarget()<<endl;

        // Current is Target!
        if(currentNode->getCellRef()->checkIsTarget()){

            // Go backwards from target node following the parent nodes to start to find the path
            return true;
        }


        vector<shared_ptr<NodeExp>> neighbourNodes;

        cout<<(currentNode->getNextRight() == nullptr)<<endl;

        neighbourNodes.push_back(currentNode->getNextRight());
        neighbourNodes.push_back(currentNode->getNext45up());
        neighbourNodes.push_back(currentNode->getNextUp());
        neighbourNodes.push_back(currentNode->getPrev45up());
        neighbourNodes.push_back(currentNode->getPrevLeft());
        neighbourNodes.push_back(currentNode->getPrev45down());
        neighbourNodes.push_back(currentNode->getNextDown());
        neighbourNodes.push_back(currentNode->getNext45down());

        cout<<"Pushed all neighbours"<<endl;


        for(auto neighbour: neighbourNodes){

            cout<<"Traversing neighbours"<<endl;

            if(neighbour.get() == nullptr) continue;

            // Node inaccessible or already closed for exlporation
            if(neighbour->getCellRef()->checkIsWall() || exploredNodesIdx[neighbour->getIdx()]){
                cout<<"Non accessible"<<endl;
                continue;
            }   

			///////////////////////////////////////
			// Figure how the neighbour is reached!
			// TODO
			///////////////////////////////////////

            // If not in Open List
            // Add to open list
            // Make current the parent
            // Record G, H, F of the square
            else if(openNodesIdx[neighbour->getIdx()] == 0){

                cout<<"Neighbour Not in open list. Inserting"<<endl;

                openNodes.push(neighbour);
                traceback[neighbour->getIdx()].parentIdx = currentNode->getIdx(); 
                traceback[neighbour->getIdx()].boardIdx = neighbour->getIdx();

                traceback[neighbour->getIdx()].gScore = currentNode->getCurrent() + currentNode->getNextUpDistance();
                traceback[neighbour->getIdx()].hScore = neighbour->getEstimate();
                traceback[neighbour->getIdx()].fScore = traceback[neighbour->getIdx()].gScore + traceback[neighbour->getIdx()].hScore;


                neighbour->getCellRef()->setExplored();
                neighbour->getCellRef()->setTexture("../assets-static/node-neighbour.jpg");
				// TODO: ADD Correct traversal costs to heuristic estimations
                neighbour->getCellRef()->setScore(traceback[neighbour->getIdx()].fScore, neighbour->getIdx());

            }

            // If already open
            else if(openNodesIdx[neighbour->getIdx()] == 1){

				// Path to neighbour is shorter via current node, than found before
                // Calculate G, F for the neighbour again
                // Change parent of neighbour on OpenList to currentNode

                if(traceback[neighbour->getIdx()].gScore > (currentNode->getCurrent() + currentNode->getNextUpDistance())){

	                cout<<"Open but better path. Substituting"<<endl;

                    // openNodes.push(neighbour);

                    traceback[neighbour->getIdx()].parentIdx = currentNode->getIdx();
                    traceback[neighbour->getIdx()].boardIdx = neighbour->getIdx();

                    traceback[neighbour->getIdx()].gScore = currentNode->getCurrent() + currentNode->getNextUpDistance();
                    traceback[neighbour->getIdx()].hScore = neighbour->getEstimate();
                    traceback[neighbour->getIdx()].fScore = traceback[neighbour->getIdx()].gScore + traceback[neighbour->getIdx()].hScore;

                }

            }

			// Change the open status
            // openNodesIdx[currentNode->getIdx()] = 0;
        	exploredNodesIdx[currentNode->getIdx()] = 1;


            for(auto each: graph->nodeMatrix){
                each->getCellRef()->render(windowRef);
            }
            windowRef->display();

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