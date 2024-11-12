#pragma once
#include "Session.h"

//[2byte : size][2byte : id][���� ������.....]
struct PacketHeader
{
	uint16 size;	//ũ�� 
	uint16 id;		//�з�

};

class PacketSession : public Session
{
public:
	PacketSession() = default;
	virtual ~PacketSession() = default;
public:
	//PacketSession �ּ� �Ѱ��ֱ�
	shared_ptr<PacketSession> GetPacketSession() { return static_pointer_cast<PacketSession>(shared_from_this()); }
public:
	//sealed : ��ӹ��� �ڽ��� �� �Լ��� �������̵�(�����) �Ҽ� ����
	virtual int OnRecv(BYTE* buffer, int len) sealed;
	//�ڽ��� OnRecv ��ſ� OnRecvPacket�� ��� �Ҽ� �ֵ��� ��ȯ
	virtual int OnRecvPacket(BYTE* buffer, int len) abstract;

};

