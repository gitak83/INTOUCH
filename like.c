#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "struct.h"
#include "like.h"
#define ONE 1
int Like(Account **headAcnt, int LoggedInAcnt_ID, Post **curPost, char *TypedChar)
{
    printf("");
    Account *currentAcnt = *headAcnt;
    Post *currentPost = NULL;
    char *CheckLike;
    char *LikesPostNum;
    char *LikedUserName;
    int counter = 0;
    int NumCounter = 0;
    int CheckUser = 0;
    int PostNumber = 0;
    int CheckPost = 0;
    int testLikedUser = 0;
    int i=0;
    LikesPostNum = (char *)malloc(ONE * sizeof(char));
    LikedUserName = (char *)malloc(ONE * sizeof(char));
    while (TypedChar[counter + 5] != ' ') //the username of the post the user wants to like will be seperated here
    {
        LikedUserName[counter] = TypedChar[counter + 5];
        counter++;
        LikedUserName = (char *)realloc(LikedUserName, (counter + 1) * sizeof(char));
    }
    LikedUserName[counter] = '\0';
    while (currentAcnt != NULL) //we will check if the username exists
    {
        if (strcmp(currentAcnt->UserName, LikedUserName) == 0)
        {
            CheckUser = 1;
            currentPost = currentAcnt->headPost;
            break;
        }
        else
        {
            currentAcnt = currentAcnt->next;
        }
    }
    free(LikedUserName);
    if (CheckUser == 0) //if the username is wrong, an error will be given
    {
        printf("The Username is wrong.\n");
        return 0;
    }

    while (TypedChar[NumCounter + counter + 6] != '\n') //we will seperate the postID here
    {
        LikesPostNum[NumCounter] = TypedChar[NumCounter + counter + 6];
        NumCounter++;
        LikesPostNum = (char *)realloc(LikesPostNum, (NumCounter + 1) * sizeof(char));
    }
    LikesPostNum[NumCounter] = '\0';
    for (int i = 0; i < NumCounter; i++) //we will cast the post ID to int 
    {
        PostNumber = PostNumber + ((int)LikesPostNum[i] - 48) * pow(10, (NumCounter - i - 1));
    }
    free(LikesPostNum);
    if (NumCounter == 3)
    {
        PostNumber++;
    }
    while (currentPost != NULL) //weather the post exists or not will be checked here
    {
        if (currentPost->postID == PostNumber)
        {
            CheckPost = 1;
            *curPost = currentPost;
            break;
        }
        else
        {
            currentPost = currentPost->next;
        }
    }
    if (CheckPost == 0) //if the post doesn't exist an error will be given
    {
        printf("The Post doesn't exist.\n");
        return 0;
    }
    if(((currentPost->LikedUser)%(LoggedInAcnt_ID))==0) //we will check if the user has liked the post before
    {
        printf("You have liked the Post before.\n");
        return 0;
    }
    else //if the user hadn't liked the post before, the number of likes will change and the account ID will be multiplied by the likedUser valuable so we can check it in the future
    {
        (*curPost)->LikedUser=(currentPost->LikedUser)*LoggedInAcnt_ID;
        (*curPost)->like=(*curPost)->like+1;
    }
    printf("You have liked the post successfully.\n");
    return 0;
}