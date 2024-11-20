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
	string id = packet.id();
	string pw = packet.pw();

	//wstring_convert<codecvt_utf8<wchar_t>> converter;
	//wstring textId = converter.from_bytes(id);
	//wstring textPw = converter.from_bytes(pw);
	//wcout.imbue(locale("Korean_Korea.949"));

	//cout << "ID : ";
	//
	//cout << textId << endl;
	//
	//cout << "PW : ";
	//cout << textPw << endl;
	

	cout << "ID : ";

	cout << id << endl;

	cout << "PW : ";
	cout << pw << endl;

	return true;
}
			 
