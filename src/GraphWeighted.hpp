#ifndef GRAPHW_H
#define GRAPHW_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include <iostream>


#include <random>

#include "Interface.hpp"
#include "Graph.hpp"

// using std::cout, std::endl, std::string, std::pair, std::vector, std::priority_queue;
using namespace std;

class NodeExp : public Node{

    public:
        
        NodeExp(shared_ptr<mapCell> reference, int index, bool isStartIn, bool isWallIn, bool isExploredIn, bool isTargetIn);

        void setNextRight(shared_ptr<NodeExp> nextRight);
        void setPrevLeft(shared_ptr<NodeExp> prevLeft);
        void setNextUp(shared_ptr<NodeExp> nextUp);
        void setNextDown(shared_ptr<NodeExp> nextDown);
        void setPrev45up(shared_ptr<NodeExp> prev45up);
        void setNext45up(shared_ptr<NodeExp> next45up);
        void setPrev45down(shared_ptr<NodeExp> prev45down);
        void setNext45down(shared_ptr<NodeExp> next45down);

        // Node connection getters
        shared_ptr<NodeExp> getNextRight() const;
        shared_ptr<NodeExp> getPrevLeft() const;
        shared_ptr<NodeExp> getNextUp() const;
        shared_ptr<NodeExp> getNextDown() const;
        shared_ptr<NodeExp> getPrev45up() const;
        shared_ptr<NodeExp> getNext45up() const;
        shared_ptr<NodeExp> getPrev45down() const;
        shared_ptr<NodeExp> getNext45down() const;

        // Extended functionality

        // Node Weight
        void setNextRightWeight(const int wght);
        void setPrevLeftWeight(const int wght);
        void setNextUpWeight(const int wght);
        void setNextDownWeight(const int wght);
        void setPrev45UpWeight(const int wght);
        void setNext45UpWeight(const int wght);
        void setPrev45DownWeight(const int wght);
        void setNext45DownWeight(const int wght);
        
        int getNextRightWeight() const;
        int getPrevLeftWeight() const;
        int getNextUpWeight() const;
        int getNextDownWeight() const;
        int getPrev45UpWeight() const;
        int getNext45UpWeight() const;
        int getPrev45DownWeight() const;
        int getNext45DownWeight() const;
        
        // Distance to neighbouring nodes
        void setNextRightDistance(const int dist);
        void setPrevLeftDistance(const int dist);
        void setNextUpDistance(const int dist);
        void setNextDownDistance(const int dist);
        void setPrev45UpDistance(const int dist);
        void setNext45UpDistance(const int dist);
        void setPrev45DownDistance(const int dist);
        void setNext45DownDistance(const int dist);
        
        int getNextRightDistance() const;
        int getPrevLeftDistance() const;
        int getNextUpDistance() const;
        int getNextDownDistance() const;
        int getPrev45UpDistance() const;
        int getNext45UpDistance() const;
        int getPrev45DownDistance() const;
        int getNext45DownDistance() const;


        void setEstimate(int est);
        void setCurrent(int cur);

        const int getEstimate();
        const int getCurrent();
        const int getFScore();

        ~NodeExp(){}

    private:

        // Heuristic estimate from the current node to target node
        // Current Score (distance travelled from start to current node)
        // A-Star score = Cost of path to current Node + Heuristic (current to target estimate)
        int heurEst;
        int curScore;

        shared_ptr<NodeExp> nextRight;
        shared_ptr<NodeExp> prevLeft;
        shared_ptr<NodeExp> nextUp;
        shared_ptr<NodeExp> nextDown;
        shared_ptr<NodeExp> prev45up;
        shared_ptr<NodeExp> next45up;
        shared_ptr<NodeExp> prev45down;
        shared_ptr<NodeExp> next45down;


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



class GraphWeighted : public Graph{

    public:

        GraphWeighted(const vector<shared_ptr<mapCell>>* board, const shared_ptr<sf::RenderWindow> ref, const int startIdx, const int idxIncrements, const int endIdx, int heurisitc);

        // 4-way movement only
        int ManhattanDistance (const int idx, const int xDim, const int yDim) const;

        // 8-way movement
        int DiagonalDistance (const int idx, const int xDim, const int yDim) const;
        int ChebyshevDistance (const int idx, const int xDim, const int yDim) const;

        // 4 or 8-way
        int EuclidianDistance (const int idx, const int xDim, const int yDim) const;


        shared_ptr<NodeExp> getStartNode() const;
        const int getMatrixSize() const;

        void setStartNode(shared_ptr<NodeExp> newStart);

        ~GraphWeighted(){}

        vector<shared_ptr<NodeExp>> nodeMatrix;


    private:

        shared_ptr<NodeExp> startNode;

        int endIdx;
};




#endif