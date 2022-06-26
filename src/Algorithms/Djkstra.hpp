#ifndef DJKSTRA_H
#define DJKSTRA_H

#include <vector>
#include <queue>
#include <iostream>
#include <memory>

#include "../GraphWeighted.hpp"

#include "../Application.hpp"

// using std::cout, std::string, std::vector;
using namespace std;


// Find shortest paths from Source to every node (Uninformed)
bool Djkstra(Application* appControls);

#endif

