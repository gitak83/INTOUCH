#include <stdio.h>
#include "prime.h"
int prime(int a)
{
    int i=0;
    for(i=2; i<a; i++)
    {
        if(a%i==0)
        {
            return 1;
        }
    }
    return 0;
}