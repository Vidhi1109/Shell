#include "headers.h"
void history()
{
    int num;
    if (args[1] == NULL)
    {
        num = 10;
    }
    else
    {
        num = atoi(args[1]);
    }
    //printf("%d %d",hist_cnt,num);
    PtrToNode temp = L->Next;
    int count = hist_cnt - num + 1, i = 1;
    //printf("%d %d",count , i);
    while (temp != NULL)
    {
        if (i >= count)
        {
            printf("%s\n", temp->Element);
        }
        temp = temp->Next;
        i++;
    }
}