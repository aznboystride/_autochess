#ifndef _observer
#define _observer

#include <vector>
#include <iterator>
#include <iostream>
#include <string>
#include "chesscomm.h"

using namespace std;

class ChessCommunicator;
class Subject;

class Observer {
public:
	virtual void update(Subject*) = 0;
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
	vector<Observer*> observers;
	string fen;
};
#endif