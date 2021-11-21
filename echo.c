#include "headers.h"

void echo()
{
    for(int i=1 ; i<arg_num;i++)
    {
        printf("%s ",args[i]);
    }
    printf("\n");
}