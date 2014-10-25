// List_L.h
// Copyleft @ weiyulan

#ifndef __LIST_L_H__
#define __LIST_L_H__
#include <stdlib.h>
#include "List.h"

struct LNode
{
    Elemtype data;
    struct LNode *next;
};

struct LList
{
    struct LNode *head;
    size_t length;
};

enum Status InitList_L(struct LList *L);

void DestroyList_L(struct LList *L);

void ClearList_L(struct LList *L);

int ListEmpty_L(struct LList *L);

size_t ListLength_L(struct LList *L);

enum Status GetElem_L(struct LList* L, size_t i, Elemtype* e);

size_t LocateElem_L(
        struct LList* L, 
        struct LNode e, 
        int (*compare)(struct LNode* a, struct LNode* b));

enum Status PriorElem_L(
        struct LList* L,
        struct LNode* cur_e,
        struct LNode** pre_e);

enum Status NextElem_L(
        struct LList* L,
        struct LNode* cur_e,
        struct LNode** next_e);

enum Status ListInsert_L(struct LList* L, size_t i, struct LNode e);

void ListDelete_L(struct LList *L, size_t i, struct LNode* e);

enum Status ListTraverse_L(struct LList *L, int (*visit)(struct LNode *e));

void Reverse_L(struct LList* L);

#endif // __LIST_L_H__
