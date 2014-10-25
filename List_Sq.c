// List_Sq.c
// Copyleft @ weiyulan

#include "List_Sq.h"
#include <assert.h>

enum Status InitList_Sq(struct SqList *L)
{
    L->elem = (Elemtype*)malloc(sizeof(Elemtype)*LIST_INIT_SIZE);
    if (NULL == L->elem)
        return OVERFLOW;
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}

void DestroyList_Sq(struct SqList *L)
{
    free(L->elem);
}

void ClearList_Sq(struct SqList *L)
{
    DestroyList_Sq(L);
    InitList_Sq(L);
}

int ListEmpty_Sq(struct SqList *L)
{
    return L->length == 0;
}

size_t ListLength_Sq(struct SqList *L)
{
    return L->length;
}

enum Status GetElem_Sq(struct SqList *L, size_t i, Elemtype* e)
{
    i--;
    assert(i < L->length);
    *e = *(L->elem + i);
    return OK;
}

size_t LocateElem_Sq(
        struct SqList *L, 
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

enum Status PriorElem_Sq(
        struct SqList *L,
        Elemtype* cur_e,
        Elemtype** pre_e)
{
    if (cur_e == L->elem)
        return OVERFLOW;
    *pre_e = cur_e-1;
    return OK;
}

enum Status NextElem_Sq(
        struct SqList *L,
        Elemtype* cur_e,
        Elemtype** next_e)
{
    if (cur_e == L->elem+L->length-1)
        return OVERFLOW;
    *next_e = cur_e+1;
    return OK;
}

enum Status __ExpandStorage_Sq(struct SqList *L)
{
    L->listsize = L->listsize + sizeof(Elemtype)*LISTINCREMENT;
    L->elem = (Elemtype*)realloc(L->elem, L->listsize);
    if (NULL == L->elem)
        return OVERFLOW;
    return OK;
}

enum Status ListInsert_Sq(struct SqList *L, size_t i, Elemtype e)
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
    
void ListDelete_Sq(struct SqList *L, size_t i, Elemtype* e)
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

enum Status ListTraverse_Sq(struct SqList *L, int (*visit)(Elemtype *e))
{
    size_t i;
    for (i=0; i<L->length; ++i)
    {
        if (OK != visit(L->elem + i))
            return FAILED;
    }
    return OK;
}

void __swap(Elemtype* a, Elemtype* b)
{
    Elemtype tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void Reverse_Sq(struct SqList* L)
{
    size_t i;
    for (i=0; i<L->length/2; ++i)
    {
        __swap(L->elem+i, L->elem+L->length-1-i);
    }
}

