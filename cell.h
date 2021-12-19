#ifndef CELL_H
#define CELL_H
#include "observer.h"
#include "subject.h"
#include "phase.h"
#include "player.h"

class Cell : public Subject<Phase>, public Observer<Phase> {
	CellType cellType;
	int cellPosition;
	std::map<Colour, bool> progressable; //notify will update these 
	bool adjacentFree; //always true for edges
	Colour playerColour = Colour::NoColour;
	Progress cellProgress = Progress::None;
	public:
		Cell(CellType cellType, int cellPosition);
		void updateProgress(Progress progress, bool bypass, Player* currentPlayer);
		void notify(Subject<Phase> &notifier) override;
		Colour cellOwner();
		Progress getProgress();
	private:
		void build(Player* currentPlayer);
};
#endif
