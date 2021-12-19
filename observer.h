#ifndef OBSERVER_H
#define OBSERVER_H

template <typename PhaseType> class Subject;
class Cell;
class Tile;

template <typename PhaseType> class Observer {
	public:
		virtual void notify(Subject<PhaseType> &notifier) = 0;
		virtual ~Observer() = default;
};
#endif
