#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "login.h"
#define START_LOGIN 6
#define ONE 1
#define TRUE 1
int Login(char *TypedChar, Account *headAcnt, Account **LoggedInAcnt)
{
    Account *currentAcnt = headAcnt;
    int TestAccount = 0;
    int TestPass = 0;
    int UserCounter = 0;
    int PassCounter = 0;
    char *UserName;
    char *pass;
    if(*LoggedInAcnt!=NULL) //if the user is still Logged in in another account an error will be given
    {
        printf("You are Logged In in another account. first Log Out from that.\n");
        return 0;
    }
    UserName = (char *)malloc(ONE * sizeof(char));
    pass = (char *)malloc(ONE * sizeof(char));
    while (TRUE) //the username will be seperated here
    {
        if (UserCounter == 0)
        {
            UserName[UserCounter] = TypedChar[UserCounter + START_LOGIN];
            UserCounter++;
        }
        else
        {
            UserName = (char *)realloc(UserName, (UserCounter + 1) * sizeof(char));
            if (TypedChar[UserCounter + START_LOGIN] != ' ')
            {
                UserName[UserCounter] = TypedChar[UserCounter + START_LOGIN];
                UserCounter++;
            }
            else
            {
                UserName[UserCounter] = '\0';
                UserCounter++;
                break;
            }
        }
    }
    while (currentAcnt != NULL) //here we will check if the username exist or not
    {
        if (strcmp(currentAcnt->UserName, UserName) == 0)
        {
            TestAccount = 1;
            break;
        }
        else
        {
            currentAcnt = currentAcnt->next;
        }
    }
    if (TestAccount == 0)
    {
        printf("Coudln't find the Account. Try again.\n"); //if the username wasn't founded an error will be given to the user
        return 0;
    }
    while (TRUE) //the password will be seperated here
    {
        if (PassCounter == 0)
        {
            pass[PassCounter] = TypedChar[PassCounter + UserCounter + START_LOGIN];
            PassCounter++;
        }
        else
        {
            pass = (char *)realloc(pass, (PassCounter + 1) * sizeof(char));
            if (TypedChar[PassCounter + UserCounter + START_LOGIN] != '\n')
            {
                pass[PassCounter] = TypedChar[PassCounter + UserCounter + START_LOGIN];
                PassCounter++;
            }
            else
            {
                pass[PassCounter] = '\0';
                break;
            }
        }
    }
    if (strcmp(currentAcnt->pass, pass) != 0) //weather the password is right or wrong will be checked here
    {
        printf("The Password doesn't mach. Try again.\n");
        return 0;
    }
    *LoggedInAcnt = currentAcnt;
    printf("You are logged in Successfully.\n");
    return 1;
}