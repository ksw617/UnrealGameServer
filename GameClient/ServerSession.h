#pragma once
#include <PacketSession.h>

class ServerSession : public PacketSession
{
public:
	~ServerSession() { printf("~ServerSession\n"); }
public:
	virtual void OnConnected() override;
	virtual int OnRecvPacket(BYTE* buffer, int len) override;
	virtual void OnSend(int len) override;
	virtual void OnDisconnected() override;
};

