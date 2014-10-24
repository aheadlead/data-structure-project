#include "List.h"
#include <assert.h>

Status InitList_Sq(SqList *L)
{
    L->elem = (Elemtype*)malloc(sizeof(Elemtype)*LIST_INIT_SIZE);
    if (NULL == L->elem)
        return OVERFLOW;
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}

void DestroyList_Sq(SqList *L)
{
    free(L->elem);
    free(L);
}

void ClearList_Sq(SqList *L)
{
    DestroyList_Sq(L);
    InitList_Sq(L);
}

int ListEmpty_Sq(SqList *L)
{
    return L->length == 0;
}

size_t ListLength_Sq(SqList *L)
{
    return L->length;
}

Status GetElem_Sq(SqList *L, size_t i, Elemtype* e)
{
    i--;
    assert(i < L->length);
    *e = *(L->elem + i);
    return OK;
}

size_t LocateElem_Sq(
        SqList *L, 
        Elemtype e, 
        int (*compare)(Elemtype *a, Elemtype* b))
{
    Elemtype* p;
    for (p=L->elem; p!=(L->elem+L->length); ++p)
    {
        if (compare(&e, p) == 1)
            return p-L->elem + 1;
    }
    return 0;
}

Status PriorElem_Sq(
        SqList *L,
        Elemtype* cur_e,
        Elemtype** pre_e)
{
    if (cur_e == L->elem)
        return OVERFLOW;
    *pre_e = cur_e-1;
    return OK;
}

Status NextElem_Sq(
        SqList *L,
        Elemtype* cur_e,
        Elemtype** next_e)
{
    if (cur_e == L->elem+L->length-1)
        return OVERFLOW;
    *next_e = cur_e+1;
    return OK;
}

Status __ExpandStorage_Sq(SqList *L)
{
    L->listsize = L->listsize + sizeof(Elemtype)*LISTINCREMENT;
    L->elem = (Elemtype*)realloc(L->elem, L->listsize);
    if (NULL == L->elem)
        return OVERFLOW;
    return OK;
}

Status ListInsert_Sq(SqList *L, size_t i, Elemtype e)
{
    size_t j;
    i--;
    if (L->length*sizeof(Elemtype) == L->listsize)
    {
        if (OVERFLOW == __ExpandStorage_Sq(L))
            return OVERFLOW;
    }
    for (j=L->length; j>i; --j)
    {
        *(L->elem + j) = *(L->elem + j-1);
    }
    *(L->elem + i) = e;
    L->length = L->length+1;
    return OK;
}
    
void ListDelete_Sq(SqList *L, size_t i, Elemtype* e)
{
    size_t j;
    i--;
    *e = *(L->elem + i);
    L->length = L->length-1;
    for (j=i; j<L->length; ++j)
    {
        *(L->elem + j) = *(L->elem + j+1);
    }
    return;
}

Status ListTraverse(SqList *L, int (*visit)(Elemtype *e))
{
    size_t i;
    for (i=0; i<L->length; ++i)
    {
        if (OK != visit(L->elem + i))
            return FAILED;
    }
    return OK;
}

