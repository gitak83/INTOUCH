#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "signup.h"
#include "prime.h"
#define ONE 1
#define ZERO 0
#define TRUE 1
#define START_OF_USER 7

int Signup(Account **previousAcnt, Account **currentAcnt, Account **headAcnt, char *TypedChar)
{
    Account *AcntNode;
    char *GetUserName;
    char *GetPass;
    int PassCheck = 0;
    int counter = 0;
    int NextPrime;
    AcntNode = (Account *)malloc(ONE * sizeof(Account));
    GetUserName = (char *)malloc(ONE * sizeof(char));
    GetPass = (char *)malloc(ONE * sizeof(char));
    while (TRUE) //we seperate the username from the password here. 
    {
        if (counter == 0)
        {
            GetUserName[counter] = TypedChar[counter + START_OF_USER];
            counter++;
        }
        else
        {
            GetUserName = (char *)realloc(GetUserName, (counter + 1) * sizeof(char));
            if (TypedChar[counter + START_OF_USER] != ' ')
            {
                GetUserName[counter] = TypedChar[counter + START_OF_USER];
                counter++;
            }
            else
            {
                GetUserName[counter] = '\0';
                break;
            }
        }
    }
    if (*headAcnt != NULL) //we will check if the username the user wants has being taken befor or not
    {
        Account *previous = NULL;
        Account *current = *headAcnt;
        while (current != NULL)
        {
            if (strcmp(current->UserName, GetUserName) != 0) //now that we are checking every account if we find a match in the usernames, 0 will be returned and an error will be given in scan function
            {
                previous = current;
                current = current->next;
            }
            else
            {
                return ZERO;
            }
        }
    }
    AcntNode->UserName = GetUserName; //if the username is new so it is valid and we will use it as the username of the new Account's username

    counter++;
    while (TRUE) //we will get the password here
    {
        if (PassCheck == 0)
        {
            GetPass[PassCheck] = TypedChar[counter + START_OF_USER + PassCheck];
            PassCheck++;
        }
        else
        {
            GetPass = (char *)realloc(GetPass, (PassCheck + 1) * sizeof(char));
            if (TypedChar[counter + START_OF_USER + PassCheck] != '\n')
            {
                GetPass[PassCheck] = TypedChar[counter + START_OF_USER + PassCheck];
                PassCheck++;
            }
            else
            {
                GetPass[PassCheck] = '\0';
                break;
            }
        }
    } 
    //the informations will be added to the new account based on the code below
    AcntNode->pass = GetPass;
    AcntNode->next = NULL;
    AcntNode->PostNum = 0;
    AcntNode->NumberForID=0;
    AcntNode->headPost = NULL;
    if (*headAcnt == NULL) //the Account ID will be given to the Account here
    {
        AcntNode->AcntID = 2;
    }
    else
    {
        if ((*headAcnt)->next == NULL)
        {
            AcntNode->AcntID = 3;
        }
        else
        {
            NextPrime = (*previousAcnt)->AcntID + 1; //cause the Account ID should be a prime number so we will start from the previous account's account ID and check if the number is prime or not, and use it as the account ID if it is a prime number
            while (prime(NextPrime)==1)
            {
                NextPrime++;
            }
            AcntNode->AcntID=NextPrime;
        }
    }
    *currentAcnt = AcntNode;
    if (*headAcnt == NULL) //if this is the first user we make it the head user
    {
        *headAcnt = *currentAcnt;
        *previousAcnt = *currentAcnt;
    }
    else //if it is not the first user so we will add it to the tail of the linked list of users.
    {
        if ((*headAcnt)->next == NULL)
        {
            (*headAcnt)->next = (*currentAcnt);
            (*previousAcnt)->next = (*currentAcnt);
        }
        else
        {
            (*previousAcnt)->next = (*currentAcnt);
        }
    }
    *previousAcnt = *currentAcnt;
    printf("You have Signed Up successfully.\n");
    return ONE;
}