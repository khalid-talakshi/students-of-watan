#include "tile.h"

Tile::Tile(ResourceType resource, int resourceRoll, int tilePosition) :
	tilePosition{tilePosition},
	resource{resource},
	resourceRoll{resourceRoll},
	goose{false},
	players{}
{}

void Tile::distributeResources(int roll) 
{
	if (!(this->goose) && (this->resourceRoll == roll))
	{
		Phase currentPhase;
		currentPhase.phase = TurnPhase::DistributeResources;
		currentPhase.resource = this->resource;

		this->setPhase(currentPhase);

		this->notifyObservers();
	}
}

void Tile::toggleGoose()
{
	this->goose = !(this->goose);

	Phase currentPhase;
	currentPhase.phase = TurnPhase::MoveGeese;
	currentPhase.position = this->tilePosition;
	currentPhase.hasGeese = this->goose;

	this->setPhase(currentPhase);
	this->notifyObservers();
}

void Tile::notify(Subject<Phase> &notifier)
{
	if (notifier.getPhase().phase == TurnPhase::Progress)
	{
		players.emplace_back(notifier.getPhase().currentPlayer);
	}
}

int Tile::getPosition()
{
	return this->tilePosition;
}

ResourceType Tile::getResource()
{
	return this->resource;
}

int Tile::getRoll()
{
	return this->resourceRoll;
}

bool Tile::hasGoose()
{
	return this->goose;
}

std::vector<Colour> Tile::getPlayers()
{
	return this->players;
}
