#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "find.h"
#define START_USER 10

int Find(Account *headAcnt, char *TypedChar)
{
    char *UserName;
    int counter=0;
    int testAcnt=0;
    Account *curAcnt=headAcnt;
    Post *curPost;
    while(TypedChar[counter+START_USER]!='\0')
    {
        counter++;
    }
    UserName=(char*)malloc(counter*sizeof(char));
    for(int i=0; i<counter; i++) //we seperate the username entered by user here
    {
        UserName[i]=TypedChar[i+START_USER];
    }
    UserName[counter-1]='\0';
    while(curAcnt!=NULL) //weather th eusername exists will be checked here
    {
        if(strcmp(curAcnt->UserName, UserName)==0)
        {
            testAcnt=1;
            break;
        }
        else
        {
            curAcnt=curAcnt->next;
        }
    }
    if(testAcnt==0)
    {
        printf("The Account doesn't exist.\n"); //an error will be given if the account is not valid
        return 0;
    }
    curPost=curAcnt->headPost;
    printf("\noooooooooooooooooooooo\n"); //the information will be printed one by one here
    if(curPost==NULL)
    {
        printf("Username: %s\n", UserName);
        printf("The User hasn't posted anything yet.\n");
        return 0;
    }
    while(curPost!=NULL)
    {
        printf("Username: %s\n", UserName);
        printf("Post ID: %d\n", curPost->postID);
        printf("Post's Text: %s", curPost->text);
        printf("Likes: %d\n", curPost->like);
        printf("-----------------------\n\n");
        curPost=curPost->next;
    }
    free(UserName);
    return 0;
}