#include "Observer.h"

string Subject::getFen()
{
	return fen;
}

void Subject::setFen(string fen)
{
	this->fen = fen;
	notifyAllObservers();
}

void Subject::attach(Observer *o)
{
	observers.push_back(o);
}

void Subject::notifyAllObservers()
{
	vector<Observer*>::iterator it;
	for (it = observers.begin(); it != observers.end(); it++) {
		(*it)->update(this);
	}
}