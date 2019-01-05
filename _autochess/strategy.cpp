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
