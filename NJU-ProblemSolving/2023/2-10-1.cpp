#include "Core.h"
#include <cstdio>

void MyPriority_Queue::heapify(int index)
{
    int tn = index;
    if (index * 2 <= size && container[tn].priority < container[index * 2].priority)
        tn = index * 2;
    if (index * 2 + 1 <= size && container[tn].priority < container[index * 2 + 1].priority)
        tn = index * 2 + 1;
    if (index != tn)
    {
        std::swap(container[index], container[tn]);
        heapify(tn);
    }
}

void MyPriority_Queue::build_heap()
{
    for (int i = size >> 1; i >= 1; --i)
        heapify(i);
}

void MyPriority_Queue::push(int value, int priority)
{
    size++;
    container.push_back({value, priority});
    int cur = size;
    while (cur > 1 && container[cur].priority > container[cur / 2].priority)
    {
        std::swap(container[cur], container[cur / 2]);
        cur >>= 1;
    }
}

void MyPriority_Queue::pop()
{
    if (size == 0)
        return;
    std::swap(container[1], container[size]);
    container.pop_back();
    size--;
    heapify(1);
}

int MyPriority_Queue::top(int &value, int &priority)
{
    if (size == 0)
        return -1;
    value = container[1].value;
    priority = container[1].priority;
    return 0;
}

int MyPriority_Queue::empty()
{
    return size == 0;
}