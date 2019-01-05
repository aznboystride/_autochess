#ifndef _strategy
#define _strategy

class ChessCommunicator;
class MoveStrategy {
public:
	void MakeMove();
};

class MoveStrategyUCI {
public:
	MoveStrategyUCI(ChessCommunicator*);
private:
	ChessCommunicator* communicator;
};

class MoveStrategyGraphical {
public:
	MoveStrategyGraphical(ChessCommunicator*);
private:
	ChessCommunicator* communicator;
};
#endif