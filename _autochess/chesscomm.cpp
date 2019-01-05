#include "chesscomm.h"

EngineCommunicator::EngineCommunicator(string &applicationPath, Subject *subject)
{
	this->applicationPath = applicationPath;
	this->subject = subject;
	this->subject->attach(this);
	this->strategy = new MoveStrategyUCI(this);
	CreateChildPipes();
	CreateChildProcess();
}

void EngineCommunicator::MovePiece()
{
	strategy->MakeMove();
}

void EngineCommunicator::update(Subject *subject)
{
	fen = subject->getFen();
	MovePiece();
}

string EngineCommunicator::getFen()
{
	return fen;
}

void EngineCommunicator::CreateChildProcess()
{
	STARTUPINFO startInfo;
	PROCESS_INFORMATION procInfo;
	startInfo.cb = sizeof(STARTUPINFO);
	startInfo.dwFlags |= STARTF_USESTDHANDLES;
	startInfo.hStdInput = stdinRd;
	startInfo.hStdOutput = stdoutWr;
	startInfo.hStdError = stdoutWr;
	if (!CreateProcess(applicationPath.c_str(), NULL, NULL, NULL, TRUE, NULL, NULL, NULL, &startInfo, &procInfo)) {
		cout << "Failure creating process " << GetLastError() << endl;
		cin.get();
		exit(1);
	}
	
}

void EngineCommunicator::CreateChildPipes()
{
	BOOL bSuccess = FALSE;
	SECURITY_ATTRIBUTES attr;
	attr.nLength = sizeof(SECURITY_ATTRIBUTES);
	attr.lpSecurityDescriptor = NULL;
	attr.bInheritHandle = TRUE;
	bSuccess = CreatePipe(&stdinRd, &stdinWr, &attr, 0);
	
	if (!bSuccess) {
		cout << "Failure creating pipe " << GetLastError() << endl;
		cin.get();
		exit(1);
	}

	bSuccess = CreatePipe(&stdoutRd, &stdoutWr, &attr, 0);
	if (!bSuccess) {
		cout << "Failure creating pipe " << GetLastError() << endl;
		cin.get();
		exit(1);
	}

	bSuccess = SetHandleInformation(stdoutRd, HANDLE_FLAG_INHERIT, 0);
	if (!bSuccess) {
		cout << "Failure setting handle information " << GetLastError() << endl;
		cin.get();
		exit(1);
	}

	bSuccess = SetHandleInformation(stdinWr, HANDLE_FLAG_INHERIT, 0);
	if (!bSuccess) {
		cout << "Failure setting handle information " << GetLastError() << endl;
		cin.get();
		exit(1);
	}
}

string EngineCommunicator::ReadFromPipe()
{
	DWORD bytesWritten;
	BOOL bSuccess = FALSE;
	CHAR buff[BUFFSIZE];
	bSuccess = ReadFile(stdoutRd, buff, BUFFSIZE, &bytesWritten, NULL);
	if (!bSuccess) {
		cout << "Failure to read from stdoutRd " << GetLastError() << endl;
		cin.get();
		exit(1);
	}
	return string(buff);
}

void EngineCommunicator::WriteToPipe(string& str)
{
	DWORD bytesWritten;
	BOOL bSuccess = FALSE;
	bSuccess = WriteFile(stdinWr, str.c_str(), BUFFSIZE, &bytesWritten, NULL);
	if (!bSuccess) {
		cout << "Failure to writefile to stdinWr " << GetLastError() << endl;
		cin.get();
		exit(1);
	}
}

Subject * EngineCommunicator::getSubject()
{
	return subject;
}

GraphicalCommunicator::GraphicalCommunicator(Subject* subject)
{
	this->subject = subject;
	this->subject->attach(this);
	strategy = new MoveStrategyGraphical(this);
}

void GraphicalCommunicator::update(Subject *subject)
{
	fen = subject->getFen();
	MovePiece();
}

string GraphicalCommunicator::getFen()
{
	return fen;
}

Subject * GraphicalCommunicator::getSubject()
{
	return subject;
}
