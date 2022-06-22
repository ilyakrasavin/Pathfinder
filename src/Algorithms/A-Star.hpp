#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <queue>
#include <iostream>

#include "../GraphWeighted.hpp"

using std::cout, std::string, std::vector;



bool AStar(GraphWeighted* graph, shared_ptr<sf::RenderWindow> windowRef);

#endif