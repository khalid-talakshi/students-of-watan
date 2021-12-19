#ifndef MAPS_H
#define MAPS_H
#include <vector>
#include <map>
#include "phase.h"

extern std::map<int, Colour> playerMap;
extern std::map<int, std::vector<int>> edgeOfTile;
extern std::map<int, std::vector<int>> vertexOfTile;
extern std::map<int, std::vector<int>> edgeOfVertex;
extern std::map<int, std::vector<int>> vertexOfEdge;

#endif
