#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Interface.hpp"


using namespace std;



class Node{

    public:
        // Default constructor
        Node(shared_ptr<mapCell> reference, int index, bool isStartIn, bool isWallIn, bool isExploredIn, bool isTargetIn){

            this->cellRef = reference;

            isStartNode = isStartIn;
            isWallNode = isWallIn;
            isExploredNode = isExploredIn;
            isTargetNode = isTargetIn;

            setIdx(index);

            nextRight = nullptr;
            prevLeft = nullptr;
            nextUp = nullptr;
            nextDown = nullptr;
            prev45up = nullptr;
            next45up = nullptr;
            prev45down = nullptr;
            next45down = nullptr;

            nextRightWeight = 0;
            prevLeftWeight = 0;
            nextUpWeight = 0;
            nextDownWeight = 0;
            prev45UpWeight = 0;
            next45UpWeight = 0;
            prev45DownWeight = 0;
            next45DownWeight = 0;

            nextRightDistance = 0;
            prevLeftDistance = 0;
            nextUpDistance = 0;
            nextDownDistance = 0;
            prev45UpDistance = 0;
            next45UpDistance = 0;
            prev45DownDistance = 0;
            next45DownDistance = 0;

        }
         

        // Node Connection setters
        void setNextRight(shared_ptr<Node> nextRight){this->nextRight = nextRight;}
        void setPrevLeft(shared_ptr<Node> prevLeft){this->prevLeft = prevLeft;}
        void setNextUp(shared_ptr<Node> nextUp){this->nextUp = nextUp;}
        void setNextDown(shared_ptr<Node> nextDown){this->nextDown = nextDown;}
        void setPrev45up(shared_ptr<Node> prev45up){this->prev45up = prev45up;}
        void setNext45up(shared_ptr<Node> next45up){this->next45up = next45up;}
        void setPrev45down(shared_ptr<Node> prev45down){this->prev45down = prev45down;}
        void setNext45down(shared_ptr<Node> next45down){this->next45down = next45down;}

        // Node connection getters
        shared_ptr<Node> getNextRight(){return nextRight;}
        shared_ptr<Node> getPrevLeft(){return prevLeft;}
        shared_ptr<Node> getNextUp(){return nextUp;}
        shared_ptr<Node> getNextDown(){return nextDown;}
        shared_ptr<Node> getPrev45up(){return prev45down;}
        shared_ptr<Node> getNext45up(){return next45up;}
        shared_ptr<Node> getPrev45down(){return prev45down;}
        shared_ptr<Node> getNext45down(){return next45down;}

        // Attribute check
        bool isExplored(){return isExploredNode;}        
        bool isStart(){return isStartNode;}
        bool isWall(){return isWallNode;}
        bool isTarget(){return isTargetNode;}
        int getIdx(){return mapIdx;}


        shared_ptr<mapCell> getCellRef();

        // Attribure setters
        void setExplored(){isExploredNode = true;}
        void setIdx(int idx){mapIdx = idx;}

        ~Node(){};

    private:
        // Reference to a cell in a Render-able map
        shared_ptr<mapCell> cellRef;

        int mapIdx;

        // Neighboring Nodes
        shared_ptr<Node> nextRight;
        shared_ptr<Node> prevLeft;
        shared_ptr<Node> nextUp;
        shared_ptr<Node> nextDown;
        shared_ptr<Node> prev45up;
        shared_ptr<Node> next45up;
        shared_ptr<Node> prev45down;
        shared_ptr<Node> next45down;

        // Cell Attributes copy
        bool isStartNode;
        bool isWallNode;
        bool isExploredNode;
        bool isTargetNode;


        // MOVE INTO SEPARATE NODE SUBCLASSES

        // Weights May be used for heuristic-based algorithms (A* ..)
        float nextRightWeight;
        float prevLeftWeight;
        float nextUpWeight;
        float nextDownWeight;
        float prev45UpWeight;
        float next45UpWeight;
        float prev45DownWeight;
        float next45DownWeight;

        // Distances May be used for distance-based algorithms (Djkstra..)
        float nextRightDistance;
        float prevLeftDistance;
        float nextUpDistance;
        float nextDownDistance;
        float prev45UpDistance;
        float next45UpDistance;
        float prev45DownDistance;
        float next45DownDistance;

};


class NodeWeighted : public Node{

};

class NodeDistance : public Node{

};


class Graph{

    public:

        // Initialization Pass -> Connection Pass
        // REMOVE WINDOW REFERENCE LATER
        Graph(vector<shared_ptr<mapCell>>* board, sf::RenderWindow& ref, int startIdx);
        int getMatrixSize();

        void setStartNode(shared_ptr<Node>);
        void setStartIdx(int);
        shared_ptr<Node> getStartNode();

        vector<shared_ptr<Node>> nodeMatrix;


        ~Graph();

    private:
        // Essential References
        // vector<shared_ptr<mapCell>>* boardCells;
        shared_ptr<Node> StartNode;

        // Traversal References
        // Node* currentNode;


        int startIdx;

};


// REMOVE WINDOW REFERENCE LATER
Graph::Graph(vector<shared_ptr<mapCell>>* board, sf::RenderWindow& ref, int StartIdx){

    // Traverse the board and create nodes

    for(int mapIdx = 0; mapIdx < board->size(); mapIdx++){

        shared_ptr<mapCell> cell = board->at(mapIdx);

        shared_ptr<Node> newNode = make_shared<Node>(cell, mapIdx, cell->checkIsStart(), cell->checkIsWall(), cell->checkIsExplored(), cell->checkIsTarget());

        this->nodeMatrix.push_back(newNode);

        cout<<"Node "<<mapIdx<<" Created!"<<endl;
        
        if(newNode->isWall())
            cout<<"Is is a WALL!"<<endl;
        else if(newNode->isTarget())
            cout<<"It is a TARGET!"<<endl;

    }

    int matrixSize = this->nodeMatrix.size();

    this->setStartNode(this->nodeMatrix.at(StartIdx));


    // Calculations below determine the position/possible connections of a Node
    for(int nodeMapIdx = 0; nodeMapIdx < matrixSize; nodeMapIdx++){

        cout<<"Node at Index: "<<nodeMapIdx<<endl;

        // if(this->nodeMatrix[nodeMapIdx].get()->isStart()){

        //     if(startCount > 1){
        //         cout<<"!!! FATAL. MULTIPLE START NODES !!!"<<endl;
        //     }

        //     cout<<"Start Node FOUND At Index :"<<nodeMatrix[nodeMapIdx].get()->getIdx()<<endl;
        //     this->setStartNode(nodeMatrix[nodeMapIdx]);
        //     startCount++;
        // }


        // Top Left Node
        if(nodeMapIdx % 30 == 0 && (nodeMapIdx == 0)){
            cout<<"Top left node"<<endl;

            // Connect to accessible neighbouring nodes
            this->nodeMatrix[nodeMapIdx].get()->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx].get()->setNext45down(this->nodeMatrix[nodeMapIdx + 31]);
            this->nodeMatrix[nodeMapIdx].get()->setNextDown(this->nodeMatrix[nodeMapIdx + 30]);

            continue;

        }

        // Top Right Node
        else if(nodeMapIdx % 30 == 29 && nodeMapIdx == 29){
            cout<<"Top Right node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + 30]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + 29]);

            continue;

        }

        // Bottom Left Node
        else if(nodeMapIdx % 30 == 0 && nodeMapIdx + 30 > matrixSize){

            cout<<"Bottom Left Node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - 29]);
            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - 30]);


            continue;

        }

        // Bottom Right Node
        else if(nodeMapIdx % 30 == 29 && (nodeMapIdx + 1 >= matrixSize)){

            cout<<"Bottom Right Node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - 30]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - 31]);


            continue;

        }

        // Left Edge Node
        else if(nodeMapIdx % 30 == 0 && nodeMapIdx + 30 < matrixSize){

            cout<<"Left Edge Node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - 30]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - 29]);
            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + 30]);
            this->nodeMatrix[nodeMapIdx]->setNext45down(this->nodeMatrix[nodeMapIdx + 31]);


            continue;

        }


        // Right Edge Node
        else if(nodeMapIdx % 30 == 29 && nodeMapIdx + 30 < matrixSize){

            cout<<"Right Edge Node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - 30]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - 31]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + 29]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + 30]);


            continue;

        }


        // Top Edge Node
        else if(nodeMapIdx > 0 && nodeMapIdx < 29){
            cout<<"Top edge Node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setNext45down(this->nodeMatrix[nodeMapIdx + 31]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + 30]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + 29]);


            continue;

        }

        else if(nodeMapIdx > getMatrixSize() - 31 && nodeMapIdx < getMatrixSize() - 1){
            cout<<"Bottom edge node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - 29]);
            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - 30]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - 31]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);



            continue;

        }


        // Middle node
        else{

            cout<<"Middle Node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - 30]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - 31]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + 29]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + 30]);
            this->nodeMatrix[nodeMapIdx]->setNext45down(this->nodeMatrix[nodeMapIdx + 31]);
            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx +1]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - 29]);

            continue;
        }
        
    }


};


void Graph::setStartNode(shared_ptr<Node> startNode){
    this->StartNode = startNode;
}

shared_ptr<Node> Graph::getStartNode(){return this->StartNode;}

int Graph::getMatrixSize(){return this->nodeMatrix.size();}


shared_ptr<mapCell> Node::getCellRef(){return this->cellRef;}

void Graph::setStartIdx(int idx){
    this->startIdx = idx;
}

Graph::~Graph(){

    for(auto node: nodeMatrix){
        node = nullptr;
    }
}



#endif