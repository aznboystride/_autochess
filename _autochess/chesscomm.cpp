#include "chesscomm.h"

void EngineCommunicator::update(Subject *subject)
{
	fen = subject->getFen();
	MovePiece();
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
	CreateProcess(applicationPath.c_str(), NULL, NULL, NULL, TRUE, NULL, NULL, NULL, &startInfo, &procInfo);
}
