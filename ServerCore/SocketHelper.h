#pragma once
class SocketHelper
{		   
public:
	//�񵿱� connect�Լ� ������
	static LPFN_CONNECTEX ConnectEx;
	static LPFN_ACCEPTEX AcceptEx;
	//�񵿱� Disconnect�Լ� ������
	static LPFN_DISCONNECTEX DisconnectEx;
public:
	static bool StartUp();
	static bool CleanUp();
public:
	static bool SetIoControl(SOCKET socket, GUID guid, LPVOID* func);
	static SOCKET CreateSocket();
	static void CloseSocket(SOCKET& socket);
public:
	static bool SetReuseAddress(SOCKET socket, bool enable);
	static bool SetLinger(SOCKET socket, u_short onOff, u_short time);
	static bool SetUpdateAcceptSocket(SOCKET acceptSocket, SOCKET listenSocket);
public:
	static bool Bind(SOCKET socket, SOCKADDR_IN sockAddr);
	//�ƹ� ip�ּ� ���ε�
	static bool BindAny(SOCKET socket, uint16 port);
	static bool Listen(SOCKET socket, int baclog = SOMAXCONN);
	
};

template<typename T>
static inline bool SetSocketOpt(SOCKET socket, int level, int optName, T optVal)
{
	return setsockopt(socket, level, optName, (char*)&optVal, sizeof(T)) != SOCKET_ERROR;
}

