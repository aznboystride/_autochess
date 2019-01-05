#ifndef _chesscomm
#define _chesscomm

#include <Windows.h>
#include "Observer.h"

#ifndef BUFFSIZE
#define BUFFSIZE 4096

class MoveStrategy;

class Subject;

class ChessCommunicator : public Observer {
public:
	virtual void MovePiece() = 0;
};

class EngineCommunicator : public ChessCommunicator {
public:
	EngineCommunicator(string&);
	void MovePiece();
	void update(Subject*);
private:
	MoveStrategy* strategy;
	string applicationPath;
	string fen;

	HANDLE stdinWr, stdinRd, stdoutWr, stdoutRd;
	void CreateChildProcess();
	void CreateChildPipes();
	string ReadFromPipe();
	void WriteToPipe(string&);
};

class GraphicalCommunicator : public ChessCommunicator {
public:
	GraphicalCommunicator();
	void MovePiece();
	void update(Subject*);
private:
	MoveStrategy* strategy;
	string fen;
};
#endif
