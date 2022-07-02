#include "Djkstra.hpp"


// function Dijkstra(Graph, source):
// 2      dist[source] ← 0                           // Initialization
// 3
// 4      create vertex priority queue Q
// 5
// 6      for each vertex v in Graph.Vertices:
// 7          if v ≠ source
// 8              dist[v] ← INT32_MAX                 // Unknown distance from source to v
// 9              prev[v] ← UNDEFINED                // Predecessor of v
// 10
// 11         Q.add_with_priority(v, dist[v])
// 12
// 13
// 14     while Q is not empty:                      // The main loop
// 15         u ← Q.extract_min()                    // Remove and return best vertex
// 16         for each neighbor v of u:              // only v that are still in Q
// 17             alt ← dist[u] + Graph.Edges(u, v)
// 18             if alt < dist[v] and dist[u] is not INT32_MAX:
// 19                 dist[v] ← alt
// 20                 prev[v] ← u
// 21                 Q.decrease_priority(v, alt)
// 22
// 23     return dist, prev



//////////////////////////////////////////////////
// IMPLEMENT FIBONACCI QUEUE??
//////////////////////////////////////////////////

struct exploredDjkstra{

    int boardIdx;
    int parentIdx;

    int distanceTo;

};



struct CompareDistance {
    bool operator()(shared_ptr<exploredDjkstra> p1, shared_ptr<exploredDjkstra> p2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return p1->distanceTo > p2->distanceTo;
    }
};


bool Djkstra(Application* appControls){

    cout<<"Entered Djkstra"<<endl;


    int indexIncrements = 20;
    int matrixSize = appControls->getWGraphRef()->getMatrixSize();

    shared_ptr<NodeExp> currentNode = appControls->getWGraphRef()->getStartNode();


    // Priority Queue
    std::priority_queue<shared_ptr<exploredDjkstra>, vector<shared_ptr<exploredDjkstra>>, CompareDistance> distanceQueue;

    // Current Source to Node distances for every Node
    vector<shared_ptr<exploredDjkstra>> distances;
    

    // Initialize the Distance Trackers & Min-Queue
    for(int i = 0; i < appControls->getWGraphRef()->getMatrixSize(); i++){

        shared_ptr<exploredDjkstra> exploredNode = make_shared<exploredDjkstra>();

        exploredNode->boardIdx = i;
        exploredNode->distanceTo = (i == currentNode->getIdx()) ? 0 : INT32_MAX;

        cout<<"Distance set to "<<exploredNode->distanceTo<<endl;

        distances.push_back(exploredNode);
        distanceQueue.push(exploredNode);

    }


    for(auto each: distances){
        cout<<&each.get()->boardIdx<<endl;
    }


    cout<<"Distance Initialization complete. Size of a vector is: "<<distances.size()<<endl;

    while(!distanceQueue.empty()){

        // Extracts the element with minimal distance
        shared_ptr<exploredDjkstra> smallestDistanceNode = distanceQueue.top();
        distanceQueue.pop();

        vector<shared_ptr<NodeExp>> neighbourNodes;

        neighbourNodes.push_back(appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNextRight());
        neighbourNodes.push_back(appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNext45up());
        neighbourNodes.push_back(appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNextUp());
        neighbourNodes.push_back(appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getPrev45up());
        neighbourNodes.push_back(appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getPrevLeft());
        neighbourNodes.push_back(appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getPrev45down());
        neighbourNodes.push_back(appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNextDown());
        neighbourNodes.push_back(appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNext45down());


        cout<<"Traversing neighbours"<<endl;

        for(auto each: neighbourNodes){

            // Fill the node relative to the smallestDistanceNode

            // Determine the direction of a neighbour node:
            // Compute by index
            //
            // Compute full-distance in the correct direction
            //

            if(each == nullptr){
                continue;
            }


            cout<<"Traversing neighbour"<<endl;

            int fullDistance;
            int neighbourIdx = each->getIdx();
            
            cout<<"computing boolean checks"<<endl;

            // Boolean Location 
            // Ranges are exclusive of endpoints
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

            cout<<"Boolean checks computed"<<endl;

            // Node is NextRight and Node is not a Right Top/Bottom/Edge Node
            if((neighbourIdx == (smallestDistanceNode->boardIdx + 1)) && !(isTopRight || isRightEdge || isBottomRight)){
                fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNextRightDistance();
            }

            // Node is NEXT45UP and is not a Left Top / Top Edge /  OR Right Top/Edge/Bottom node 
            else if((neighbourIdx == (smallestDistanceNode->boardIdx - indexIncrements + 1)) && !(isTopLeft || isTopEdge || isTopRight || isRightEdge || isBottomRight)){
                fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNext45UpDistance();
            }

            // Node is UP and is not Left Top / Top Edge / Right Top node
            else if((neighbourIdx == (smallestDistanceNode->boardIdx - indexIncrements)) && !(isTopLeft || isTopRight || isTopEdge)){
                fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNextUpDistance();
            }

            // Node is PREV45UP and is not Left Top/Bottom/Edge or Right Top
            else if((neighbourIdx == (smallestDistanceNode->boardIdx - indexIncrements - 1)) && !(isTopLeft || isBottomLeft || isLeftEdge || isTopRight)){
                fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getPrev45UpDistance();
            }

            // Node is PrevLeft and is not Left Top/Bottom/Edge
            else if((neighbourIdx == (smallestDistanceNode->boardIdx - 1)) && !(isLeftEdge || isTopLeft || isBottomLeft)){
                fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getPrevLeftDistance();
            }

            // Node is PREV45Down and is not Right Bottom or Left Top/Edge/Bottom or Bottom Edge
            else if((neighbourIdx == (smallestDistanceNode->boardIdx + indexIncrements - 1)) && !(isBottomRight || isTopLeft || isLeftEdge || isBottomLeft || isBottomEdge)){
                fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getPrev45DownDistance();
            }

            // Node is Down and is not a bottom edge / left/right
            else if((neighbourIdx == (smallestDistanceNode->boardIdx + indexIncrements)) && !(isBottomEdge || isBottomLeft || isBottomRight)){
                fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNextDownDistance();
            }

            // Node is Next45Down and is not Right Top/Edge/Botom or Bottom Edge/Left/Right
            else if((neighbourIdx == (smallestDistanceNode->boardIdx + indexIncrements + 1)) && !(isTopRight || isRightEdge || isBottomRight || isBottomEdge || isBottomLeft || isBottomRight)){
                fullDistance = smallestDistanceNode->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getNext45DownDistance();
            }


            cout<<"Node determined and fullDistance computed"<<endl;
            cout<<"Comparing new distance"<<endl;

            cout<<"Fulldistance set to: "<<fullDistance<<endl;
            cout<<"Neighbour Index is: "<<neighbourIdx<<endl;
            cout<<"Recorded distance to Neigbour is: "<<distances[neighbourIdx].get()->distanceTo<<endl;
            cout<<"Is Recorded distance to Origin equal to INT32_MAX? "<<(smallestDistanceNode->distanceTo != INT32_MAX)<<endl;

            /////////////////////////////////////////////////
            // Compare the distance on newfound path with distance previously in the list
            /////////////////////////////////////////////////
            if((fullDistance < distances.at(neighbourIdx)->distanceTo) && (smallestDistanceNode->distanceTo != INT32_MAX)){

                cout<<"If check performed"<<endl;

                distances.at(neighbourIdx)->distanceTo = fullDistance;
                distances.at(neighbourIdx)->parentIdx = smallestDistanceNode->boardIdx;

                // update the distance queue with node of lower priority
                distanceQueue.push(distances.at(neighbourIdx));

                // neighbour->getCellRef()->setExplored();
                each->getCellRef()->setTexture("../assets-static/node-neighbour.jpg");
                each->getCellRef()->setScore(fullDistance, neighbourIdx);

                appControls->renderCells();
                appControls->displayInterface();
            }
            /////////////////////////////////////////////////

            else{
                continue;
            }

        }

        appControls->renderCells();
        appControls->displayInterface();


    }


// while Q is not empty:                      // The main loop
// 15         u ← Q.extract_min()                    // Remove and return best vertex
// 16         for each neighbor v of u:              // only v that are still in Q
// 17             alt ← dist[u] + Graph.Edges(u, v)
// 18             if alt < dist[v] and dist[u] is not INT32_MAX:
// 19                 dist[v] ← alt
// 20                 prev[v] ← u
// 21                 Q.decrease_priority(v, alt)



    return false;
}








