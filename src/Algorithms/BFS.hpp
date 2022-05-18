#include "../Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

bool BreadthFirstSearch(Graph* graph, sf::RenderWindow* windowRef){

// Run the algorithm AND perform rendering within the algoritm

// ASSURE no retraction is happenning (No backwards exporation -> Nodes marked visited)

    // Begin with the Start Node
    Node* currentNode = graph->getStartNode();

    vector<Node*> explored;
    queue<Node*> children_queue;

    // Push the Non-explored children of a node into a queue (if exist)
    // Pop the first child off the queue -> Make it a current node -> Add to explored array
    // Push the Non-explored children of a node into a queue (if exist)
    // Pop the second child of a root off the queue -> Make current ... -> Add to explored array
    // ...


    while(true){


        Node* nextRight = currentNode->getNextRight();
        // Adjacent Node Exists
        if(nextRight != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!nextRight->isExplored() && !nextRight->isWall()){
                cout<<"Pushed Next Right child into the queue"<<endl;
                children_queue.push(nextRight);

                // Render as Being Looked At

            }
            else if(nextRight->isExplored()){
                cout<<"Next Right Child already explored"<<endl;
            }
            else if(nextRight->isWall()){
                cout<<"Next Right Cell is an obstacle, can not explore!"<<endl;
            }
            else if(nextRight->isTarget()){
                cout<<"Target Found!"<<endl;
                // Render as Target
                return true;
            }
        }
        else{
            cout<<"Next Right Cell does not exist!"<<endl;
        }



        Node* prevLeft = currentNode->getPrevLeft();
        // Adjacent Node Exists
        if(prevLeft != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!prevLeft->isExplored() && !prevLeft->isWall()){
                cout<<"Pushed Prev Left child into the queue"<<endl;
                children_queue.push(prevLeft);

                // Render as Being Looked At

            }
            else if(prevLeft->isExplored()){
                cout<<"Prev Left Child already explored"<<endl;
            }
            else if(prevLeft->isWall()){
                cout<<"Prev Left Cell is an obstacle, can not explore!"<<endl;
            }
            else if(prevLeft->isTarget()){
                cout<<"Target Found!"<<endl;
                // Render as Target
                return true;
            }            
            
        }
        else{
            cout<<"Prev Left Cell does not exist!"<<endl;
        }



        Node* nextUp = currentNode->getNextUp();
        // Adjacent Node Exists
        if(nextUp != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!nextUp->isExplored() && !nextUp->isWall()){
                cout<<"Pushed Next Up child into the queue"<<endl;
                children_queue.push(nextUp);

                // Render as Being Looked At

            }
            else if(nextUp->isExplored()){
                cout<<"Next Up Child already explored"<<endl;
            }
            else if(nextUp->isWall()){
                cout<<"Next Up Cell is an obstacle, can not explore!"<<endl;
            }
            else if(nextUp->isTarget()){
                cout<<"Target Found!"<<endl;
                // Render as Target
                return true;
            }           
        }
        else{
            cout<<"Next Up Cell does not exist!"<<endl;
        }



        Node* nextDown = currentNode->getNextDown();
        // Adjacent Node Exists
        if(nextDown != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!nextDown->isExplored() && !nextDown->isWall()){
                cout<<"Pushed Next Down child into the queue"<<endl;
                children_queue.push(nextDown);

                // Render as Being Looked At

            }
            else if(nextDown->isExplored()){
                cout<<"Next Down Child already explored"<<endl;
            }
            else if(nextDown->isWall()){
                cout<<"Next Down Cell is an obstacle, can not explore!"<<endl;
            }
            else if(nextDown->isTarget()){
                cout<<"Target Found!"<<endl;
                // Render as Target
                return true;
            }            
        }
        else{
            cout<<"Next Down Cell does not exist!"<<endl;
        }



        Node* prev45up = currentNode->getPrev45up();
        // Adjacent Node Exists
        if(prev45up != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!prev45up->isExplored() && !prev45up->isWall()){
                cout<<"Pushed Prev 45Up child into the queue"<<endl;
                children_queue.push(prev45up);

                // Render as Being Looked At

            }
            else if(prev45up->isExplored()){
                cout<<"Prev 45Up Child already explored"<<endl;
            }
            else if(prev45up->isWall()){
                cout<<"Prev 45Up Cell is an obstacle, can not explore!"<<endl;
            }
            else if(prev45up->isTarget()){
                cout<<"Target Found!"<<endl;
                // Render as Target
                return true;
            }
        }
        else{
            cout<<"Prev 45Up Cell does not exist!"<<endl;
        }




        Node* next45up = currentNode->getNext45up();
        // Adjacent Node Exists
        if(next45up != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!next45up->isExplored() && !next45up->isWall()){
                cout<<"Pushed Next 45 Up child into the queue"<<endl;
                children_queue.push(next45up);

                // Render as Being Looked At

            }
            else if(next45up->isExplored()){
                cout<<"Next 45 Up Child already explored"<<endl;
            }
            else if(next45up->isWall()){
                cout<<"Next 45 Up Cell is an obstacle, can not explore!"<<endl;
            }
            else if(next45up->isTarget()){
                cout<<"Target Found!"<<endl;
                // Render as Target
                return true;
            }
        }
        else{
            cout<<"Next 45 Up Cell does not exist!"<<endl;
        }



        Node* prev45down = currentNode->getPrev45down();
        // Adjacent Node Exists
        if(prev45down != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!prev45down->isExplored() && !prev45down->isWall()){
                cout<<"Pushed Prev 45 Down child into the queue"<<endl;
                children_queue.push(prev45down);

                // Render as Being Looked At

            }
            else if(prev45down->isExplored()){
                cout<<"Prev 45 Down Child already explored"<<endl;
            }
            else if(prev45down->isWall()){
                cout<<"Prev 45 Down Cell is an obstacle, can not explore!"<<endl;
            }
            else if(prev45down->isTarget()){
                cout<<"Target Found!"<<endl;
                // Render as Target
                return true;
            }
        }
        else{
            cout<<"Prev 45 Down Cell does not exist!"<<endl;
        }


        Node* next45down = currentNode->getNext45down();
        // Adjacent Node Exists
        if(next45down != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!next45down->isExplored() && !next45down->isWall()){
                cout<<"Pushed Next 45 Down child into the queue"<<endl;
                children_queue.push(next45down);

                // Render as Being Looked At

            }
            else if(next45down->isExplored()){
                cout<<"Next 45 Down Child already explored"<<endl;
            }
            else if(next45down->isWall()){
                cout<<"Next 45 Down Cell is an obstacle, can not explore!"<<endl;
            }
            else if(next45down->isTarget()){
                cout<<"Target Found!"<<endl;
                // Render as Target
                return true;
            }
        }
        else{
            cout<<"Next 45 Down Cell does not exist!"<<endl;
        }



        // Mark current node as explored
        explored.push_back(currentNode);
        
        // Render as Explored
        //


        // Queue is empty! Done
        if(children_queue.empty()){
            break;
        }

        // Dequeue the element off the queue and make it current -> Repeat
        currentNode = children_queue.front();
        children_queue.pop();

    }



    return false;
}