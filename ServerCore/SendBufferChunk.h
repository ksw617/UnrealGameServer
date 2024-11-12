#pragma once

class SendBufferChunk : public enable_shared_from_this<SendBufferChunk>
{
	enum { BUFFER_SIZE = 0x10000 };
private:
	vector<BYTE> buffer;
	bool open = false;
	int usedsize = 0;
public:
	SendBufferChunk() : buffer(BUFFER_SIZE) {}
	~SendBufferChunk() {}
public:
	bool IsOpen() const { return open; }
	int FreeSize() const { return buffer.size() - usedsize; }
public:
	void Init();
	shared_ptr<class SendBuffer> Open(int size);
	//�پ��� �� ������ �˷� �ֱ�
	void Close(int size);
};
