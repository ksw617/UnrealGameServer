#pragma once
#include "Task.h"
#include "TaskTimer.h"

class TaskQueue : public enable_shared_from_this<TaskQueue>
{
protected:
    shared_mutex rwLock;
    atomic<int> taskCount = 0;
    queue<shared_ptr<Task>> tasks;
public:

    void CallAsync(Callback&& callback)
    {
        Push(make_shared<Task>(std::move(callback)));
    }

    template<typename ReturnType, typename ClassType, typename... Args>
    void CallAsync(ReturnType(ClassType::* memFunc)(Args...), Args... args)
    {
        shared_ptr<ClassType> pointer = static_pointer_cast<ClassType>(shared_from_this());
        Push(make_shared<Task>(pointer, memFunc, std::forward<Args>(args)...));
    }
    // ������ �ð� �Ŀ� �ݹ��� �����ϱ� ���� TaskTimer�� ����ϴ� �޼���
    void CallTimer(UINT64 tickAfter, Callback&& callback)
    {
        shared_ptr<Task> task = make_shared<Task>(std::move(callback));
        TaskTimer::Get().Reserve(tickAfter, shared_from_this(), task);
    }
    // ������ �ð� �Ŀ� Ŭ������ ��� �Լ��� �����ϱ� ���� TaskTimer�� ����ϴ� ���ø� �޼���
    template<typename ReturnType, typename ClassType, typename... Args>
    void CallTimer(UINT64 tickAfter, ReturnType(ClassType::* memFunc)(Args...), Args... args)
    {
        shared_ptr<ClassType> pointer = static_pointer_cast<ClassType>(shared_from_this());
        shared_ptr<Task> task = make_shared<Task>(pointer, memFunc, std::forward<Args>(args)...);
        TaskTimer::Get().Reserve(tickAfter, shared_from_this(), task);
    }

public:
    void Push(shared_ptr<Task> task, bool pushOnly = false);
public:
    void Execute();
    void Clear();
};
