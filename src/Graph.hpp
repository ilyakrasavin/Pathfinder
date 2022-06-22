#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include <iostream>


#include "Interface.hpp"

// #include "Application.hpp"

// using std::cout, std::endl, std::string, std::pair, std::vector, std::priority_queue;
using namespace std;


class Node{

    public:

        Node(){};

        // Default constructor
        Node(const shared_ptr<mapCell> reference, int index, bool isStartIn, bool isWallIn, bool isExploredIn, bool isTargetIn);         

        // Node Connection setters
        void setNextRight(shared_ptr<Node> nextRight);
        void setPrevLeft(shared_ptr<Node> prevLeft);
        void setNextUp(shared_ptr<Node> nextUp);
        void setNextDown(shared_ptr<Node> nextDown);
        void setPrev45up(shared_ptr<Node> prev45up);
        void setNext45up(shared_ptr<Node> next45up);
        void setPrev45down(shared_ptr<Node> prev45down);
        void setNext45down(shared_ptr<Node> next45down);

        // Node connection getters
        shared_ptr<Node> getNextRight() const;
        shared_ptr<Node> getPrevLeft() const;
        shared_ptr<Node> getNextUp() const;
        shared_ptr<Node> getNextDown() const;
        shared_ptr<Node> getPrev45up() const;
        shared_ptr<Node> getNext45up() const;
        shared_ptr<Node> getPrev45down() const;
        shared_ptr<Node> getNext45down() const;

        // Attribute check
        const bool isExplored();        
        const bool isStart();
        const bool isWall();
        const bool isTarget();
        const int getIdx();

        const shared_ptr<mapCell> getCellRef();

        // Attribure setters
        void setExplored();
        void setIdx(int idx);

        virtual ~Node();

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
        Graph();
        Graph(const vector<shared_ptr<mapCell>>* board, const shared_ptr<sf::RenderWindow> ref, const int startIdx, const int idxIncrements);
        const int getMatrixSize() const;

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


#endif