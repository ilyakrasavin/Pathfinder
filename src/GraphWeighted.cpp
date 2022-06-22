#include "GraphWeighted.hpp"

NodeExp::NodeExp(shared_ptr<mapCell> reference, int index, bool isStartIn, bool isWallIn, bool isExploredIn, bool isTargetIn){

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


shared_ptr<NodeExp> NodeExp::getNextRight() const {return nextRight;}
shared_ptr<NodeExp> NodeExp::getPrevLeft() const {return prevLeft;}
shared_ptr<NodeExp> NodeExp::getNextUp() const {return nextUp;}
shared_ptr<NodeExp> NodeExp::getNextDown() const {return nextDown;}
shared_ptr<NodeExp> NodeExp::getPrev45up() const {return prev45down;}
shared_ptr<NodeExp> NodeExp::getNext45up() const {return next45up;}
shared_ptr<NodeExp> NodeExp::getPrev45down() const {return prev45down;}
shared_ptr<NodeExp> NodeExp::getNext45down() const {return next45down;}


void NodeExp::setNextRightWeight(const int wght){this->nextRightWeight = wght;}
void NodeExp::setPrevLeftWeight(const int wght){this->prevLeftWeight = wght;}
void NodeExp::setNextUpWeight(const int wght){this->nextUpWeight = wght;}
void NodeExp::setNextDownWeight(const int wght){this->nextDownWeight = wght;}
void NodeExp::setPrev45UpWeight(const int wght){this->prev45UpWeight = wght;}
void NodeExp::setNext45UpWeight(const int wght){this->next45UpWeight = wght;}
void NodeExp::setPrev45DownWeight(const int wght){this->prev45DownWeight = wght;}
void NodeExp::setNext45DownWeight(const int wght){this->next45DownWeight = wght;}

int NodeExp::getNextRightWeight() const {return this->nextRightWeight;}
int NodeExp::getPrevLeftWeight() const {return this->prevLeftWeight;}
int NodeExp::getNextUpWeight() const {return this->nextUpWeight;}
int NodeExp::getNextDownWeight() const {return this->nextDownWeight;}
int NodeExp::getPrev45UpWeight() const {return this->prev45UpWeight;}
int NodeExp::getNext45UpWeight() const {return this->next45UpWeight;}
int NodeExp::getPrev45DownWeight() const {return this->prev45DownWeight;}
int NodeExp::getNext45DownWeight() const {return this->next45DownWeight;}

// Distance to neighbouring nodes
void NodeExp::setNextRightDistance(const int dist){this->nextRightDistance = dist;}
void NodeExp::setPrevLeftDistance(const int dist){this->prevLeftDistance = dist;}
void NodeExp::setNextUpDistance(const int dist){this->nextUpDistance = dist;}
void NodeExp::setNextDownDistance(const int dist){this->nextDownDistance = dist;}
void NodeExp::setPrev45UpDistance(const int dist){this->prev45UpDistance = dist;}
void NodeExp::setNext45UpDistance(const int dist){this->next45UpDistance = dist;}
void NodeExp::setPrev45DownDistance(const int dist){this->prev45DownDistance = dist;}
void NodeExp::setNext45DownDistance(const int dist){this->next45DownDistance = dist;}

int NodeExp::getNextRightDistance() const {return this->nextRightDistance;}
int NodeExp::getPrevLeftDistance() const {return this->prevLeftDistance;}
int NodeExp::getNextUpDistance() const {return this->nextUpDistance;}
int NodeExp::getNextDownDistance() const {return this->nextDownDistance;}
int NodeExp::getPrev45UpDistance() const {return this->prev45UpDistance;}
int NodeExp::getNext45UpDistance() const {return this->next45UpDistance;}
int NodeExp::getPrev45DownDistance() const {return this->prev45DownDistance;}
int NodeExp::getNext45DownDistance() const {return this->next45DownDistance;}


void NodeExp::setEstimate(int est){this->heurEst = est;}
void NodeExp::setCurrent(int cur){}

const int NodeExp::getEstimate(){return this->heurEst;}
const int NodeExp::getCurrent(){return this->curScore;}
const int NodeExp::getFScore(){return this->heurEst + this->curScore;}



void NodeExp::setNextRight(shared_ptr<NodeExp> nextRight){this->nextRight = nextRight;}
void NodeExp::setPrevLeft(shared_ptr<NodeExp> prevLeft){this->prevLeft = prevLeft;}
void NodeExp::setNextUp(shared_ptr<NodeExp> nextUp){this->nextUp = nextUp;}
void NodeExp::setNextDown(shared_ptr<NodeExp> nextDown){this->nextDown = nextDown;}
void NodeExp::setPrev45up(shared_ptr<NodeExp> prev45up){this->prev45up = prev45up;}
void NodeExp::setNext45up(shared_ptr<NodeExp> next45up){this->next45up = next45up;}
void NodeExp::setPrev45down(shared_ptr<NodeExp> prev45down){this->prev45down = prev45down;}
void NodeExp::setNext45down(shared_ptr<NodeExp> next45down){this->next45down = next45down;}



GraphWeighted::GraphWeighted(const vector<shared_ptr<mapCell>>* board, const shared_ptr<sf::RenderWindow> ref, const int startIdx, const int idxIncrements, const int endIdx, int heuristic){

    // Initialize nodes for the board
    for(int mapIdx = 0; mapIdx < board->size(); mapIdx++){

        shared_ptr<mapCell> cell = board->at(mapIdx);

        shared_ptr<NodeExp> newNode = make_shared<NodeExp>(cell, mapIdx, cell->checkIsStart(), cell->checkIsWall(), cell->checkIsExplored(), cell->checkIsTarget());

        
        int heuristicRes = 0;

        if(heuristic == 0){
            
            heuristicRes = this->EuclidianDistance(mapIdx, 20, 17);
            
        }
        else if(heuristic == 1){
            
            heuristicRes = this->ManhattanDistance(mapIdx, 20, 17);

        }
        else{

            heuristicRes = this->ChebyshevDistance(mapIdx, 20, 17);

        }

        
        newNode->setEstimate(heuristicRes);
        newNode->getCellRef()->setScore(heuristicRes, mapIdx);

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
            // int heuristicRes = this->ChebyshevDistance(nodeMapIdx, 20, 17);
            // this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            // Connect to accessible neighbouring nodes
            this->nodeMatrix[nodeMapIdx].get()->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx].get()->setNext45down(this->nodeMatrix[nodeMapIdx + idxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx].get()->setNextDown(this->nodeMatrix[nodeMapIdx + idxIncrements]);


            // Insert random distances to neighbouring nodes
            this->nodeMatrix[nodeMapIdx].get()->setNextRightDistance(1);
            this->nodeMatrix[nodeMapIdx].get()->setNext45DownDistance(1);
            this->nodeMatrix[nodeMapIdx].get()->setNextDownDistance(1);

            continue;

        }

        // Top Right Node
        else if((nodeMapIdx % idxIncrements == (idxIncrements - 1)) && (nodeMapIdx == (idxIncrements -1))){
            cout<<"Top Right node"<<endl;

            // Set the heuristic estimation
            // int heuristicRes = this->ChebyshevDistance(nodeMapIdx, 20, 17);
            // this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);


            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + idxIncrements - 1]);

            this->nodeMatrix[nodeMapIdx]->setPrevLeftDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNextDownDistance(1);
            this->nodeMatrix[nodeMapIdx]->setPrev45DownDistance(1);

            continue;

        }

        // Bottom Left Node
        else if((nodeMapIdx % idxIncrements == 0) && (nodeMapIdx + idxIncrements >= matrixSize)){

            cout<<"Bottom Left Node"<<endl;

            // Set the heuristic estimation
            // int heuristicRes = this->ChebyshevDistance(nodeMapIdx, 20, 17);
            // this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - idxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - idxIncrements]);

            this->nodeMatrix[nodeMapIdx]->setNextRightDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNext45UpDistance(1);
            this->nodeMatrix[nodeMapIdx]->setPrev45DownWeight(1);

            continue;

        }

        // Bottom Right Node
        else if((nodeMapIdx % idxIncrements == (idxIncrements-1)) && (nodeMapIdx + 1 >= matrixSize)){

            cout<<"Bottom Right Node"<<endl;

            // Set the heuristic estimation
            // int heuristicRes = this->ChebyshevDistance(nodeMapIdx, 20, 17);
            // this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - idxIncrements - 1]);


            this->nodeMatrix[nodeMapIdx]->setPrevLeftDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNextUpDistance(1);
            this->nodeMatrix[nodeMapIdx]->setPrev45UpDistance(1);


            continue;

        }

        // Left Edge Node
        else if((nodeMapIdx % idxIncrements == 0) && (nodeMapIdx + idxIncrements < matrixSize)){

            cout<<"Left Edge Node"<<endl;

            // Set the heuristic estimation
            // int heuristicRes = this->ChebyshevDistance(nodeMapIdx, 20, 17);
            // this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - idxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setNext45down(this->nodeMatrix[nodeMapIdx + idxIncrements + 1]);


            this->nodeMatrix[nodeMapIdx]->setNextUpDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNext45UpDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNextRightDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNextDownDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNext45DownDistance(1);

            continue;

        }


        // Right Edge Node
        else if((nodeMapIdx % idxIncrements == (idxIncrements-1)) && (nodeMapIdx + idxIncrements < matrixSize)){

            cout<<"Right Edge Node"<<endl;

            // Set the heuristic estimation
            // int heuristicRes = this->ChebyshevDistance(nodeMapIdx, 20, 17);
            // this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - idxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + idxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + idxIncrements]);

            this->nodeMatrix[nodeMapIdx]->setNextUpDistance(1);
            this->nodeMatrix[nodeMapIdx]->setPrev45UpDistance(1);
            this->nodeMatrix[nodeMapIdx]->setPrevLeftDistance(1);
            this->nodeMatrix[nodeMapIdx]->setPrev45DownDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNextDownDistance(1);

            continue;

        }


        // Top Edge Node
        else if(nodeMapIdx > 0 && (nodeMapIdx < (idxIncrements - 1))){
            cout<<"Top edge Node"<<endl;


            // Set the heuristic estimation
            // int heuristicRes = this->ChebyshevDistance(nodeMapIdx, 20, 17);
            // this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setNext45down(this->nodeMatrix[nodeMapIdx + idxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + idxIncrements - 1]);

            this->nodeMatrix[nodeMapIdx]->setNextRightDistance(1);
            this->nodeMatrix[nodeMapIdx]->setPrevLeftDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNext45DownDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNextDownDistance(1);
            this->nodeMatrix[nodeMapIdx]->setPrev45DownDistance(1);

            continue;

        }

        else if(nodeMapIdx >= (this->getMatrixSize() - (idxIncrements + 1)) && (nodeMapIdx < (this->getMatrixSize() - 1))){
            cout<<"Bottom edge node"<<endl;


            // Set the heuristic estimation
            // int heuristicRes = this->ChebyshevDistance(nodeMapIdx, 20, 17);
            // this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx + 1]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - idxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - idxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);


            this->nodeMatrix[nodeMapIdx]->setNextRightDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNext45UpDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNextUpDistance(1);
            this->nodeMatrix[nodeMapIdx]->setPrev45UpDistance(1);
            this->nodeMatrix[nodeMapIdx]->setPrevLeftDistance(1);

            continue;

        }


        // Middle node
        else{

            cout<<"Middle Node"<<endl;

            cout<<"IS BOTTOM EDGE TRUE?: "<<(nodeMapIdx >= (this->getMatrixSize() - (idxIncrements + 1)) && (nodeMapIdx < (this->getMatrixSize() - 1)))<<endl;

            // Set the heuristic estimation
            // int heuristicRes = this->ChebyshevDistance(nodeMapIdx, 20, 17);
            // this->nodeMatrix[nodeMapIdx].get()->setEstimate(heuristicRes);

            // cout<<"Heuristic estimate is: "<<heuristicRes<<endl;

            this->nodeMatrix[nodeMapIdx]->setNextUp(this->nodeMatrix[nodeMapIdx - idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setPrev45up(this->nodeMatrix[nodeMapIdx - idxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrevLeft(this->nodeMatrix[nodeMapIdx - 1]);
            this->nodeMatrix[nodeMapIdx]->setPrev45down(this->nodeMatrix[nodeMapIdx + idxIncrements - 1]);
            this->nodeMatrix[nodeMapIdx]->setNextDown(this->nodeMatrix[nodeMapIdx + idxIncrements]);
            this->nodeMatrix[nodeMapIdx]->setNext45down(this->nodeMatrix[nodeMapIdx + idxIncrements + 1]);
            this->nodeMatrix[nodeMapIdx]->setNextRight(this->nodeMatrix[nodeMapIdx +1]);
            this->nodeMatrix[nodeMapIdx]->setNext45up(this->nodeMatrix[nodeMapIdx - idxIncrements + 1]);

            this->nodeMatrix[nodeMapIdx]->setNextUpDistance(1);
            this->nodeMatrix[nodeMapIdx]->setPrev45UpDistance(1);
            this->nodeMatrix[nodeMapIdx]->setPrevLeftDistance(1);
            this->nodeMatrix[nodeMapIdx]->setPrev45DownDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNextDownDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNext45DownDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNextRightDistance(1);
            this->nodeMatrix[nodeMapIdx]->setNext45UpDistance(1);


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


shared_ptr<NodeExp> GraphWeighted::getStartNode() const {return startNode;}
const int GraphWeighted::getMatrixSize() const{return this->nodeMatrix.size();}

void GraphWeighted::setStartNode(shared_ptr<NodeExp> newStart){this->startNode = newStart;}