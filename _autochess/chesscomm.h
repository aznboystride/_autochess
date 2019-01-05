#ifndef _chesscomm
#define _chesscomm

#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

class MoveStrategy;

class ChessCommunicator {
public:
	virtual void MovePiece() = 0;
};

class EngineCommunicator : public ChessCommunicator {
public:
	EngineCommunicator(MoveStrategy*, string&);
	void MovePiece();
private:
	MoveStrategy* strategy;
	string& applicationPath;
	string fen;
	void CreateChildProcess();
	void CreateChildPipes();
	string ReadFromPipe();
	void WriteToPipe();
};

class GraphicalCommunicator : public ChessCommunicator {
public:
	GraphicalCommunicator(MoveStrategy*);
	void MovePiece();
private:
	MoveStrategy* strategy;
	string fen;
};
#endif
