#ifndef LINKED_H
#define LINKED_H

typedef char* ElementType;

typedef struct Node ListNode;
typedef struct Node* PtrToNode;

typedef PtrToNode List;
typedef PtrToNode Position;
PtrToNode rear;
struct Node {
    ElementType Element;
    Position Next;
};
struct Node2 {
    ElementType Element;
    int jobnumber;
    int pid;
    struct Node2* Next;
};
PtrToNode MakeNode(ElementType X);
List CreateEmptyList();
void InsertAtFront(List *LP, ElementType X);
void DeleteNode(PtrToNode P);
void PrintList(List L);
void EmptyList(List *LP);
void DeleteList(List *LP);
void storeList();
struct Node2 * MakeNode2(ElementType X , int n , int pid);
void Insert(struct Node2* List , int job_num , int pid);
struct Node2* CreateEmptyList2();
#endif