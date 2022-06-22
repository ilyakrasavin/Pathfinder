#include "BFS.hpp"

bool BreadthFirstSearch(Graph* graph, shared_ptr<sf::RenderWindow> windowRef){
// ASSURE no retraction is happenning (No backwards exporation -> Nodes marked visited)

    cout<<"Entered BFS"<<endl;

    // Begin with the Start Node
    shared_ptr<Node> currentNode = graph->getStartNode();

    vector<shared_ptr<Node>> explored;
    queue<shared_ptr<Node>> children_queue;

    // Push the Non-explored children of a node into a queue (if exist)
    // Pop the first child off the queue -> Make it a current node -> Add to explored array
    // Push the Non-explored children of a node into a queue (if exist)
    // Pop the second child of a root off the queue -> Make current ... -> Add to explored array
    // ...

    cout<<"BFS Started with node at position: "<<currentNode->getIdx()<<endl;

    while(true){


        if(currentNode->getCellRef()->checkIsTarget()){
            cout<<"target found @ "<<currentNode->getIdx()<<endl;
            return true;
        }

        if(currentNode->getCellRef()->checkIsWall()){
            cout<<"I AM A WALL!!"<<endl;
        }


        shared_ptr<Node> nextRight = currentNode->getNextRight();
        
        // Adjacent Node Exists
        if(nextRight != nullptr){

            // Adjacent node not previously explored & is not a Wall
            if(!nextRight->isExplored() && !nextRight->getCellRef()->checkIsWall()){

                if(nextRight->isTarget()){
                    cout<<"Target Found!"<<endl;
                    // Render as Target
                    return true;
                }

                nextRight->setExplored();
                cout<<"Pushed Next Right child into the queue"<<endl;
                children_queue.push(nextRight);

                // Render as Being Looked At
                nextRight->getCellRef()->setTexture("../assets-static/node-neighbour.jpg");

            }
            else if(nextRight->isExplored()){
                cout<<"Next Right Child already explored"<<endl;
            }
            else if(nextRight->getCellRef()->checkIsWall()){
                cout<<"Next Right Cell is an obstacle, can not explore!"<<endl;
                nextRight->getCellRef()->setTexture("assets-static/node-wall.jpg");
            }

        }
        else{
            cout<<"Next Right Cell does not exist!"<<endl;
        }



        shared_ptr<Node> next45up = currentNode->getNext45up();
        // Adjacent Node Exists
        if(next45up != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!next45up->isExplored() && !next45up->getCellRef()->checkIsWall()){

                if(next45up->isTarget()){
                    cout<<"Target Found!"<<endl;
                    // Render as Target
                    return true;
                }
                
                next45up->setExplored();
                cout<<"Pushed Next 45 Up child into the queue"<<endl;
                children_queue.push(next45up);

                // Render as Being Looked At
                next45up->getCellRef()->setTexture("../assets-static/node-neighbour.jpg");

            }
            else if(next45up->isExplored()){
                cout<<"Next 45 Up Child already explored"<<endl;
            }
            else if(next45up->getCellRef()->checkIsWall()){
                cout<<"Next 45 Up Cell is an obstacle, can not explore!"<<endl;
                next45up->getCellRef()->setTexture("assets-static/node-wall.jpg");

            }

        }
        else{
            cout<<"Next 45 Up Cell does not exist!"<<endl;
        }




        shared_ptr<Node> nextUp = currentNode->getNextUp();
        // Adjacent Node Exists
        if(nextUp != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!nextUp->isExplored() && !nextUp->getCellRef()->checkIsWall()){

                if(nextUp->isTarget()){
                    cout<<"Target Found!"<<endl;
                    // Render as Target
                    return true;
                }    

                nextUp->setExplored();
                cout<<"Pushed Next Up child into the queue"<<endl;
                children_queue.push(nextUp);

                // Render as Being Looked At
                nextUp->getCellRef()->setTexture("../assets-static/node-neighbour.jpg");

            }
            else if(nextUp->isExplored()){
                cout<<"Next Up Child already explored"<<endl;
            }
            else if(nextUp->getCellRef()->checkIsWall()){
                cout<<"Next Up Cell is an obstacle, can not explore!"<<endl;
                nextUp->getCellRef()->setTexture("assets-static/node-wall.jpg");

            }
       
        }
        else{
            cout<<"Next Up Cell does not exist!"<<endl;
        }



        shared_ptr<Node> prev45up = currentNode->getPrev45up();
        // Adjacent Node Exists
        if(prev45up != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!prev45up->isExplored() && !prev45up->getCellRef()->checkIsWall()){

                if(prev45up->isTarget()){
                    cout<<"Target Found!"<<endl;
                    // Render as Target
                    return true;
                }

                prev45up->setExplored();

                cout<<"Pushed Prev 45Up child into the queue"<<endl;
                children_queue.push(prev45up);

                // Render as Being Looked At
                prev45up->getCellRef()->setTexture("../assets-static/node-neighbour.jpg");

            }
            else if(prev45up->isExplored()){
                cout<<"Prev 45Up Child already explored"<<endl;
            }
            else if(prev45up->getCellRef()->checkIsWall()){
                cout<<"Prev 45Up Cell is an obstacle, can not explore!"<<endl;
                prev45up->getCellRef()->setTexture("assets-static/node-wall.jpg");
            }

        }
        else{
            cout<<"Prev 45Up Cell does not exist!"<<endl;
        }



        shared_ptr<Node> prevLeft = currentNode->getPrevLeft();
        // Adjacent Node Exists
        if(prevLeft != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!prevLeft->isExplored() && !prevLeft->getCellRef()->checkIsWall()){

                if(prevLeft->isTarget()){
                    cout<<"Target Found!"<<endl;
                    // Render as Target
                    return true;
                }    

                prevLeft->setExplored();
                cout<<"Pushed Prev Left child into the queue"<<endl;
                children_queue.push(prevLeft);

                // Render as Being Looked At
                prevLeft->getCellRef()->setTexture("../assets-static/node-neighbour.jpg");


            }
            else if(prevLeft->isExplored()){
                cout<<"Prev Left Child already explored"<<endl;
            }
            else if(prevLeft->getCellRef()->checkIsWall()){
                cout<<"Prev Left Cell is an obstacle, can not explore!"<<endl;
                prevLeft->getCellRef()->setTexture("assets-static/node-wall.jpg");

            }
            
        }
        else{
            cout<<"Prev Left Cell does not exist!"<<endl;
        }




        shared_ptr<Node> prev45down = currentNode->getPrev45down();
        // Adjacent Node Exists
        if(prev45down != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!prev45down->isExplored() && !prev45down->getCellRef()->checkIsWall()){

                if(prev45down->isTarget()){
                    cout<<"Target Found!"<<endl;
                    // Render as Target
                    return true;
                }

                prev45down->setExplored();
                cout<<"Pushed Prev 45 Down child into the queue"<<endl;
                children_queue.push(prev45down);

                // Render as Being Looked At
                prev45down->getCellRef()->setTexture("../assets-static/node-neighbour.jpg");


            }
            else if(prev45down->isExplored()){
                cout<<"Prev 45 Down Child already explored"<<endl;
            }
            else if(prev45down->getCellRef()->checkIsWall()){
                cout<<"Prev 45 Down Cell is an obstacle, can not explore!"<<endl;
                prev45down->getCellRef()->setTexture("assets-static/node-wall.jpg");
            }

        }
        else{
            cout<<"Prev 45 Down Cell does not exist!"<<endl;
        }



        shared_ptr<Node> nextDown = currentNode->getNextDown();
        // Adjacent Node Exists
        if(nextDown != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!nextDown->isExplored() && !nextDown->getCellRef()->checkIsWall()){

                if(nextDown->isTarget()){
                    cout<<"Target Found!"<<endl;
                    // Render as Target
                    return true;
                }      

                nextDown->setExplored();

                cout<<"Pushed Next Down child into the queue"<<endl;
                children_queue.push(nextDown);

                // Render as Being Looked At
                nextDown->getCellRef()->setTexture("../assets-static/node-neighbour.jpg");


            }
            else if(nextDown->isExplored()){
                cout<<"Next Down Child already explored"<<endl;
            }
            else if(nextDown->getCellRef()->checkIsWall()){
                cout<<"Next Down Cell is an obstacle, can not explore!"<<endl;
                nextDown->getCellRef()->setTexture("assets-static/node-wall.jpg");

            }
      
        }
        else{
            cout<<"Next Down Cell does not exist!"<<endl;
        }


        shared_ptr<Node> next45down = currentNode->getNext45down();
        // Adjacent Node Exists
        if(next45down != nullptr){
            // Adjacent node not previously explored & is not a Wall
            if(!next45down->isExplored() && !next45down->getCellRef()->checkIsWall()){

                if(next45down->isTarget()){
                    cout<<"Target Found!"<<endl;
                    // Render as Target
                    return true;
                }

                next45down->setExplored();
                cout<<"Pushed Next 45 Down child into the queue"<<endl;
                children_queue.push(next45down);

                // Render as Being Looked At
                next45down->getCellRef()->setTexture("../assets-static/node-neighbour.jpg");


            }
            else if(next45down->isExplored()){
                cout<<"Next 45 Down Child already explored"<<endl;
            }
            else if(next45down->getCellRef()->checkIsWall()){
                cout<<"Next 45 Down Cell is an obstacle, can not explore!"<<endl;
                next45down->getCellRef()->setTexture("assets-static/node-wall.jpg");

            }

        }
        else{
            cout<<"Next 45 Down Cell does not exist!"<<endl;
        }


        // Mark current node as explored
        
        explored.push_back(currentNode);
        currentNode->setExplored();
        currentNode->getCellRef()->setTexture("../assets-static/node-start.jpg");

        cout<<"Nodes explored: "<<explored.size()<<endl;

        // Render the board cells ONLY
        for(auto each: graph->nodeMatrix){
            each->getCellRef()->render(windowRef);
        }

        windowRef->display();



        // Queue is empty! Done
        if(children_queue.empty()){
            break;
        }

        // Dequeue the element off the queue and make it current -> Repeat
        currentNode = children_queue.front();
        children_queue.pop();

        cout<<"# of Elements in the Children Queue: "<<children_queue.size()<<endl;

    }


    return false;
}

