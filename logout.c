#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "logout.h"
void Logout(Account **LoggedInAcnt)
{   
    *LoggedInAcnt=NULL;
    printf("You have Logged Out successfully.\n");
}