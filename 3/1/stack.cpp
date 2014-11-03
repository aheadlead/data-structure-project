#include "stack.h"
#include <algorithm>

void InitStack(ADT_Stack* S)
{
    *S = std::vector<int>();
    return;
}

void DestroyStack(ADT_Stack* S)
{
    ClearStack(S);
    return;
}

void ClearStack(ADT_Stack* S)
{
    S->clear();
    return;
}

bool StackEmpty(ADT_Stack* S)
{
    return StackLength(S) == 0;
}

size_t StackLength(ADT_Stack* S)
{
    return S->size();
}

void GetTop(ADT_Stack* S, int* e)
{
    *e = *(S->rbegin());
    return;
}

void Push(ADT_Stack* S, int e)
{
    S->push_back(e);
    return;
}

void Pop(ADT_Stack* S, int* e)
{
    GetTop(S, e);
    S->pop_back();
    return;
}

void StackTraverse(ADT_Stack* S, void (*visit)(int))
{
    for_each(S->begin(), S->end(), visit);
    return;
}
