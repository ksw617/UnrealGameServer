#include "pch.h"
#include "SendBuffer.h"
#include "SendBufferChunk.h"

SendBuffer::SendBuffer(shared_ptr<SendBufferChunk> chunk, BYTE* start, int size)
	:sendBufferChunk(chunk), buffer(start), freeSize(size)
{
}

SendBuffer::~SendBuffer()
{
}

bool SendBuffer::Close(int usedSize)
{
	//���� ������ ����� �ͺ��� �۴ٸ�
	if (freeSize < usedSize)
		return false;

	//����� ������ �־��ְ�
	writeSize = usedSize;

	//����ŭ �ݾ��ְ�
	sendBufferChunk->Close(usedSize);

	return true;
}

