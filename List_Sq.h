// List_Sq.h
// Copyleft @ weiyulan

#ifndef __LIST_SQ_H__
#define __LIST_SQ_H__
#include <stdlib.h>
#include "List.h"

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

struct SqList
{
    Elemtype *elem;
    size_t length;
    size_t listsize;
};

enum Status InitList_Sq(struct SqList *L);

void DestroyList_Sq(struct SqList *L);

void ClearList_Sq(struct SqList *L);

int ListEmpty_Sq(struct SqList *L);

size_t ListLength_Sq(struct SqList *L);

enum Status GetElem_Sq(struct SqList *L, size_t i, Elemtype* e);

size_t LocateElem_Sq(
        struct SqList *L, 
        Elemtype e, 
        int (*compare)(Elemtype *a, Elemtype* b));

enum Status PriorElem_Sq(
        struct SqList *L,
        Elemtype* cur_e,
        Elemtype** pre_e);

enum Status NextElem_Sq(
        struct SqList *L,
        Elemtype* cur_e,
        Elemtype** next_e);

enum Status ListInsert_Sq(struct SqList *L, size_t i, Elemtype e);

void ListDelete_Sq(struct SqList *L, size_t i, Elemtype* e);

enum Status ListTraverse_Sq(struct SqList *L, int (*visit)(Elemtype *e));

void Reverse_Sq(struct SqList *L);

#endif // __LIST_SQ_H__
