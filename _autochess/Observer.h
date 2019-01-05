#ifndef _observer
#define _observer

#include <vector>
#include <iostream>
#include <string>
using namespace std;

class ChessCommunicator;

class Observer {
public:
	virtual void update() = 0;
protected:
	ChessCommunicator* communicator;
};

class Subject {
public:
	string getFen();
	void setFen(string);
	void attach(Observer*);
	void notifyAllObservers();
private:
	vector<Observer> observers;
	string fen;
};
#endif