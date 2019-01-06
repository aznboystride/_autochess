#ifndef _chesscomm 
#define _chesscomm

#include <Windows.h>
#include "Observer.h"
#include "strategy.h"

#define BUFFSIZE 4096

class MoveStrategy;

class Subject;

class ChessCommunicator : public Observer {
public:
	virtual void MovePiece() = 0;
};

class EngineCommunicator : public ChessCommunicator {
public:
	EngineCommunicator(string&, Subject*);
	void MovePiece();
	void update(Subject*);
	string getFen();
	string ReadFromPipe();
	void WriteToPipe(string&);
	Subject* getSubject();
private:
	MoveStrategy* strategy;
	Subject* subject;
	string applicationPath;
	string fen;

	HANDLE stdinWr, stdinRd, stdoutWr, stdoutRd;
	void CreateChildProcess();
	void CreateChildPipes();
};

class GraphicalCommunicator : public ChessCommunicator {
public:
	GraphicalCommunicator(Subject*);
	void MovePiece();
	void update(Subject*);
	string getFen();
	Subject* getSubject();
private:
	MoveStrategy* strategy;
	Subject* subject;
	string fen;
};
#endif
