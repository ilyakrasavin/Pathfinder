#include "A-Star.hpp"

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


int computeDirection(shared_ptr<NodeExp> currentNodeRef, int neighbourIdx){

    // Compute the neighbour direction
    // Return corrent distance

}


bool AStar(Application* appControls){

    shared_ptr<NodeExp> startNode = appControls->getWGraphRef()->getStartNode();

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

    int indexIncrements = 20;


    for(int i = 0; i < appControls->getWGraphRef()->getMatrixSize(); i++){

        exlporedAStar newExplored;

        exploredNodesIdx.push_back(0);
        openNodesIdx.push_back(0);
        traceback.push_back(newExplored);

		// TODO: MARK HEURISTIC ESTIMATES
		// graph->nodeMatrix.at(i)->getCellRef()->setScore(graph->nodeMatrix.at(i)->getEstimate(), i);

    }

    cout<<"Traceback Array Filled"<<endl;

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

            int neighbourIdx = neighbour->getIdx();

            // If not in Open List
            // Add to open list
            // Make current the parent
            // Record G, H, F of the square
            bool isTopLeft = neighbourIdx % indexIncrements == 0 && (neighbourIdx == 0);
            bool isTopEdge = (neighbourIdx > 0) && (neighbourIdx < (indexIncrements - 1));
            bool isTopRight = (neighbourIdx % indexIncrements == (indexIncrements - 1)) && (neighbourIdx == ((indexIncrements - 1)));
            bool isLeftEdge = (neighbourIdx % indexIncrements == 0) && ((neighbourIdx + indexIncrements) < appControls->getWGraphRef()->getMatrixSize());
            bool isRightEdge = (neighbourIdx % indexIncrements == (indexIncrements - 1)) && ((neighbourIdx + indexIncrements) < appControls->getWGraphRef()->getMatrixSize());
            bool isBottomLeft = (neighbourIdx % indexIncrements == 0) && ((neighbourIdx + indexIncrements) > appControls->getWGraphRef()->getMatrixSize());
            bool isBottomEdge = (neighbourIdx > (appControls->getWGraphRef()->getMatrixSize() - (indexIncrements + 1))) && (neighbourIdx < (appControls->getWGraphRef()->getMatrixSize() - 1));
            bool isBottomRight = (neighbourIdx % indexIncrements == (indexIncrements - 1)) && (neighbourIdx + 1 >= appControls->getWGraphRef()->getMatrixSize());
            bool isMiddle = {!(isTopLeft || isTopEdge || isTopRight || isLeftEdge 
                            || isRightEdge || isBottomLeft || isBottomEdge || isBottomRight)};

            // // Node is NextRight and Node is not a Right Top/Bottom/Edge Node
            // if((neighbourIdx == (currentNode->getIdx() + 1)) && !(isTopRight || isRightEdge || isBottomRight)){
            //     fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNextRightDistance();
            // }

            // // Node is NEXT45UP and is not a Left Top / Top Edge /  OR Right Top/Edge/Bottom node 
            // else if((neighbourIdx == (smallestDistanceNode->boardIdx - indexIncrements + 1)) && !(isTopLeft || isTopEdge || isTopRight || isRightEdge || isBottomRight)){
            //     fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNext45UpDistance();
            // }

            // // Node is UP and is not Left Top / Top Edge / Right Top node
            // else if((neighbourIdx == (smallestDistanceNode->boardIdx - indexIncrements)) && !(isTopLeft || isTopRight || isTopEdge)){
            //     fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNextUpDistance();
            // }

            // // Node is PREV45UP and is not Left Top/Bottom/Edge or Right Top
            // else if((neighbourIdx == (smallestDistanceNode->boardIdx - indexIncrements - 1)) && !(isTopLeft || isBottomLeft || isLeftEdge || isTopRight)){
            //     fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getPrev45UpDistance();
            // }

            // // Node is PrevLeft and is not Left Top/Bottom/Edge
            // else if((neighbourIdx == (smallestDistanceNode->boardIdx - 1)) && !(isLeftEdge || isTopLeft || isBottomLeft)){
            //     fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getPrevLeftDistance();
            // }

            // // Node is PREV45Down and is not Right Bottom or Left Top/Edge/Bottom or Bottom Edge
            // else if((neighbourIdx == (smallestDistanceNode->boardIdx + indexIncrements - 1)) && !(isBottomRight || isTopLeft || isLeftEdge || isBottomLeft || isBottomEdge)){
            //     fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getPrev45DownDistance();
            // }

            // // Node is Down and is not a bottom edge / left/right
            // else if((neighbourIdx == (smallestDistanceNode->boardIdx + indexIncrements)) && !(isBottomEdge || isBottomLeft || isBottomRight)){
            //     fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNextDownDistance();
            // }

            // // Node is Next45Down and is not Right Top/Edge/Botom or Bottom Edge/Left/Right
            // else if((neighbourIdx == (smallestDistanceNode->boardIdx + indexIncrements + 1)) && !(isTopRight || isRightEdge || isBottomRight || isBottomEdge || isBottomLeft || isBottomRight)){
            //     fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNext45DownDistance();
            // }


            if(openNodesIdx[neighbour->getIdx()] == 0){

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


            appControls->renderCells();
            appControls->displayInterface();

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
