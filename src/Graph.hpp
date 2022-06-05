#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Interface.hpp"


using namespace std;



class Node{

    public:

        Node(){};

        // Default constructor
        Node(const shared_ptr<mapCell> reference, int index, bool isStartIn, bool isWallIn, bool isExploredIn, bool isTargetIn){

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
        const shared_ptr<Node> getNextRight(){return nextRight;}
        const shared_ptr<Node> getPrevLeft(){return prevLeft;}
        const shared_ptr<Node> getNextUp(){return nextUp;}
        const shared_ptr<Node> getNextDown(){return nextDown;}
        const shared_ptr<Node> getPrev45up(){return prev45down;}
        const shared_ptr<Node> getNext45up(){return next45up;}
        const shared_ptr<Node> getPrev45down(){return prev45down;}
        const shared_ptr<Node> getNext45down(){return next45down;}

        // Attribute check
        const bool isExplored(){return isExploredNode;}        
        const bool isStart(){return isStartNode;}
        const bool isWall(){return isWallNode;}
        const bool isTarget(){return isTargetNode;}
        const int getIdx(){return mapIdx;}


        const shared_ptr<mapCell> getCellRef();

        // Attribure setters
        void setExplored(){isExploredNode = true;}
        void setIdx(int idx){mapIdx = idx;}

        virtual ~Node(){};

    protected:
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


};




class Graph{

    public:

        // Initialization Pass -> Connection Pass
        // REMOVE WINDOW REFERENCE LATER
        Graph(){}
        Graph(const vector<shared_ptr<mapCell>>* board, const shared_ptr<sf::RenderWindow> ref, const int startIdx, const int idxIncrements);
        const int getMatrixSize();

        void setStartNode(shared_ptr<Node>);
        void setStartIdx(int);
        const shared_ptr<Node> getStartNode();

        vector<shared_ptr<Node>> nodeMatrix;


        virtual ~Graph();


    protected:
        // Essential References
        shared_ptr<Node> StartNode;

        int startIdx;

};


// REMOVE WINDOW REFERENCE LATER
Graph::Graph(const vector<shared_ptr<mapCell>>* board, const shared_ptr<sf::RenderWindow> ref, const int StartIdx, const int IdxIncrements){

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
        if(nodeMapIdx % IdxIncrements == 0 && (nodeMapIdx == 0)){
            cout<<"Top left node"<<endl;

            // Connect to accessible neighbouring nodes
            this->nodeMatrix[nodeMapIdx].get()->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx].get()->setNext45down(this->nodeMatrix[nodeMapIdx + IdxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx].get()->setNextDown(this->nodeMatrix[nodeMapIdx + IdxIncrements]);

            continue;

        }

        // Top Right Node
        else if((nodeMapIdx % IdxIncrements == (IdxIncrements - 1)) && (nodeMapIdx == (IdxIncrements -1))){
            cout<<"Top Right node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + IdxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + IdxIncrements - 1]);

            continue;

        }

        // Bottom Left Node
        else if((nodeMapIdx % IdxIncrements == 0) && (nodeMapIdx + IdxIncrements > matrixSize)){

            cout<<"Bottom Left Node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - IdxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - IdxIncrements]);


            continue;

        }

        // Bottom Right Node
        else if((nodeMapIdx % IdxIncrements == (IdxIncrements-1)) && (nodeMapIdx + 1 >= matrixSize)){

            cout<<"Bottom Right Node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - IdxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - IdxIncrements - 1]);


            continue;

        }

        // Left Edge Node
        else if((nodeMapIdx % IdxIncrements == 0) && (nodeMapIdx + IdxIncrements < matrixSize)){

            cout<<"Left Edge Node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - IdxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - IdxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + IdxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setNext45down(this->nodeMatrix[nodeMapIdx + IdxIncrements + 1]);


            continue;

        }


        // Right Edge Node
        else if((nodeMapIdx % IdxIncrements == (IdxIncrements-1)) && (nodeMapIdx + IdxIncrements < matrixSize)){

            cout<<"Right Edge Node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - IdxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - IdxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + IdxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + IdxIncrements]);


            continue;

        }


        // Top Edge Node
        else if(nodeMapIdx > 0 && (nodeMapIdx < (IdxIncrements - 1))){
            cout<<"Top edge Node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setNext45down(this->nodeMatrix[nodeMapIdx + IdxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + IdxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + IdxIncrements - 1]);


            continue;

        }

        else if(nodeMapIdx > (getMatrixSize() - (IdxIncrements + 1)) && (nodeMapIdx < (getMatrixSize() - 1))){
            cout<<"Bottom edge node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - IdxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - IdxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - IdxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);



            continue;

        }


        // Middle node
        else{

            cout<<"Middle Node"<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - IdxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - IdxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + IdxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + IdxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setNext45down(this->nodeMatrix[nodeMapIdx + IdxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx +1]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - IdxIncrements + 1]);

            continue;
        }
        
    }


};


void Graph::setStartNode(shared_ptr<Node> startNode){
    this->StartNode = startNode;
}

const shared_ptr<Node> Graph::getStartNode(){return this->StartNode;}

const int Graph::getMatrixSize(){return this->nodeMatrix.size();}


const shared_ptr<mapCell> Node::getCellRef(){return this->cellRef;}

void Graph::setStartIdx(int idx){
    this->startIdx = idx;
}

Graph::~Graph(){

    for(auto node: nodeMatrix){
        node = nullptr;
    }
}



#endif