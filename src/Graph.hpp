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
        void setNextRight(Node* nextRight){this->nextRight = nextRight;}
        void setPrevLeft(Node* prevLeft){this->prevLeft = prevLeft;}
        void setNextUp(Node* nextUp){this->nextUp = nextUp;}
        void setNextDown(Node* nextDown){this->nextDown = nextDown;}
        void setPrev45up(Node* prev45up){this->prev45up = prev45up;}
        void setNext45up(Node* next45up){this->next45up = next45up;}
        void setPrev45down(Node* prev45down){this->prev45down = prev45down;}
        void setNext45down(Node* next45down){this->next45down = next45down;}

        // Node connection getters
        Node* getNextRight(){return nextRight;}
        Node* getPrevLeft(){return prevLeft;}
        Node* getNextUp(){return nextUp;}
        Node* getNextDown(){return nextDown;}
        Node* getPrev45up(){return prev45down;}
        Node* getNext45up(){return next45up;}
        Node* getPrev45down(){return prev45down;}
        Node* getNext45down(){return next45down;}

        // Attribute check
        bool isExplored(){return isExploredNode;}        
        bool isStart(){return isStartNode;}
        bool isWall(){return isWallNode;}
        bool isTarget(){return isTargetNode;}
        int getIdx(){return mapIdx;}


        // Attribure setters
        void setExplored(){isExploredNode = true;}
        void setIdx(int idx){mapIdx = idx;}

        ~Node(){};

    private:
        // Reference to a cell in a Render-able map
        shared_ptr<mapCell> cellRef;

        int mapIdx;

        // Neighboring Nodes
        Node* nextRight;
        Node* prevLeft;
        Node* nextUp;
        Node* nextDown;
        Node* prev45up;
        Node* next45up;
        Node* prev45down;
        Node* next45down;

        // Cell Attributes copy
        bool isStartNode;
        bool isWallNode;
        bool isExploredNode;
        bool isTargetNode;

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
        Graph(vector<shared_ptr<mapCell>>* board);
        Node* getStartNode();
        // void moveCurrent();
    
        ~Graph();

    private:
        // Essential References
        // vector<shared_ptr<mapCell>>* boardCells;
        Node* StartNode;

        // Traversal References
        // Node* currentNode;

        vector<Node*> nodeMatrix;

};


Graph::Graph(vector<shared_ptr<mapCell>>* board){

    // Traverse the board and create nodes

    for(int mapIdx = 0; mapIdx < board->size(); mapIdx++){

        shared_ptr<mapCell> cell = board->at(mapIdx);

        Node* newNode = new Node(cell, mapIdx, cell->checkIsStart(), cell->checkIsWall(), cell->checkIsExplored(), cell->checkIsTarget());

        this->nodeMatrix.push_back(newNode);

        cout<<"Node "<<mapIdx<<" Created!"<<endl;

    }

    int matrixSize = this->nodeMatrix.size();

    // Calculations below determine the position/possible connections of a Node
    for(int nodeMapIdx = 0; nodeMapIdx < matrixSize; nodeMapIdx++){

        // Top Left Node
        if(nodeMapIdx % 45 == 0 && (nodeMapIdx == 0)){
            cout<<"Top left node"<<endl;
            // Connect
        }

        // Top Right Node
        else if(nodeMapIdx % 45 == 44 && nodeMapIdx == 44){
            cout<<"Top Right node"<<endl;

        }

        // Bottom Left Node
        else if(nodeMapIdx % 45 == 0 && nodeMapIdx + 45 > matrixSize){

        }

        // Bottom Right Node
        else if(nodeMapIdx % 45 == 44 && (nodeMapIdx + 1 > matrixSize)){

        }

        // Left Edge Node
        else if(nodeMapIdx % 45 == 0){

        }


        // Right Edge Node
        else if(nodeMapIdx % 45 == 44){

        }

        // Middle node
        else{

        }
        
    }



}


Node* Graph::getStartNode(){return this->StartNode;}

Graph::~Graph(){

    for(auto node: nodeMatrix){
        delete node;
    }
}



#endif