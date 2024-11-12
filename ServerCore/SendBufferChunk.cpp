#include "pch.h"
#include "SendBufferChunk.h"
#include "SendBuffer.h"

void SendBufferChunk::Init()
{
    //���� ���丮�� �� �̱� ������ó�� ����ϸ� ��
    //���� �ʱ�ȭ
    open = false;
    usedsize = 0;
}

shared_ptr<SendBuffer> SendBufferChunk::Open(int size)
{
    //����ҷ��� �����Ͱ� BUFFER_SIZE���� ũ��
    if (size > BUFFER_SIZE)
        return nullptr;

    //����ϰ� �ִ� ���¶��
    if (open)
        return nullptr;

    //����ҷ��� �����Ͱ� ���� �������� ũ��
    if (size > FreeSize())
        return nullptr;

    //����ϰڴ� ǥ��
    open = true;

    //���� Ȯ��
    //size == 4096
    //               [  4096                                    ]
    //[x][x][x][x][x][usedSize][][][][][][][][][][][][][][][][][]
    return make_shared<SendBuffer>(shared_from_this(), &buffer[usedsize], size);
}

void SendBufferChunk::Close(int size)
{
    //����ϴ� ���°� �ƴ϶��
    if (!open)
        return;

    //���� ����� ������ ��ŭ �޸� �ڸ� �Ű��ֱ�
    usedsize += size;   //size == 10
   //               [  4096                                    ]
   //[x][x][x][x][x][usedSize][][][][][][][][][][][][][][][][][]

   //               [  4096                                              ]
   //[x][x][x][x][x][x][x][x][x][x][x][x][x][x][x][usedSize][][][][][][][]

    //��� �����ٰ� �ݾ��ְ�
    open = false;
}
