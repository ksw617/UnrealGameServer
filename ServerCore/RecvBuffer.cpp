#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(uint32 size) : bufferSize(size)
{
    //��û���� ū ���� Ȯ���� �ֱ�
    capacity = bufferSize * BUFFER_COUNT;
    buffer.resize(capacity); // [][][][] capacity��ŭ �迭 �Ҵ�
}

RecvBuffer::~RecvBuffer()
{
}

void RecvBuffer::Clear()
{
    int dataSize = DataSize();
    if (dataSize == 0) 
    {
        readPos = 0;
        writePos = 0;
    }
    else  
    {
        //[64kb][64kb][64kb][64kb][64kb][64kb][64kb][64kb][64kb][r..w]
        //[r..w][64kb][64kb][64kb][64kb][64kb][64kb][64kb][64kb][64kb]
        if (FreeSize() < bufferSize)
        {
            //���� ����
            memcpy(&buffer[0], &buffer[readPos], dataSize);
            readPos = 0;
            writePos = dataSize;
        }
      
    }
}

bool RecvBuffer::OnRead(uint32 readBytes)
{
   
    if (readBytes > DataSize())
        return false;
    
    readPos += readBytes;
    return true;
}

bool RecvBuffer::OnWrite(uint32 writeBytes)
{
    if (writeBytes > FreeSize())
        return false;

    writePos += writeBytes;
    return true;
}
