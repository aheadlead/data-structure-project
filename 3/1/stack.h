#ifndef __STACK_H__
#define __STACK_H__

#include <vector>

// std::vector is a standard sequential container.
typedef std::vector<int> ADT_Stack;

void InitStack(ADT_Stack* S);
void DestroyStack(ADT_Stack* S);
void ClearStack(ADT_Stack* S);
bool StackEmpty(ADT_Stack* S);
size_t StackLength(ADT_Stack* S);
void GetTop(ADT_Stack* S, int* e);
void Push(ADT_Stack* S, int e);
void Pop(ADT_Stack* S, int* e);
void StackTraverse(ADT_Stack* S, void (*visit)(int));

#endif // __STACK_H__
