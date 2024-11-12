#pragma once

class TaskQueue;
class Task;

struct TaskData
{
    // TaskData ����ü�� ������: TaskQueue�� ���� weak_ptr�� Task�� ���� shared_ptr�� �޾� ��� ������ �ʱ�ȭ�մϴ�.
    TaskData(weak_ptr<TaskQueue> owner, shared_ptr<Task> task) : owner(owner), task(task) {    }

    weak_ptr<TaskQueue> owner; // TaskQueue�� ���� ������ �����մϴ�. ���� ��ü�� ������� �����ϰ� ���� ����.
    shared_ptr<Task> task; // Task�� ���� ���� ������. Task�� ���� �ֱ⸦ �����մϴ�.
};

struct TimerItem
{
    // TimerItem���� ���ϱ� ���� ������ �����ε�. ���� �ð�(executeTick)�� �������� ���մϴ�.
    bool operator < (const TimerItem& other) const
    {
        return executeTick > other.executeTick;
    }

    UINT64 executeTick = 0; // �� Ÿ�̸� �������� ����� �ð� (�ý��� ƽ ����)
    TaskData* taskData = nullptr; // ������ TaskData�� ������

};

class TaskTimer
{
private:
    TaskTimer() = default;
    ~TaskTimer() = default;
public:
    static TaskTimer& Get()
    {
        static TaskTimer instance;
        return instance;
    }
public:
    TaskTimer(const TaskTimer&) = delete;
    TaskTimer& operator= (const TaskTimer&) = delete;
private:
    shared_mutex rwLock; // �б�/���� ����� ���� shared_mutex
    priority_queue<TimerItem> items; // TimerItem���� �켱���� ť�� �����մϴ�.
    atomic<bool> distributing = false; // ���� Distribute �۾��� ���� ������ ��Ÿ���� �÷���
public:
    void Reserve(UINT64 tickAfter, weak_ptr<TaskQueue> owner, shared_ptr<Task> task); // ������ �ð� �Ŀ� Task�� �����ϱ� ���� �����մϴ�.
    void Distribute(UINT64 now); // ����� Task�� �� ���� �ð�(now)�� �����ؾ� �� Task���� �����մϴ�.
    void Clear(); // ��� ����� Task���� ����ϰ� ���� ���ҽ��� �����մϴ�.

};