#include "pch.h"
#include "ClientPacketHandler.h"

#include "GameManager.h"
#include "ClientPacketHandler.h"

#include <locale>
#include <codecvt>
#include <string>

#include "Player.h"

void ClientPacketHandler::Init()
{
	PacketHandler::Init();

	//Recv
	packetHandlers[C_LOGIN] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{
			return HandlePacket<Protocol::C_Login>(Handle_C_LOGIN, session, buffer, len);
		};
	packetHandlers[C_REGISTER] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{
			return HandlePacket<Protocol::C_Register>(Handle_C_REGISTER, session, buffer, len);
		};

	packetHandlers[C_ENTERGAME] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{
			return HandlePacket<Protocol::C_EnterGame>(Handle_C_ENTERGAME, session, buffer, len);
		};
}

bool Handle_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int len)
{
	printf("Handle_INVALID\n");
	return false;
}

bool Handle_C_LOGIN(shared_ptr<PacketSession>& session, Protocol::C_Login& packet)
{
	string id = packet.id();
	string pw = packet.pw(); 

	Protocol::S_Login sendPacket;

	bool success = GameManager::Get().CheckUser(id);
	
	if (success)
	{
		success = (pw == GameManager::Get().GetPW(id));
	}

	sendPacket.set_success(success);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);
	

	return true;
}

bool Handle_C_REGISTER(shared_ptr<PacketSession>& session, Protocol::C_Register& packet)
{
	string id = packet.id();

	Protocol::S_Register sendPacket;

	bool success = !GameManager::Get().CheckUser(id);

	if (success)
	{
		string pw = packet.pw();
		string name = packet.name();

		//Ãß°¡
		GameManager::Get().AddUser(id, pw, name);
	}

	sendPacket.set_success(success);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);
	
	return true;
}

bool Handle_C_ENTERGAME(shared_ptr<PacketSession>& session, Protocol::C_EnterGame& packet)
{
	//Todo
	auto& p = packet.player();

	wstring_convert<codecvt_utf8<wchar_t>> converter;
	wstring name = converter.from_bytes(p.name());
	
	shared_ptr<Player> player = make_shared<Player>(session, name, (PLAYER_TYPE)p.type());
	GameManager::Get().AddPlayer(player);


	return true;
}
			 
