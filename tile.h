#ifndef TILE_H
#define TILE_H
#include <vector>
#include "observer.h"
#include "subject.h"
#include "phase.h"

class Tile : public Subject<Phase>, public Observer<Phase> {
	int tilePosition;
	ResourceType resource;
	int resourceRoll;
	bool goose;
	std::vector<Colour> players;
	public:
		Tile(ResourceType resource, int resourceRoll, int tilePosition);
		void distributeResources(int roll);
		void toggleGoose();
		void notify(Subject<Phase> &notifier) override;
		int getPosition();
		ResourceType getResource();
		int getRoll();
		bool hasGoose();
		std::vector<Colour> getPlayers();
};
#endif
