#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include <vector>
#include <map>
#include "observer.h"
#include "subject.h"
#include "phase.h"
#include "tile.h"
#include "maps.h"

struct TileDisplay {
	std::vector<char> topEdge;
	std::vector<char> topEmpty;
	std::vector<char> position;
	std::vector<char> resource;
	std::vector<char> diceRoll;
	std::vector<char> hasGeese;
	std::vector<char> midEmpty;
	std::vector<char> lowEmpty;
	std::vector<char> lowEdge;
};


class Display: public Observer<Phase> {
	std::vector<TileDisplay> theDisplay;
	public:
		Display(std::vector<Tile> tiles); //set up all tile displays of board
		void notify(Subject<Phase> &notifier) override;

		friend std::ostream &operator<<(std::ostream &out, const Display &display);
	private:
		void updateProgress(int tile, int cell, Colour colour, Progress progress);
};
#endif
