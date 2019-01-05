#ifndef _observer
#define _observer

class ChessCommunicator;

class Observer {
public:
	virtual void update() = 0;
protected:
	ChessCommunicator* communicator;
};
#endif