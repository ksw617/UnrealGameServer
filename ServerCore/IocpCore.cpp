#include "pch.h"
#include "IocpCore.h"
#include "IocpEvent.h"
#include "IocpObj.h"
#include "Session.h"

IocpCore::IocpCore()
{
    iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, NULL);
}

IocpCore::~IocpCore()
{
    CloseHandle(iocpHandle);
}

//수정
//스마트 포인터로 수정
bool IocpCore::Register(shared_ptr<IocpObj> iocpObj)
{
   return CreateIoCompletionPort(iocpObj->GetHandle(), iocpHandle, 0, 0);
}

bool IocpCore::ObserveIO(DWORD time)
{
    DWORD bytesTransferred = 0;
    ULONG_PTR key = 0;
    IocpEvent* iocpEvent = nullptr;

    if (GetQueuedCompletionStatus(iocpHandle, &bytesTransferred, &key, (LPOVERLAPPED*)&iocpEvent, INFINITE))
    {

        //스마트 포인터로 변환
        shared_ptr<IocpObj> iocpObj = iocpEvent->owner;
        iocpObj->ObserveIO(iocpEvent, bytesTransferred);

    }
    else
    {
        switch (GetLastError())
        {
        case WAIT_TIMEOUT:
            return false;
        default:
            //스마트 포인터로 변환
            shared_ptr<IocpObj> iocpObj = iocpEvent->owner;
            iocpObj->ObserveIO(iocpEvent, bytesTransferred);
            break;
        }
        return false;
    }

    return true;

}
