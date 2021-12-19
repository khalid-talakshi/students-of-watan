#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include <map>
#include "observer.h"
#include "subject.h"
#include "phase.h"

template <typename PhaseType> class Observer;
class Cell;

class Player: public Observer<Phase> {
        std::map<Progress, std::vector<int>> completedCriteria;
        std::vector<int> completedGoals;
        std::map<ResourceType, int> resources;
        Colour colour;
        public:
                Player(Colour pColour);
                void addResources(ResourceType res, int amount);
                void notify(Subject<Phase> &notifier) override;
                int rollDice(bool loaded);
                std::map<ResourceType, int> getResources();
                void addGoals(int cellToAdd);
                void addCriteria(int cellToAdd, Progress cellProgress);
                void setResource(ResourceType res, int amount);
                void removeResource(ResourceType res, int amount);
                std::map<Progress, std::vector<int>> getCriteria();
                std::vector<int> getGoals();
                bool hasEnoughResources(Cell cell, std::string buildType);
                ResourceType loseRandomResource(int amount);
                Colour getColour();
                std::string getColourStr();
                void printStatus();
                void printCompletions();
                std::string getStatus();
                std::string getCriteriaPairs();
                std::string progressToString(Progress progress);
                void addResource(ResourceType res, int amount);
                int getResourceCount();
                int getCriteriaCount();
                void removeCriteria(int criteriaToRemove, Progress progress);
        private:
                

};
#endif
