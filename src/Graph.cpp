#include "Graph.hpp"

Node::Node(const shared_ptr<mapCell> reference, int index, bool isStartIn, bool isWallIn, bool isExploredIn, bool isTargetIn){

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

void Node::setNextRight(shared_ptr<Node> nextRight){this->nextRight = nextRight;}
void Node::setPrevLeft(shared_ptr<Node> prevLeft){this->prevLeft = prevLeft;}
void Node::setNextUp(shared_ptr<Node> nextUp){this->nextUp = nextUp;}
void Node::setNextDown(shared_ptr<Node> nextDown){this->nextDown = nextDown;}
void Node::setPrev45up(shared_ptr<Node> prev45up){this->prev45up = prev45up;}
void Node::setNext45up(shared_ptr<Node> next45up){this->next45up = next45up;}
void Node::setPrev45down(shared_ptr<Node> prev45down){this->prev45down = prev45down;}
void Node::setNext45down(shared_ptr<Node> next45down){this->next45down = next45down;}


shared_ptr<Node> Node::getNextRight() const {return nextRight;}
shared_ptr<Node> Node::getPrevLeft() const {return prevLeft;}
shared_ptr<Node> Node::getNextUp() const {return nextUp;}
shared_ptr<Node> Node::getNextDown() const {return nextDown;}
shared_ptr<Node> Node::getPrev45up() const {return prev45down;}
shared_ptr<Node> Node::getNext45up() const {return next45up;}
shared_ptr<Node> Node::getPrev45down() const {return prev45down;}
shared_ptr<Node> Node::getNext45down() const {return next45down;}


const bool Node::isExplored(){return isExploredNode;}        
const bool Node::isStart(){return isStartNode;}
const bool Node::isWall(){return isWallNode;}
const bool Node::isTarget(){return isTargetNode;}
const int Node::getIdx(){return mapIdx;}


void Node::setExplored(){isExploredNode = true;}
void Node::setIdx(int idx){mapIdx = idx;}

Node::~Node(){}



Graph::Graph(){}

Graph::Graph(const vector<shared_ptr<mapCell>>* board, const shared_ptr<sf::RenderWindow> ref, const int startIdx, const int IdxIncrements){

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

    this->setStartNode(this->nodeMatrix.at(startIdx));


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
}




void Graph::setStartNode(shared_ptr<Node> startNode){
    this->StartNode = startNode;
}

const shared_ptr<Node> Graph::getStartNode(){return this->StartNode;}

const int Graph::getMatrixSize() const {return this->nodeMatrix.size();}


const shared_ptr<mapCell> Node::getCellRef(){return this->cellRef;}

void Graph::setStartIdx(int idx){
    this->startIdx = idx;
}


Graph::~Graph(){

    for(auto node: nodeMatrix){
        node = nullptr;
    }
}

