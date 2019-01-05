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
