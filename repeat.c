#include "headers.h"
void repeat()
{
    int num = atoi(args[1]);
    int j=0;
    for(int i=0 ; i<arg_num;i++)
    {
        if(i>=2)
        {
            args[j++] = args[i];
        }
    }
    arg_num = arg_num-2;
    while(num--)
    {
        call();
    }
}
