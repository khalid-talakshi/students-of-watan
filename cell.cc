#include "cell.h"

Cell::Cell(CellType cellType, int cellPosition) :
	cellType{cellType},
	cellPosition{cellPosition},
	progressable{},
	adjacentFree{true},
	playerColour{Colour::NoColour},
	cellProgress{Progress::None}
{
	progressable.emplace(Colour::Blue, false);
	progressable.emplace(Colour::Red, false);
	progressable.emplace(Colour::Orange, false);
	progressable.emplace(Colour::Yellow, false);
}

void Cell::updateProgress(Progress progress, bool bypass, Player* currentPlayer)
{
	if (adjacentFree && ((bypass && this->cellProgress == Progress::None) || this->progressable[currentPlayer->getColour()]))
	{
		this->build(currentPlayer);
	}
}

void Cell::notify(Subject<Phase> &notifier)
{
	if (notifier.getPhase().phase == TurnPhase::DistributeResources)
	{
		Phase currentPhase = notifier.getPhase();
		currentPhase.phase = TurnPhase::DistributeResourcesPlayer;
		currentPhase.cellProgress = this->cellProgress;
		this->setPhase(currentPhase);
		this->notifyObservers();
	}
	else if (notifier.getPhase().phase == TurnPhase::Progress)
	{
		Progress currentProgress = notifier.getPhase().cellProgress;	
		if (currentProgress == Progress::Goals)
		{
			if (this->cellProgress == Progress::None) 
			{
				this->progressable[notifier.getPhase().currentPlayer] = this->adjacentFree;
			}

			Phase currentPhase = notifier.getPhase();
			currentPhase.phase = TurnPhase::updateEdgeProgressability;
			this->setPhase(currentPhase);
			this->notifyObservers();
		}
		else if (currentProgress == Progress::Assignment)
		{
			if (this->cellProgress == Progress::None)
			{
				this->progressable[notifier.getPhase().currentPlayer] = true;
			}

			Phase currentPhase = notifier.getPhase();
			currentPhase.phase = TurnPhase::updateVertexProgressability;
			this->setPhase(currentPhase);
			this->notifyObservers();
		}
	}
	else if (notifier.getPhase().phase == TurnPhase::updateEdgeProgressability)
	{
		if (this->cellPosition != notifier.getPhase().position)
		{
			if (this->cellProgress == Progress::None)
			{
				this->progressable[notifier.getPhase().currentPlayer] = true;
			}
		}
	}
	else if (notifier.getPhase().phase == TurnPhase::updateVertexProgressability)
	{
		if (this->cellPosition != notifier.getPhase().position)
		{
			this->adjacentFree = false;
			this->progressable[Colour::Blue] = false;
			this->progressable[Colour::Red] = false;
			this->progressable[Colour::Orange] = false;
			this->progressable[Colour::Yellow] = false;
		}
	}
}

Colour Cell::cellOwner() 
{
	return this->playerColour;
}

void Cell::build(Player* currentPlayer)
{
	Phase currentPhase;
	currentPhase.phase = TurnPhase::Progress;
	currentPhase.currentPlayer = currentPlayer->getColour();
	currentPhase.position = this->cellPosition;

	if (this->cellType == CellType::Edge)
	{
		this->progressable[Colour::Blue] = false;
		this->progressable[Colour::Red] = false;
		this->progressable[Colour::Orange] = false;
		this->progressable[Colour::Yellow] = false;
		this->playerColour = currentPlayer->getColour();
		this->cellProgress = Progress::Goals;
		currentPhase.cellProgress = Progress::Goals;
		this->attach(currentPlayer);
	}
	else
	{
		if (this->cellProgress == Progress::None)
		{
			this->progressable[Colour::Blue] = false;
			this->progressable[Colour::Red] = false;
			this->progressable[Colour::Orange] = false;
			this->progressable[Colour::Yellow] = false;
			this->progressable[currentPlayer->getColour()] = true;
			this->playerColour = currentPlayer->getColour();
			this->cellProgress = Progress::Assignment;
			currentPhase.cellProgress = Progress::Assignment;
			this->attach(currentPlayer);
		}
		else if (this->cellProgress == Progress::Assignment)
		{
			this->cellProgress = Progress::Midterm;
			currentPhase.cellProgress = Progress::Midterm;
		}
		else if (this->cellProgress == Progress::Midterm)
		{
			this->progressable[currentPlayer->getColour()] = false;
			this->cellProgress = Progress::Exam;
			currentPhase.cellProgress = Progress::Exam;
		}
	}

	this->setPhase(currentPhase);
	this->notifyObservers();
}

Progress Cell::getProgress() {
	return this->cellProgress;
}
