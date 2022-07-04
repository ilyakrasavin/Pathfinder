#include "Djkstra.hpp"


struct exploredDjkstra{

    int boardIdx;
    int parentIdx;

    int distanceTo;

};


struct CompareDistance {
    bool operator()(shared_ptr<pair<int, pair<int, int>>>& ptr1, shared_ptr<pair<int, pair<int, int>>>& ptr2)
    {

        // return "true" if "p1" is ordered
        // before "p2", for example:
        return ptr1->first < ptr2->first;
    }
};

////////////////////////////
// FIX: Distance changes after whole graph is traversed
////////////////////////////


bool Djkstra(Application* appControls){

    cout<<"Entered Djkstra"<<endl;


    int indexIncrements = 20;
    int matrixSize = appControls->getWGraphRef()->getMatrixSize();

    shared_ptr<NodeExp> currentNode = appControls->getWGraphRef()->getStartNode();

    // DOES NOT WORK (No sorting post initial stage)
    /////////////////////////////
    // Priority Queue
    // Stores a pair of Int and Pair <Int, Int> where:
    // First int is DistanceTo
    // Second pair is <Index, Parent Index>
    // std::priority_queue<shared_ptr<pair<int, pair<int, int>>>, vector<shared_ptr<pair<int, pair<int, int>>>>, CompareDistance> distanceQueue;
    /////////////////////////////


    /////////////////////////////
    // HEAP 
    vector<shared_ptr<pair<int, pair<int, int>>>> distanceHeap;
    make_heap(distanceHeap.begin(), distanceHeap.end(), CompareDistance());
    /////////////////////////////


    // Current Source to Node distances for every Node
    vector<shared_ptr<exploredDjkstra>> distances;
    

    // Initialize the Distance Trackers & Min-Queue
    for(int i = 0; i < appControls->getWGraphRef()->getMatrixSize(); i++){

        shared_ptr<exploredDjkstra> exploredNode = make_shared<exploredDjkstra>();

        if(appControls->getWGraphRef()->nodeMatrix.at(i)->getCellRef()->checkIsWall()){
            distances.push_back(nullptr);
            continue;
        }

        exploredNode->boardIdx = i;
        exploredNode->distanceTo = (i == currentNode->getIdx()) ? 0 : INT32_MAX;

        cout<<"Distance set to "<<exploredNode->distanceTo<<endl;

        distances.push_back(exploredNode);

        pair<int, int> indices = make_pair(exploredNode->boardIdx, exploredNode->parentIdx);
        pair<int, pair<int, int>> total = make_pair(exploredNode->distanceTo, indices);
        shared_ptr<pair<int, pair<int, int>>> newptr = make_shared<pair<int, pair<int, int>>>(total);
        distanceHeap.push_back(newptr);
        push_heap(distanceHeap.begin(), distanceHeap.end(), CompareDistance());

    }

    sort_heap(distanceHeap.begin(), distanceHeap.end(), CompareDistance());


    cout<<"Distance Initialization complete. Size of a vector is: "<<distances.size()<<endl;
    cout<<"Nodes in a priority queue: "<<distanceHeap.size()<<endl;

    while(!distanceHeap.empty()){

        cout<<"Extracting the top element off the queue..."<<endl;

        // Extracts the element with minimal distance

        pop_heap(distanceHeap.begin(), distanceHeap.end(), CompareDistance());
        const shared_ptr<exploredDjkstra> smallestDistanceNode = distances.at(distanceHeap.back()->second.first);
        distanceHeap.pop_back(); 
    
        sort_heap(distanceHeap.begin(), distanceHeap.end(), CompareDistance());           

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

            int fullDistance;
            int neighbourIdx = each->getIdx();

            cout<<"Traversing neighbour at index: "<<neighbourIdx<<endl;


            if(each == nullptr || distances.at(neighbourIdx) == nullptr){
                continue;
            }

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


            cout<<isTopLeft<<endl;
            cout<<isTopEdge<<endl;
            cout<<isTopRight<<endl;
            cout<<isLeftEdge<<endl;
            cout<<isRightEdge<<endl;
            cout<<isBottomLeft<<endl;
            cout<<isBottomEdge<<endl;
            cout<<isBottomRight<<endl;
            cout<<isMiddle<<endl;


            cout<<"Node determined and fullDistance computed"<<endl;
            cout<<"Comparing new distance"<<endl;

            cout<<"Fulldistance set to: "<<fullDistance<<endl;
            cout<<"Neighbour Index is: "<<neighbourIdx<<endl;
            cout<<"Recorded distance to Neigbour is: "<<distances.at(neighbourIdx)->distanceTo<<endl;
            cout<<"Is Recorded distance to Origin equal to INT32_MAX? "<<(smallestDistanceNode->distanceTo == INT32_MAX)<<endl;

            /////////////////////////////////////////////////
            // Compare the distance on newfound path with distance previously in the list
            /////////////////////////////////////////////////
            if((fullDistance < distances.at(neighbourIdx)->distanceTo) && (smallestDistanceNode->distanceTo != INT32_MAX)){

                cout<<"If check performed"<<endl;

                distances.at(neighbourIdx)->distanceTo = fullDistance;
                distances.at(neighbourIdx)->parentIdx = smallestDistanceNode->boardIdx;


                // update the distance queue with node of lower priority
                pair<int, int> indices = make_pair(neighbourIdx, distances.at(neighbourIdx)->parentIdx);
                pair<int, pair<int, int>> total = make_pair(fullDistance, indices);
                distanceHeap.push_back(make_shared<pair<int, pair<int, int>>>(total));
                push_heap(distanceHeap.begin(), distanceHeap.end(), CompareDistance());


                each->getCellRef()->setTexture("../assets-static/node-neighbour.jpg");
                each->getCellRef()->setScore(fullDistance, neighbourIdx);

                appControls->renderCells();
                appControls->displayInterface();

                // sort_heap(distanceHeap.begin(), distanceHeap.end(), CompareDistance());

            }
            /////////////////////////////////////////////////

            cout<<"If check completed"<<endl;
            sort_heap(distanceHeap.begin(), distanceHeap.end(), CompareDistance());


        }

        cout<<"Elements in a queue: "<<distanceHeap.size()<<endl;

        sort_heap(distanceHeap.begin(), distanceHeap.end(), CompareDistance());


        appControls->renderCells();
        appControls->displayInterface();


    }


    return false;
}

