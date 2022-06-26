#include "Djkstra.hpp"


// function Dijkstra(Graph, source):
// 2      dist[source] ← 0                           // Initialization
// 3
// 4      create vertex priority queue Q
// 5
// 6      for each vertex v in Graph.Vertices:
// 7          if v ≠ source
// 8              dist[v] ← INFINITY                 // Unknown distance from source to v
// 9              prev[v] ← UNDEFINED                // Predecessor of v
// 10
// 11         Q.add_with_priority(v, dist[v])
// 12
// 13
// 14     while Q is not empty:                      // The main loop
// 15         u ← Q.extract_min()                    // Remove and return best vertex
// 16         for each neighbor v of u:              // only v that are still in Q
// 17             alt ← dist[u] + Graph.Edges(u, v)
// 18             if alt < dist[v] and dist[u] is not INFINITY:
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


    shared_ptr<NodeExp> currentNode = appControls->getWGraphRef()->getStartNode();


    // Priority Queue
    std::priority_queue<shared_ptr<exploredDjkstra>, vector<shared_ptr<exploredDjkstra>>, CompareDistance> distanceQueue;

    // Current Source to Node distances for every Node
    vector<shared_ptr<exploredDjkstra>> distances(appControls->getWGraphRef()->getMatrixSize());
    


    // Initialize the Distance Trackers & Min-Queue
    for(int i = 0; i < appControls->getWGraphRef()->getMatrixSize(); i++){

        shared_ptr<exploredDjkstra> exploredNode = make_shared<exploredDjkstra>();

        exploredNode->boardIdx = i;
        exploredNode->distanceTo = (i == currentNode->getIdx()) ? 0 : INFINITY;

        distances.push_back(exploredNode);
        distanceQueue.push(exploredNode);

    }

    cout<<"Distance Initialization complete"<<endl;

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


        for(auto each: neighbourNodes){

            int fullDistance = distances.at(each->getIdx())->distanceTo + appControls->getWGraphRef()->nodeMatrix.at(smallestDistanceNode->boardIdx)->getPrevLeftDistance();

            if(fullDistance < distances.at(each->getIdx())->distanceTo && smallestDistanceNode->distanceTo != INFINITY){

                distances.at(each->getIdx())->distanceTo = fullDistance;
                distances.at(each->getIdx())->parentIdx = smallestDistanceNode->boardIdx;

                // update the distance queue with node of lower priority
                distanceQueue.push(distances.at(each->getIdx()));

                // neighbour->getCellRef()->setExplored();
                each->getCellRef()->setTexture("../assets-static/node-neighbour.jpg");
                each->getCellRef()->setScore(fullDistance, each->getIdx());

            }

        }

        appControls->renderCells();
        appControls->displayInterface();


    }


// while Q is not empty:                      // The main loop
// 15         u ← Q.extract_min()                    // Remove and return best vertex
// 16         for each neighbor v of u:              // only v that are still in Q
// 17             alt ← dist[u] + Graph.Edges(u, v)
// 18             if alt < dist[v] and dist[u] is not INFINITY:
// 19                 dist[v] ← alt
// 20                 prev[v] ← u
// 21                 Q.decrease_priority(v, alt)



    return false;
}








