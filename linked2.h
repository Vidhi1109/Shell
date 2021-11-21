#ifndef LINKED2_H
#define LINKED2_H

typedef char* ElementType;

typedef struct Node ListNode;
typedef struct Node* PtrToNode;

typedef PtrToNode List;
typedef PtrToNode Position;
PtrToNode rear;
struct Node {
    ElementType Element;
    int jobnumber;
    Position Next;
};
PtrToNode MakeNode(ElementType X);
List CreateEmptyList();
void InsertAtFront(List *LP, ElementType X);
void DeleteNode(PtrToNode P);
void PrintList(List L);
void EmptyList(List *LP);
void DeleteList(List *LP);
void storeList();
#endif