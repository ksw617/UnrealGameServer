#include "pch.h"
#include "TaskTimer.h"
#include "TaskQueue.h"


void TaskTimer::Reserve(UINT64 tickAfter, weak_ptr<TaskQueue> owner, shared_ptr<Task> task)
{
    const UINT64 executeTick = GetTickCount64() + tickAfter; // ���� �ð� ���
    TaskData* taskData = new TaskData(owner, task); // ���ο� TaskData �ν��Ͻ� ����

    unique_lock<shared_mutex> lock(rwLock); // ���� ���
    items.push(TimerItem{ executeTick, taskData }); // �켱���� ť�� Ÿ�̸� ������ �߰�
}

void TaskTimer::Distribute(UINT64 now)
{
    if (distributing.exchange(true) == true) // �̹� Distribute �۾��� ���� ������ Ȯ��
        return;

    vector<TimerItem> timerItems; // ������ Ÿ�̸� �����۵��� �ӽ� ������ ����

    {
        unique_lock<shared_mutex> lock(rwLock); // ���� ���

        while (items.empty() == false) // �켱���� ť�� ������� ���� ����
        {
            const TimerItem& timerItem = items.top(); // ���� �켱������ ���� ������ Ȯ��
            if (now < timerItem.executeTick) // ���� �ð��� ���� �ð����� �̸��� �ߴ�
                break;

            timerItems.push_back(timerItem); // ������ �������� ���Ϳ� �߰�
            items.pop(); // ť���� ������ ����
        }
    }

    for (TimerItem& item : timerItems) // ��� ������ �����ۿ� ����
    {
        if (shared_ptr<TaskQueue> owner = item.taskData->owner.lock()) // TaskQueue�� ������ �����ϴ��� Ȯ��
            owner->Push(item.taskData->task); // TaskQueue�� Task �߰�

        delete item.taskData; // TaskData �ν��Ͻ� ����

    }

    distributing.store(false); // Distribute �۾� �Ϸ�
}

void TaskTimer::Clear()
{
    unique_lock<shared_mutex> lock(rwLock); // ���� ���
    while (items.empty() == false) // �켱���� ť�� ������� ���� ����
    {
        const TimerItem& timerItem = items.top(); // ���� �켱������ ���� ������ Ȯ��
        delete timerItem.taskData; // TaskData �ν��Ͻ� ����
        items.pop(); // ť���� ������ ����
    }
}