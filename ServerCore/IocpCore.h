#pragma once
class IocpObj;

class IocpCore
{
private:
	HANDLE iocpHandle = NULL;
public:
	IocpCore();
	~IocpCore();
public:
	HANDLE GetHandle() const { return iocpHandle; }
public:
	//����Ʈ �����ͷ� ��ȯ
	bool Register(shared_ptr<IocpObj> iocpObj);
	bool ObserveIO(DWORD time = INFINITE);
};

