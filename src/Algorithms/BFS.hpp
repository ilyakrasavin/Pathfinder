#ifndef BFS_H
#define BFS_H

#include <vector>
#include <queue>
#include <iostream>

#include "../Graph.hpp"

using namespace std;


// Add App reference for cleaner state controls

bool BreadthFirstSearch(Graph* graph, shared_ptr<sf::RenderWindow> windowRef);


#endif