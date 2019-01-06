#ifndef _strategy
#define _strategy

#include "chesscomm.h"

class MoveStrategy {
public:
	virtual void MakeMove() = 0;
};

class MoveStrategyUCI: public MoveStrategy {
public:
	MoveStrategyUCI(ChessCommunicator*);
	void MakeMove();
private:
	ChessCommunicator* communicator;
};

class MoveStrategyGraphical: public MoveStrategy {
public:
	MoveStrategyGraphical(ChessCommunicator*);
	void MakeMove();
private:
	ChessCommunicator* communicator;
};
#endif