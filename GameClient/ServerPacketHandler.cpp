#include "pch.h"
#include "ServerPacketHandler.h"

#include "SceneManager.h" 
#include "GameManager.h"


#include <locale>
#include <codecvt>
#include <string>

void ServerPacketHandler::Init()
{
	PacketHandler::Init();

	//Recv
	packetHandlers[S_LOGIN] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len) 
		{  return HandlePacket<Protocol::S_Login>(Handle_S_LOGIN, session, buffer, len); };

	packetHandlers[S_REGISTER] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_Register>(Handle_S_REGISTER, session, buffer, len); 	};

	packetHandlers[S_ENTERGAME] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_EnterGame>(Handle_S_ENTERGAME, session, buffer, len); };

	packetHandlers[S_ENTERROOM] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_EnterRoom>(Handle_S_ENTERROOM, session, buffer, len); };

	packetHandlers[S_ENTERNEWBIE] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_EnterNewbie>(Handle_S_ENTERNEWBIE, session, buffer, len); };

	packetHandlers[S_CHAT] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_Chat>(Handle_S_CHAT, session, buffer, len); };
}


bool Handle_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int len)
{
	printf("Handle_INVALID\n");
	return false;
}

bool Handle_S_LOGIN(shared_ptr<PacketSession>& session, Protocol::S_Login& packet)
{
	if (packet.success())
	{
		SceneManager::Get().LoadScene(SCENE_ID::ENTERGAME);
	}
	else
	{
		SceneManager::Get().LoadScene(SCENE_ID::REGISTER);
	}

	return true;
}

bool Handle_S_REGISTER(shared_ptr<PacketSession>& session, Protocol::S_Register& packet)
{
	if (packet.success())
	{
		SceneManager::Get().LoadScene(SCENE_ID::LOGIN);
	}
	else
	{
		SceneManager::Get().LoadScene(SCENE_ID::REGISTER);
	}

	return true;
}

bool Handle_S_ENTERGAME(shared_ptr<PacketSession>& session, Protocol::S_EnterGame& packet)
{
	if (packet.success())
	{
		GameManager::Get().SetID(packet.playerindex());

		for (auto& value : packet.roomids())
		{
			GameManager::Get().SetGameRoom(value);
		}
		SceneManager::Get().LoadScene(SCENE_ID::SELECTROOM);
	}

	return true;
}

bool Handle_S_ENTERROOM(shared_ptr<PacketSession>& session, Protocol::S_EnterRoom& packet)
{	 
	for (auto& player : packet.players())
	{
		const Protocol::Player& p = player;
		wstring_convert<codecvt_utf8<wchar_t>> converter;
		wstring name = converter.from_bytes(p.name());

		wcout << name << endl;
	}


	SceneManager::Get().LoadScene(SCENE_ID::ENTERROOM);


	return true;

}

bool Handle_S_ENTERNEWBIE(shared_ptr<PacketSession>& session, Protocol::S_EnterNewbie& packet)
{
	auto& p = packet.player();
	
	wstring_convert<codecvt_utf8<wchar_t>> converter;
	wstring name = converter.from_bytes(p.name());
	
	
	wcout << name << endl;

	return true;
}

bool Handle_S_CHAT(shared_ptr<PacketSession>& session, Protocol::S_Chat& packet)
{
	//Todo

	wstring_convert<codecvt_utf8<wchar_t>> converter;
	wstring msg = converter.from_bytes(packet.msg());

	wcout << msg << endl;

	return true;
}
