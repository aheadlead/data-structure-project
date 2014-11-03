#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <list>

typedef std::list<int> ADT_Queue;

void InitQueue(ADT_Queue* Q);
void DestroyQueue(ADT_Queue* Q);
void ClearQueue(ADT_Queue* Q);
bool QueueEmpty(ADT_Queue* Q);
size_t QueueLength(ADT_Queue* Q);
void GetHead(ADT_Queue* Q, int* e);
void EnQueue(ADT_Queue* Q, int e);
void DeQueue(ADT_Queue* Q, int* e);
void QueueTraverse(ADT_Queue* Q, void (*visit)(int));

#endif // __QUEUE_H__
