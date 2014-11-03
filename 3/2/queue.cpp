#include "queue.h"
#include <algorithm>

void InitQueue(ADT_Queue* Q)
{
    *Q = std::list<int>();
    return;
}

void DestroyQueue(ADT_Queue* Q)
{
    ClearQueue(Q);
    return;
}

void ClearQueue(ADT_Queue* Q)
{
    Q->clear();
    return;
}

bool QueueEmpty(ADT_Queue* Q)
{
    return QueueLength(Q) == 0;
}

size_t QueueLength(ADT_Queue* Q)
{
    return Q->size();
}

void GetHead(ADT_Queue* Q, int* e)
{
    *e = Q->front();
    return;
}

void EnQueue(ADT_Queue* Q, int e)
{
    Q->push_back(e);
    return;
}

void DeQueue(ADT_Queue* Q, int* e)
{
    GetHead(Q, e);
    Q->pop_front();
    return;
}

void QueueTraverse(ADT_Queue* Q, void (*visit)(int))
{
    for_each(Q->begin(), Q->end(), visit);
}
