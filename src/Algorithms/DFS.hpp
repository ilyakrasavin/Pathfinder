#include "../Graph.hpp"
#include <vector>
#include <stack>
#include <iostream>

bool DepthFirstSearch(Graph* graph, sf::RenderWindow& windowRef){

    shared_ptr<Node> startNode = graph->getStartNode();
    stack<shared_ptr<Node>> toExplore;

    toExplore.push(startNode);

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

        shared_ptr<Node> nextRight = temp->getNextRight();
        if(nextRight != nullptr && !nextRight->isExplored()){
            toExplore.push(nextRight);
        }

        shared_ptr<Node> next45up = temp->getNext45up();
        if(next45up != nullptr && !next45up->isExplored()){
            toExplore.push(next45up);
        }

        
        shared_ptr<Node> nextUp = temp->getNextUp();
        if(nextUp != nullptr && !nextUp->isExplored()){
            toExplore.push(nextUp);
        }

        shared_ptr<Node> prev45up = temp->getPrev45up();
        if(prev45up != nullptr && !prev45up->isExplored()){
            toExplore.push(prev45up);
        }

        shared_ptr<Node> prevLeft = temp->getPrevLeft();
        if(prevLeft != nullptr && !prevLeft->isExplored()){
            toExplore.push(prevLeft);
        }

        shared_ptr<Node> prev45down = temp->getPrev45down();
        if(prev45down != nullptr && !prev45down->isExplored()){
            toExplore.push(prev45down);
        }

        shared_ptr<Node> nextDown = temp->getNextDown();
        if(nextDown != nullptr && !nextDown->isExplored()){
            toExplore.push(nextDown);
        }

        shared_ptr<Node> next45down = temp->getNext45down();
        if(next45down != nullptr && !next45down->isExplored()){
            toExplore.push(next45down);
        }


    }


    return false;
}


