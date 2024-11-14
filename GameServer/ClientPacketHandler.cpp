#include "pch.h"
#include "ClientPacketHandler.h"

#include <locale>
#include <codecvt>
#include <string>

void ClientPacketHandler::Init()
{
	PacketHandler::Init();

	//Recv
	packetHandlers[C_LOGIN] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{
			return HandlePacket<Protocol::C_Login>(Handle_C_LOGIN, session, buffer, len);
		};
}

bool Handle_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int len)
{
	printf("Handle_INVALID\n");
	return false;
}

bool Handle_C_LOGIN(shared_ptr<PacketSession>& session, Protocol::C_Login& packet)
{
	string text = packet.name();

	wstring_convert<codecvt_utf8<wchar_t>> converter;
	wstring name = converter.from_bytes(text);
	cout << "Name : ";
	wcout.imbue(locale("Korean_Korea.949"));
	wcout << name << endl;

	return true;
}

