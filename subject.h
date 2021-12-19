#ifndef SUBJECT_H
#define SUBJECT_H
#include "phase.h"
#include <vector>

template <typename PhaseType> class Observer;
class Cell;
class Display;
class Player;

template <typename PhaseType> class Subject {
	std::vector<Observer<PhaseType>*> observers;
	PhaseType phase;
	protected:
		void setPhase(PhaseType currentPhase);
	public:
		void attach(Observer<PhaseType> *observer);
		void notifyObservers();
		PhaseType getPhase() const;
};

template <typename PhaseType>
void Subject<PhaseType>::attach(Observer<PhaseType> *observer) {
	observers.emplace_back(observer);
}

template <typename PhaseType>
void Subject<PhaseType>::notifyObservers() {
	for (auto &observer : observers) observer->notify(*this);
}

template <typename PhaseType>
void Subject<PhaseType>::setPhase(PhaseType currentPhase) {
	phase = currentPhase;
}

template <typename PhaseType>
PhaseType Subject<PhaseType>::getPhase() const {
	return phase;
}
#endif
