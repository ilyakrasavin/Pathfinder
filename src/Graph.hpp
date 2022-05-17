#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Interface.hpp"


using namespace std;


class Node;

class Graph{

    public:

        Graph(vector<shared_ptr<mapCell>>* board);
        ~Graph();

    private:
        // Essential References
        vector<shared_ptr<mapCell>>* boardCells;
        Node* StartNode;

        // Traversal References
        Node* currentNode;

        int exploredCount;
};



class Node{

    public:

        Node(bool isStartIn, bool isWallIn, bool isExploredIn, bool isTargetIn){

            isStartNode = isStartIn;
            isWallNode = isWallIn;
            isExploredNode = isExploredIn;
            isTargetNode = isTargetIn;

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
            prev45Weight = 0;
            next45Weight = 0;
            prev45Weight = 0;
            next45Weight = 0;

            nextRightDistance = 0;
            prevLeftDistance = 0;
            nextUpDistance = 0;
            nextDownDistance = 0;
            prev45Distance = 0;
            next45Distance = 0;
            prev45Distance = 0;
            next45Distance = 0;

        }
         
        void setNextRight(shared_ptr<mapCell> nextRight);
        void setPrevLeft(shared_ptr<mapCell> prevLeft);
        void setNextUp(shared_ptr<mapCell> nextUp);
        void setNextDown(shared_ptr<mapCell> nextDown);
        void setPrev45up(shared_ptr<mapCell> prev45up);
        void setNext45up(shared_ptr<mapCell> next45up);
        void setPrev45down(shared_ptr<mapCell> prev45down);
        void setNext45down(shared_ptr<mapCell> next45down);

        bool isExplored();        
        bool isExplored(Node* nextNode);
        bool isStart();
        bool isWall(Node* nextNode);
        bool isTarget(Node* nextNode);

        void setExplored();
    
        int getIdx();

        ~Node();

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
        float prev45Weight;
        float next45Weight;
        float prev45Weight;
        float next45Weight;

        // Distances May be used for distance-based algorithms (Djkstra..)
        float nextRightDistance;
        float prevLeftDistance;
        float nextUpDistance;
        float nextDownDistance;
        float prev45Distance;
        float next45Distance;
        float prev45Distance;
        float next45Distance;

};


#endif