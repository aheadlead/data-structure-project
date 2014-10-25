#include "List_L.h"
#include <assert.h>

enum Status InitList_L(struct LList *L)
{
    L->length = 0;
    L->head = NULL;
    return OK;
}

void DestroyList_L(struct LList *L)
{
    struct LNode *p=L->head, *t;
    while (NULL != p)
    {
        t = p->next;
        free(p);
        p = t;
    }
}

void ClearList_L(struct LList *L)
{
    DestroyList_L(L);
    InitList_L(L);
}

int ListEmpty_L(struct LList *L)
{
    return L->length == 0;
}

size_t ListLength_L(struct LList *L)
{
    return L->length;
}

enum Status GetElem_L(struct LList* L, size_t i, Elemtype* e)
{
    i--;
    struct LNode *p=L->head->next;
    for (; i>0; --i)
    {
        p = p->next;
    }
    *e = p->data;
    return OK;
}

size_t LocateElem_L(
        struct LList* L, 
        struct LNode e, 
        int (*compare)(struct LNode* a, struct LNode* b))
{
    struct LNode* p=L->head->next;
    int counter = 1;
    for (; NULL!=p; p=p->next, counter++)
    {
        if (compare(&e, p))
            return counter;
    }
    return 0;
}

enum Status PriorElem_L(
        struct LList* L,
        struct LNode* cur_e,
        struct LNode** pre_e)
{
    struct LNode* p=L->head;
    if (cur_e == p)
        return OVERFLOW;
    for (; NULL!=p; p=p->next)
    {
        if (p->next == cur_e)
        {
            *pre_e = p;
            return OK;
        }
    }
    return FAILED;
}

enum Status NextElem_L(
        struct LList* L,
        struct LNode* cur_e,
        struct LNode** next_e)
{
    *next_e = cur_e->next;
    return OK;
}

enum Status ListInsert_L(struct LList* L, size_t i, struct LNode e)
{
    struct LNode* p=L->head;
    struct LNode* newplace=(struct LNode*)malloc(sizeof(struct LNode));
    i--;
    for (; i>0; --i)
    {
        p = p->next;
    }
    *newplace = e;
    newplace->next = p->next;
    p->next = newplace; 
    return OK;
}

void ListDelete_L(struct LList *L, size_t i, struct LNode* e)
{
    struct LNode* p=L->head;
    struct LNode* del;
    i--;
    for (; i>0; --i)
    {
        p = p->next;
    }
    del = p->next;
    p = p->next->next;
    *e = *del;
    free(del);
    return;
}

enum Status ListTraverse_L(struct LList *L, int (*visit)(struct LNode *e))
{
    struct LNode* p=L->head;
    for (; NULL!=p; p=p->next)
    {
        if (OK != visit(p))
            return FAILED;
    }
    return OK;
}

void __swap_pointer(struct LNode** a, struct LNode** b)
{
    struct LNode* tmp=*a;
    *a = *b;
    *b = tmp;
}

void Reverse_L(struct LList* L)
{
    struct LNode* next;
    struct LNode* tmp=NULL;
    struct LNode* p=L->head->next;
    for (; ; )
    {
        next = p->next;
        p->next = tmp;
        tmp = p;
        if (NULL != next)
        {
            p = next;
        }
        else
        {
            L->head = p;
            break;
        }
    }
    return;
}
