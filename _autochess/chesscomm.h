#ifndef _chesscomm
#define _chesscomm

#include <Windows.h>
#include "Observer.h"

class MoveStrategy;

class Subject;

class ChessCommunicator : public Observer {
public:
	virtual void MovePiece() = 0;
};

class EngineCommunicator : public ChessCommunicator {
public:
	EngineCommunicator(MoveStrategy*, string&);
	void MovePiece();
	void update(Subject*);
private:
	MoveStrategy* strategy;
	string& applicationPath;
	string fen;

	HANDLE stdinWr, stdinRd, stdoutWr, stdoutRd;
	void CreateChildProcess();
	void CreateChildPipes();
	string ReadFromPipe();
	void WriteToPipe();
};

class GraphicalCommunicator : public ChessCommunicator {
public:
	GraphicalCommunicator(MoveStrategy*);
	void MovePiece();
	void update(Subject*);
private:
	MoveStrategy* strategy;
	string fen;
};
#endif
