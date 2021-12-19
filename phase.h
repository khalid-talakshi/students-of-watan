#ifndef PHASE_H
#define PHASE_H
#include <exception>
#include <vector>
#include <map>

//Phase carries the information of the current command
//a distribute resource command will trigger a Phase with the resource type of the resource
//being distributed, not the resource of the Cell since Cells do not have resources

enum class CellType { None, Edge, Vertex };
enum class Progress { None, Goals, Assignment, Midterm, Exam };
enum class Colour { NoColour, Blue, Red, Orange, Yellow };
enum class TurnPhase { Roll, DistributeResources, MoveGeese, Trade, Progress, updateEdgeProgressability, updateVertexProgressability, DistributeResourcesPlayer };
enum class ResourceType { None, Tutorial, Study, Caffeine, Lab, Lecture };

struct ExceptionEOF : public std::exception {
};

struct Phase {
	TurnPhase phase;
	Colour currentPlayer;
	ResourceType resource;
	Progress cellProgress;
	int position;
	bool hasGeese;
};

#endif
