#include "DFS.hpp"

bool DepthFirstSearch(Application* appControls){

    shared_ptr<Node> startNode = appControls->getGraphRef()->getStartNode();
    std::vector<std::shared_ptr<Node>> nodeMatrixLocal = appControls->getGraphRef()->nodeMatrix;
    std::shared_ptr<sf::RenderWindow> windowRef = appControls->getMainWindowRef();


    stack<shared_ptr<Node>> toExplore;

    toExplore.push(startNode);

    random_device randomNum;

    // Randomize the branch choice

    while(!toExplore.empty()){

        shared_ptr<Node> temp = toExplore.top();
        toExplore.pop();

        cout<<"Now at node: "<<temp->getIdx()<<endl;
        cout<<"# Of nodes a stack is: "<<toExplore.size();

        if(!temp->isExplored()){
            
            temp->setExplored();
            temp->getCellRef()->setTexture("../assets-static/node-neighbour.jpg");

        }

        for(auto each: nodeMatrixLocal){
            each->getCellRef()->render(windowRef);
        }

        // appControls->renderCells();
        appControls->displayInterface();

        // windowRef->display();


        if(temp->isTarget()){
            cout<<"Found target!"<<endl;
            return true;
        }


        vector<shared_ptr<Node>> adjacent;
        adjacent.push_back(temp->getNextRight());
        adjacent.push_back(temp->getNext45up());
        adjacent.push_back(temp->getNextUp());
        adjacent.push_back(temp->getPrev45up());
        adjacent.push_back(temp->getPrevLeft());
        adjacent.push_back(temp->getPrev45down());
        adjacent.push_back(temp->getNextDown());
        adjacent.push_back(temp->getNext45down());


        int traversedCount = 0;

        while(traversedCount < 7){

            int randomIdx = randomNum() % (7 - traversedCount);
            
            if(adjacent[randomIdx] != nullptr && !adjacent[randomIdx]->isExplored() && !adjacent[randomIdx]->isWall()){
                toExplore.push(adjacent[randomIdx]);
                adjacent[randomIdx] = nullptr;
            }

            traversedCount++;

        }



    }


    return false;
}

