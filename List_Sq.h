#ifndef __LIST_H__
#define __LIST_H__
#include <stdlib.h>
typedef int Elemtype;

struct SqList
{
    Elemtype *elem;
    size_t length;
    size_t listsize;
};

enum Status {OK, OVERFLOW, FAILED};

Status InitList_Sq(SqList *L);

void DestroyList_Sq(SqList *L);

void ClearList_Sq(SqList *L);

int ListEmpty_Sq(SqList *L);

size_t ListLength_Sq(SqList *L);

Status GetElem_Sq(SqList *L, size_t i, Elemtype* e);

size_t LocateElem_Sq(
        SqList *L, 
        Elemtype e, 
        int (*compare)(Elemtype *a, Elemtype* b));

Status PriorElem_Sq(
        SqList *L,
        Elemtype* cur_e,
        Elemtype** pre_e);

Status NextElem_Sq(
        SqList *L,
        Elemtype* cur_e,
        Elemtype** next_e);

Status __ExpandStorage_Sq(SqList *L);

Status ListInsert_Sq(SqList *L, size_t i, Elemtype e);

void ListDelete_Sq(SqList *L, size_t i, Elemtype* e);

Status ListTraverse(SqList *L, int (*visit)(Elemtype *e));

#endif // __LIST_H__
