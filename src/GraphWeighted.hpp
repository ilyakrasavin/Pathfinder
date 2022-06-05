#ifndef GRAPHW_H
#define GRAPHW_H

#include "Graph.hpp"

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include <random>

#include "Interface.hpp"

using std::string, std::cout, std::endl;


class NodeExp : public Node{

    public:
        
        NodeExp(shared_ptr<mapCell> reference, int index, bool isStartIn, bool isWallIn, bool isExploredIn, bool isTargetIn){

            heurEst = INFINITY;
            curScore = 0;

            this->cellRef = reference;

            this->isStartNode = isStartIn;
            this->isWallNode = isWallIn;
            this->isExploredNode = isExploredIn;
            this->isTargetNode = isTargetIn;

            this->setIdx(index);

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

            // traversal Cost
            nextRightDistance = 0;
            prevLeftDistance = 0;
            nextUpDistance = 0;
            nextDownDistance = 0;
            prev45UpDistance = 0;
            next45UpDistance = 0;
            prev45DownDistance = 0;
            next45DownDistance = 0;

        }


        // Node Weight (if needed)
        void setNextRightWeight(const int wght){this->nextRightWeight = wght;}
        void setPrevLeftWeight(const int wght){this->prevLeftWeight = wght;}
        void setNextUpWeight(const int wght){this->nextUpWeight = wght;}
        void setNextDownWeight(const int wght){this->nextDownWeight = wght;}
        void setPrev45UpWeight(const int wght){this->prev45UpWeight = wght;}
        void setNext45UpWeight(const int wght){this->next45UpWeight = wght;}
        void setPrev45DownWeight(const int wght){this->prev45DownWeight = wght;}
        void setNext45DownWeight(const int wght){this->next45DownWeight = wght;}
        
        int getNextRightWeight() const {return this->nextRightWeight;}
        int getPrevLeftWeight() const {return this->prevLeftWeight;}
        int getNextUpWeight() const {return this->nextUpWeight;}
        int getNextDownWeight() const {return this->nextDownWeight;}
        int getPrev45UpWeight() const {return this->prev45UpWeight;}
        int getNext45UpWeight() const {return this->next45UpWeight;}
        int getPrev45DownWeight() const {return this->prev45DownWeight;}
        int getNext45DownWeight() const {return this->next45DownWeight;}
        
        // Distance to neighbouring nodes
        void setNextRightDistance(const int dist){this->nextRightDistance = dist;}
        void setPrevLeftDistance(const int dist){this->prevLeftDistance = dist;}
        void setNextUpDistance(const int dist){this->nextUpDistance = dist;}
        void setNextDownDistance(const int dist){this->nextDownDistance = dist;}
        void setPrev45UpDistance(const int dist){this->prev45UpDistance = dist;}
        void setNext45UpDistance(const int dist){this->next45UpDistance = dist;}
        void setPrev45DownDistance(const int dist){this->prev45DownDistance = dist;}
        void setNext45DownDistance(const int dist){this->next45DownDistance = dist;}
        
        int getNextRightDistance() const {return this->nextRightDistance;}
        int getPrevLeftDistance() const {return this->prevLeftDistance;}
        int getNextUpDistance() const {return this->nextUpDistance;}
        int getNextDownDistance() const {return this->nextDownDistance;}
        int getPrev45UpDistance() const {return this->prev45UpDistance;}
        int getNext45UpDistance() const {return this->next45UpDistance;}
        int getPrev45DownDistance() const {return this->prev45DownDistance;}
        int getNext45DownDistance() const {return this->next45DownDistance;}


        void setEstimate(int est){this->heurEst = est;}
        void setCurrent(int cur);

        constexpr const int getEstimate(){return this->heurEst;}
        constexpr const int getCurrent(){return this->curScore;}
        constexpr const int getAScore(){return this->heurEst + this->curScore;}

        ~NodeExp(){}

    private:

        // Heuristic estimate from the current node to target node
        // Current Score (distance travelled from start to current node)
        int heurEst;
        int curScore;
        // A-Star score = Cost of path to current Node + Heuristic (current to target estimate)

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




// Randomized Edge Weights / Distances

class GraphWeighted : public Graph{

    public:

        // Initialize random distances b/w vertices
        // Weights uninitialized for A* - May be used for other DP problems (Interval scheduling)

        GraphWeighted(const vector<shared_ptr<mapCell>>* board, const shared_ptr<sf::RenderWindow> ref, const int startIdx, const int idxIncrements, const int endIdx);


        // 4-way movement only
        int ManhattanDistance (const int idx, const int xDim, const int yDim) const;

        // 8-way movement
        int DiagonalDistance (const int idx, const int xDim, const int yDim) const;
        int ChebyshevDistance (const int idx, const int xDim, const int yDim) const;

        // 4 or 8-way
        int EuclidianDistance (const int idx, const int xDim, const int yDim) const;


        const shared_ptr<NodeExp> getStartNode() const {return startNode;}

        ~GraphWeighted(){}

    private:

        vector<shared_ptr<NodeExp>> nodeMatrix;

        shared_ptr<NodeExp> startNode;

        int endIdx;
};



GraphWeighted::GraphWeighted(const vector<shared_ptr<mapCell>>* board, const shared_ptr<sf::RenderWindow> ref, const int startIdx, const int idxIncrements, const int endIdx){

    // Initialize nodes for the board
    for(int mapIdx = 0; mapIdx < board->size(); mapIdx++){

        shared_ptr<mapCell> cell = board->at(mapIdx);

        shared_ptr<NodeExp> newNode = make_shared<NodeExp>(cell, mapIdx, cell->checkIsStart(), cell->checkIsWall(), cell->checkIsExplored(), cell->checkIsTarget());

        nodeMatrix.push_back(newNode);

        cout<<"Node "<<mapIdx<<" Created!"<<endl;
        
        if(newNode->isWall())
            cout<<"Is is a WALL!"<<endl;
        else if(newNode->isTarget())
            cout<<"It is a TARGET!"<<endl;

    }

    random_device randomNum;

    this->startIdx = startIdx;
    this->endIdx = endIdx;

    int matrixSize = this->nodeMatrix.size();

    this->setStartNode(this->nodeMatrix.at(startIdx));


    // Walk through the map by index
    // Connect nodes & Initialize traversal costs to random positive values

    for(int nodeMapIdx = 0; nodeMapIdx < matrixSize; nodeMapIdx++){

        cout<<"Node at Index: "<<nodeMapIdx<<endl;


        // Top Left Node
        if(nodeMapIdx % idxIncrements == 0 && (nodeMapIdx == 0)){
            cout<<"Top left node"<<endl;

            // Set the heuristic estimation
            int heuristicRes = this->EuclidianDistance(nodeMapIdx, 20, 17);
            this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            // Connect to accessible neighbouring nodes
            this->nodeMatrix[nodeMapIdx].get()->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx].get()->setNext45down(this->nodeMatrix[nodeMapIdx + idxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx].get()->setNextDown(this->nodeMatrix[nodeMapIdx + idxIncrements]);


            // Insert random distances to neighbouring nodes
            this->nodeMatrix[nodeMapIdx].get()->setNextRightDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx].get()->setNext45DownDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx].get()->setNextDownDistance(randomNum()%100);

            continue;

        }

        // Top Right Node
        else if((nodeMapIdx % idxIncrements == (idxIncrements - 1)) && (nodeMapIdx == (idxIncrements -1))){
            cout<<"Top Right node"<<endl;

            // Set the heuristic estimation
            int heuristicRes = this->EuclidianDistance(nodeMapIdx, 20, 17);
            this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);


            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + idxIncrements - 1]);

            this->nodeMatrix[nodeMapIdx]->setPrevLeftDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNextDownDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setPrev45DownDistance(randomNum()%100);

            continue;

        }

        // Bottom Left Node
        else if((nodeMapIdx % idxIncrements == 0) && (nodeMapIdx + idxIncrements > matrixSize)){

            cout<<"Bottom Left Node"<<endl;

            // Set the heuristic estimation
            int heuristicRes = this->EuclidianDistance(nodeMapIdx, 20, 17);
            this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - idxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - idxIncrements]);

            this->nodeMatrix[nodeMapIdx]->setNextRightDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNext45UpDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setPrev45DownWeight(randomNum()%100);

            continue;

        }

        // Bottom Right Node
        else if((nodeMapIdx % idxIncrements == (idxIncrements-1)) && (nodeMapIdx + 1 >= matrixSize)){

            cout<<"Bottom Right Node"<<endl;

            // Set the heuristic estimation
            int heuristicRes = this->EuclidianDistance(nodeMapIdx, 20, 17);
            this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - idxIncrements - 1]);


            this->nodeMatrix[nodeMapIdx]->setPrevLeftDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNextUpDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setPrev45UpDistance(randomNum()%100);


            continue;

        }

        // Left Edge Node
        else if((nodeMapIdx % idxIncrements == 0) && (nodeMapIdx + idxIncrements < matrixSize)){

            cout<<"Left Edge Node"<<endl;

            // Set the heuristic estimation
            int heuristicRes = this->EuclidianDistance(nodeMapIdx, 20, 17);
            this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - idxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setNext45down(this->nodeMatrix[nodeMapIdx + idxIncrements + 1]);


            this->nodeMatrix[nodeMapIdx]->setNextUpDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNext45UpDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNextRightDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNextDownDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNext45DownDistance(randomNum()%100);

            continue;

        }


        // Right Edge Node
        else if((nodeMapIdx % idxIncrements == (idxIncrements-1)) && (nodeMapIdx + idxIncrements < matrixSize)){

            cout<<"Right Edge Node"<<endl;

            // Set the heuristic estimation
            int heuristicRes = this->EuclidianDistance(nodeMapIdx, 20, 17);
            this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - idxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + idxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + idxIncrements]);

            this->nodeMatrix[nodeMapIdx]->setNextUpDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setPrev45UpDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setPrevLeftDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setPrev45DownDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNextDownDistance(randomNum()%100);

            continue;

        }


        // Top Edge Node
        else if(nodeMapIdx > 0 && (nodeMapIdx < (idxIncrements - 1))){
            cout<<"Top edge Node"<<endl;


            // Set the heuristic estimation
            int heuristicRes = this->EuclidianDistance(nodeMapIdx, 20, 17);
            this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setNext45down(this->nodeMatrix[nodeMapIdx + idxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + idxIncrements - 1]);

            this->nodeMatrix[nodeMapIdx]->setNextRightDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setPrevLeftDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNext45DownDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNextDownDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setPrev45DownDistance(randomNum()%100);

            continue;

        }

        else if(nodeMapIdx > (getMatrixSize() - (idxIncrements + 1)) && (nodeMapIdx < (getMatrixSize() - 1))){
            cout<<"Bottom edge node"<<endl;


            // Set the heuristic estimation
            int heuristicRes = this->EuclidianDistance(nodeMapIdx, 20, 17);
            this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - idxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - idxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);


            this->nodeMatrix[nodeMapIdx]->setNextRightDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNext45UpDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNextUpDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setPrev45UpDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setPrevLeftDistance(randomNum()%100);

            continue;

        }


        // Middle node
        else{

            cout<<"Middle Node"<<endl;

            // Set the heuristic estimation
            int heuristicRes = this->EuclidianDistance(nodeMapIdx, 20, 17);
            this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            cout<<"Heuristic estimate is: "<<heuristicRes<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - idxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + idxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setNext45down(this->nodeMatrix[nodeMapIdx + idxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx +1]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - idxIncrements + 1]);

            this->nodeMatrix[nodeMapIdx]->setNextUpDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setPrev45UpDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setPrevLeftDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setPrev45DownDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNextDownDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNext45DownDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNextRightDistance(randomNum()%100);
            this->nodeMatrix[nodeMapIdx]->setNext45UpDistance(randomNum()%100);


            continue;
        }
        
    }

}


int GraphWeighted::EuclidianDistance (const int idx, const int xDim, const int yDim) const{

    int elemX = idx % xDim;
    int elemY = (idx / xDim) % yDim;

    int targetX = this->endIdx % xDim;
    int targetY = (this->endIdx / xDim) % yDim;


    return sqrt(pow(abs(targetX) - abs(elemX), 2) + pow(abs(targetY) - abs(elemY), 2));
}


int GraphWeighted::ManhattanDistance (const int idx, const int xDim, const int yDim) const{
    
    int elemX = idx % xDim;
    int elemY = (idx / xDim) % yDim;

    int targetX = this->endIdx % xDim;
    int targetY = (this->endIdx / xDim) % yDim;
    
    
    return abs(targetX - elemX) + abs(targetY - elemY);
}

int GraphWeighted::ChebyshevDistance (const int idx, const int xDim, const int yDim) const{

    int elemX = idx % xDim;
    int elemY = (idx / xDim) % yDim;

    int targetX = this->endIdx % xDim;
    int targetY = (this->endIdx / xDim) % yDim;

    int dx = abs(targetX - elemX);
    int dy = abs(targetY - elemY);

    int minDist = (dx < dy) ? dx : dy;

    return (dx + dy) - minDist;
}


#endif