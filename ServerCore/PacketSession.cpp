#include "pch.h"
#include "PacketSession.h"

//������ �����Ͱ� 21byte
//�νĿ����� 4byte (2byte:size, 2byte:id)
//[0]...........................[25][26]..........................[50] 
//[packet                          ][packet                          ]
//[[size(2byte)][id(2byte)][data21]][[size(2byte)][id(2byte)][data21]] 
int PacketSession::OnRecv(BYTE* buffer, int len)
{
	//ó���� ����
	int processLen = 0;

	while (true)
	{
		//��Ŷ�� �ΰ� �޴´ٸ�
		//50 		 = 50  - 0
		int dataSize = len - processLen;
		//25
	//	int dataSize = 50 -  25


		//��� 4byte�� ����� size�� id�� �˼� �����ϱ�
		//50		 < 4 == sizeof(PacketHeader)
		if (dataSize < sizeof(PacketHeader))
			break;
								
		//                 ���� [2][2]
		//[size(2)][id(2)]	= *( �� ��ȯ     )(buffer[0]��° �ּ�)
		PacketHeader header = *(PacketHeader*)(&buffer[processLen]);

		//[��Ŷ 1][��Ŷ 2]
		//OnRecvPacket ���ٰ� (��Ŷ�� ���� �ּ�, ũ��)
		//ū�����͸� �ɰ��� �ѱ�
		//50byte �޾Ҵٸ�
		//header : 21 + 4
		OnRecvPacket(&buffer[processLen], header.size);
		
		//[��Ŷ 1���� �켱 ó��]
		//[��Ŷ 2���� ���� while��]

		//25����Ʈ ó���ϰ�
		processLen += header.size;
	}

	return processLen;
}
