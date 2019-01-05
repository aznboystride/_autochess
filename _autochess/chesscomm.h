#ifndef _chesscomm
#define _chesscom

#include <Windows.h>

class MoveStrategy;

class ChessCommunicator {
public:
	virtual void MovePiece() = 0;
};

class EngineCommunicator: public ChessCommunicator {
public:
	EngineCommunicator(MoveStrategy*, TCHAR*, TCHAR*);
	void MovePiece();
private:
	MoveStrategy* strategy;
};

class GraphicalCommunicator : public ChessCommunicator {
public:
	GraphicalCommunicator(MoveStrategy*, TCHAR*, TCHAR*);
	void MovePiece();
private:
	MoveStrategy* strategy;
};
#endif
