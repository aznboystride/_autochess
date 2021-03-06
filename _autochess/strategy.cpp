#include "strategy.h"

MoveStrategyUCI::MoveStrategyUCI(ChessCommunicator *communicator)
{
	this->communicator = communicator;
}

void MoveStrategyUCI::MakeMove()
{
	EngineCommunicator* com = ((EngineCommunicator*)communicator);
	string instr = com->getFen();
	com->WriteToPipe(instr);
	string bestMove = com->ReadFromPipe();
	com->getSubject()->setFen(bestMove);
}

MoveStrategyGraphical::MoveStrategyGraphical(ChessCommunicator *communicator)
{
	this->communicator = communicator;
}

void MoveStrategyGraphical::MakeMove()
{
	GraphicalCommunicator* comm = (GraphicalCommunicator*)communicator;
	cout << "Made Graphical Move: " << comm->getFen() << endl;
}
