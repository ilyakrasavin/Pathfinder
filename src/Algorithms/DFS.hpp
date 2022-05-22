#include "../Graph.hpp"
#include <vector>
#include <stack>
#include <iostream>

#include <random>

bool DepthFirstSearch(Graph* graph, sf::RenderWindow& windowRef){

    shared_ptr<Node> startNode = graph->getStartNode();
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
            temp->getCellRef()->setTexture("../assets-static/cell-neighbour.jpg");

        }

        for(auto each: graph->nodeMatrix){
            each->getCellRef()->render(windowRef);
        }
        windowRef.display();


        if(temp->isTarget()){
            cout<<"Found target!"<<endl;
            return true;
        }

        // shared_ptr<Node> nextRight = temp->getNextRight();
        // shared_ptr<Node> next45up = temp->getNext45up();
        // shared_ptr<Node> nextUp = temp->getNextUp();
        // shared_ptr<Node> prev45up = temp->getPrev45up();
        // shared_ptr<Node> prevLeft = temp->getPrevLeft();
        // shared_ptr<Node> prev45down = temp->getPrev45down();
        // shared_ptr<Node> nextDown = temp->getNextDown();
        // shared_ptr<Node> next45down = temp->getNext45down();

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
            
            if(adjacent[randomIdx] != nullptr && !adjacent[randomIdx]->isExplored()){
                toExplore.push(adjacent[randomIdx]);
                adjacent[randomIdx] = nullptr;
            }

            traversedCount++;

        }



    }


    return false;
}


