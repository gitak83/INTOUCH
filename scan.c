#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scan.h"
#include "signup.h"
#include "login.h"
#include "post.h"
#include "Delete.h"
#include "find.h"
#include "info.h"
#include "like.h"
#include "logout.h"
#define TRUE 1
#define FALSE 0
#define ONE 1
#define ZERO 0
#define TWO 2
#define THREE 3
int scan(int *ptrAct)
{
    char signup[] = "signup";
    char login[] = "login";
    char post[] = "post";
    char like[] = "like";
    char logout[] = "logout";
    char delete[] = "delete";
    char info[] = "info";
    char find[] = "find_user";
    Account *headAcnt;
    Account *previousAcnt;
    Account *currentAcnt;
    Account *LoggedInAcnt;
    Post *prevPost;
    Post *currentPost;
    Post *headPost;
    Post *curPost_JustForLike;
    Post *curPost_JustForDelete;
    Post *prevPost_JustForDelete;
    FILE *accounts;
    FILE *posts;
    if (*ptrAct == 0)
    {
        headAcnt = NULL;
        previousAcnt = NULL;
        currentAcnt = NULL;
        LoggedInAcnt = NULL;
        prevPost = NULL;
        currentPost = NULL;
        headPost = NULL;
        curPost_JustForLike= NULL;
        curPost_JustForDelete=NULL;
    }
    int test = 0;
    int counter = 0;
    char *TypedChar;
    int index;
    char *CheckOrder;
    char *PostText;
    int numOfSp = 0;
    int placeOfSp = 0;
    int ScanTest = 0;
    int i = 0;
    int del=0;
    while (TRUE) //in this while loop we get the characters the user has entered one by one
    {
        if (counter == 0)
        {
            TypedChar = (char *)malloc(ONE * sizeof(char));
            if (TypedChar == NULL)
            {
                printf("There was aproblem. Try again.\n");
                return 0;
            }
            TypedChar[counter] = getchar();
            if (TypedChar[counter] == '\n') //when the user press the enter key, it means the order is done, so we are done getting what the user has entered
                return ZERO;
            if (TypedChar[counter] == 'X') //if the user press X anytime, the program will be closed. so we return 1 here and the amount that scan function returns, will be checked in the maiin function and if it is one the will be closed.
            {
                accounts=fopen("accounts.txt", "w"); //now that the user wants to close the program, we should save the informations in two files with codes below.
                posts=fopen("posts.txt", "w");
                currentAcnt=headAcnt;
                while(currentAcnt!=NULL)
                {
                    fwrite(currentAcnt->UserName, sizeof(char), (strlen(currentAcnt->UserName)), accounts);
                    fprintf(accounts, " ");
                    fwrite(currentAcnt->pass, sizeof(char), strlen(currentAcnt->pass), accounts);
                    fprintf(accounts, " %d\n", currentAcnt->PostNum);
                    currentPost=currentAcnt->headPost;
                    while(currentPost!=NULL)
                    {
                        fwrite(currentPost->text, sizeof(char), strlen(currentPost->text), posts);
                        fwrite(currentPost->UserName, sizeof(char), (strlen(currentPost->UserName)), posts);
                        fprintf(posts, " %d\n-\n", currentPost->like);
                        currentPost=currentPost->next;
                    }
                    currentAcnt=currentAcnt->next;
                }
                fclose(posts);
                fclose(accounts);
                return ONE;
            }
                
            counter++;
        }
        else
        {
            //after the first malloc we will realloc everytime until the user press the enter key.
            TypedChar=(char*)realloc(TypedChar,(counter+1) * sizeof(char));
            if (TypedChar == NULL)
            {
                printf("There was aproblem. Try again.\n");
                return 0;
            }
            TypedChar[counter] = getchar();
            if (TypedChar[counter] == ' ') //the number and the place of the space character should be counted, to check weather th euser had follow the orders. and give an error if needed
            {
                numOfSp++;
                if (placeOfSp == 0)
                    placeOfSp = counter;
            }
            if (TypedChar[counter] == '\n')
            {
                TypedChar=(char*)realloc(TypedChar, (counter+2)*sizeof(char));
                if (placeOfSp == 0)
                    placeOfSp = counter;
                break;
            }
            counter++;
        }
    }
    TypedChar[counter+1]='\0';
    char input[counter]; 
    strcpy(input, TypedChar);
    free(TypedChar);
    while(input[counter]!='\n')
    {
        if(input[counter]==' ')
        {
            numOfSp++;
            if(placeOfSp==0)
            {
                placeOfSp=counter;
            }
        }
        counter++;
    }
    if(placeOfSp==0)
    {
        placeOfSp=counter;
    }
    CheckOrder = (char *)malloc((placeOfSp) * sizeof(char)); //this to check what the user wants to based on the first word entered.
    if (CheckOrder == NULL)
    {
        printf("There was aproblem. Try again.\n");
        return 0;
    }
    for (i = 0; i < placeOfSp; i++)
        CheckOrder[i] = input[i];
    CheckOrder[placeOfSp] = '\0';
    if (strcmp(CheckOrder, signup) == 0)
        ScanTest = 1;
    if (strcmp(CheckOrder, login) == 0)
        ScanTest = 2;
    if (strcmp(CheckOrder, post) == 0)
        ScanTest = 3;
    if (strcmp(CheckOrder, like) == 0)
        ScanTest = 4;
    if (strcmp(CheckOrder, logout) == 0)
        ScanTest = 5;
    if (strcmp(CheckOrder, delete) == 0)
        ScanTest = 6;
    if (strcmp(CheckOrder, info) == 0)
        ScanTest = 7;
    if (strcmp(CheckOrder, find) == 0)
        ScanTest = 8;
    if (ScanTest == 0)
    {
        //if the user hadn't entered the orders right, we will give an error 
        printf("Please follow the orders of INTOUCH\n");
        return ZERO;
    }
    free(CheckOrder);
    if (*ptrAct == 0)
        if (ScanTest != 1)
        {
            printf("You should Sign Up first\n");
            return ZERO;
        }
    switch (ScanTest) //in this part we use different functions for different orders and we will check weather the user has used the orders right
    {
    case 1:
    {
        if (numOfSp != 2)
        {
            printf("Please follow the orders of INTOUCH\n");
            return ZERO;
        }
        if (Signup(&previousAcnt, &currentAcnt, &headAcnt, input) == 0)
        {
            printf("That username is taken. Try another.\n");
            return ZERO;
        }
        else
        {
            break;
        }
    }
    case 2:
    {
        if (numOfSp != 2)
        {
            printf("Please follow the orders of INTOUCH\n");
            return ZERO;
        }
        int TestLogin = Login(input, headAcnt, &LoggedInAcnt);
        if (TestLogin == 0)
        {
            return ZERO;
        }
        currentPost=LoggedInAcnt->headPost;
        while(currentPost!=NULL)
        {
            prevPost=currentPost;
            currentPost=currentPost->next;
        }
        break;
    }
    case 3:
    {
        if (counter < 5)
        {
            printf("Please follow the orders of INTOUCH\n");
            return ZERO;
        }
        if (LoggedInAcnt == NULL)
        {
            printf("You are not Logged in.\n");
            return ZERO;
        }
        printf("");
        Posting(LoggedInAcnt->UserName, input, &currentPost, &prevPost, &headPost, counter, &LoggedInAcnt);
        printf("The Text is posted successfully.\n");
        break;
    }
    case 4:
    {
        if (numOfSp != 2)
        {
            printf("Please follow the orders of INTOUCH\n");
            return ZERO;
        }
        if (LoggedInAcnt == NULL)
        {
            printf("You are not Logged in.\n");
            return ZERO;
        }
        Like(&headAcnt, LoggedInAcnt->AcntID, &curPost_JustForLike, input);
        
        break;
    }
    case 5:
    {
        if (numOfSp != 0)
        {
            printf("Please follow the orders of INTOUCH\n");
            return ZERO;
        }
        if (LoggedInAcnt == NULL)
        {
            printf("You are not Logged in.\n");
            return ZERO;
        }
        Logout(&LoggedInAcnt);
        break;
    }
    case 6:
    {
        if (numOfSp != 1)
        {
            printf("Please follow the orders of INTOUCH\n");
            return ZERO;
        }
        if (LoggedInAcnt == NULL)
        {
            printf("You are not Logged in.\n");
            return ZERO;
        }
        printf("");
        del=Delete(&curPost_JustForDelete, &prevPost_JustForDelete, &(LoggedInAcnt->headPost), input);
        if(del==0)
        {
            LoggedInAcnt->PostNum--;
        }
        break;
    }
    case 7:
    {
        if (numOfSp != 0)
        {
            printf("Please follow the orders of INTOUCH\n");
            return ZERO;
        }
        if (LoggedInAcnt == NULL)
        {
            printf("You are not Logged in.\n");
            return ZERO;
        }
        Info(LoggedInAcnt);
        break;
    }
    case 8:
    {
        if (numOfSp != 1)
        {
            printf("Please follow the orders of INTOUCH\n");
            return ZERO;
        }
        if (LoggedInAcnt == NULL)
        {
            printf("You are not Logged in.\n");
            return ZERO;
        }
        Find(headAcnt, input);
        break;
    }
    }
    *ptrAct = *ptrAct + 1;
    return ZERO;
}