#include "headers.h"
#include "linked.h"
PtrToNode MakeNode(ElementType X)
{
    PtrToNode P = (PtrToNode)malloc(sizeof(ListNode));
    if (P != NULL)
    {
        P->Element = (char *)(malloc(strlen(X) + 1));
        if (P->Element != NULL)
        {
            strcpy(P->Element, X);
            P->Next = NULL;
        }
    }
    return P;
}
List CreateEmptyList()
{
    PtrToNode P = MakeNode("header");
    rear = MakeNode("back");
    rear = P;
    return P;
}
void InsertAtFront(List *LP, ElementType X)
{
    PtrToNode PNew = MakeNode(X);
    List L = *LP;
    if (hist_cnt >= 20)
    {
        hist_cnt--;
    }
    if (strcmp(rear->Element, X) != 0)
    {
        rear->Next = PNew;
        rear = PNew;
        //PNew->Next = L->Next;
        //L->Next = PNew;
        if (hist_cnt >= 20)
        {
            PtrToNode P = (*LP)->Next;
            (*LP)->Next = ((*LP)->Next)->Next;
            DeleteNode(P);
            PrintList(L);
        }
    }
}
void DeleteNode(PtrToNode P)
{
    if (!P)
        free(P);
}
void PrintList(List L)
{
    PtrToNode P = L->Next; // Skip header

    printf("\n");
    while (P != NULL)
    {
        printf("%s --> ", P->Element);
        P = P->Next;
    }
    printf("[NULL]");
    printf("\n\n");
}
void EmptyList(List *LP)
{
    List L = *LP;
    L = L->Next;
    PtrToNode Curr;
    while (L != NULL)
    {
        Curr = L;
        L = L->Next;
        DeleteNode(Curr);
    }
    (*LP)->Next = NULL;
}
void DeleteList(List *LP)
{
    EmptyList(LP);
    free(*LP);
}

void storeList()
{
    FILE *file = fopen("./history.txt", "w");
    if (file == NULL)
    {
        fprintf(stderr, "Couldn't Open File'\n");
        return;
    }
    else
    {
        PtrToNode temp = L->Next;
        while (temp != NULL)
        {
            fwrite(temp->Element, strlen(temp->Element), 1, file);
            temp = temp->Next;
            if (fwrite <= 0)
            {
                printf("Error encountered in storing history\n");
                return;
            }
            fwrite("\n", 1, 1, file);
        }
    }
    fclose(file);
}

struct Node2 * MakeNode2(ElementType X , int n, int job_pid)
{
    struct Node2* P = (struct Node2 *)malloc(sizeof(struct Node2));
    if (P != NULL)
    {
        P->Element = (char *)(malloc(strlen(X) + 1));
        if (P->Element != NULL)
        {
            strcpy(P->Element, X);
            P->Next = NULL;
        }
        P->jobnumber = n;
        P->pid = job_pid;
    }
    return P;
}

void Insert(struct Node2* List , int job_num , int pid)
{
    int i=0 , size=0;
    while(args[i]!=NULL)
    {
        size += strlen(args[i]);
        size++;
        i++;
    }
    size++;
    char * X = (char*)(malloc(sizeof(char)*size));
    i=0;
    while(args[i]!=NULL)
    {
        strcat(X , args[i]);
        i++;
    }
    struct Node2* PNew = MakeNode2(X,job_num, pid);
    struct Node2* temp = List;
    while(temp->Next!=NULL && strcmp(temp->Next->Element , X)<0)
    {
        temp = temp->Next;
    }
    temp ->Next = PNew;
    free(temp);
}

struct Node2* CreateEmptyList2()
{
    struct Node2* P = MakeNode2("header" , 0 , 0);
    P->Next=NULL;
    return P;
}
