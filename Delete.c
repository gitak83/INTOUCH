#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "struct.h"
#include "Delete.h"
#define ONE 1
int Delete(Post **currentPost, Post **prevPost, Post **headPost, char *TypedChar)
{
    printf("");
    int PostNumCounter = 7;
    int getPostNum = 0;
    int PostNumber = 0;
    int checkHead=0;
    char *PostNum;
    while (TypedChar[PostNumCounter] != '\0') // the post ID will be seperated here
    {
        if (PostNumCounter == 7)
        {
            PostNum = (char *)malloc(ONE * sizeof(char));
            PostNum[getPostNum] = TypedChar[PostNumCounter];
            PostNumCounter++;
            getPostNum++;
        }
        else
        {
            PostNum = (char *)realloc(PostNum, (getPostNum + 1) * sizeof(char));
            PostNum[getPostNum] = TypedChar[PostNumCounter];
            PostNumCounter++;
            getPostNum++;
        }
    }
    PostNum[getPostNum] = '\0';
    for (int i = 0; i < getPostNum - 1; i++) // the post ID entered by the user will be casted to int here
    {
        PostNumber = PostNumber + ((int)PostNum[i] - 48) * pow(10, (getPostNum - i - 2));
    }
    free(PostNum);
    if (getPostNum == 4)
    {
        PostNumber++;
    }
    *currentPost = *headPost;
    *prevPost = *headPost;
    while ((*currentPost) != NULL) // we will check if the post exists
    {
        if ((*currentPost)->postID == PostNumber) // when we find the post, it will be deleted from the list
        {
            if (checkHead==0)
            {
                (*headPost) = (*currentPost)->next;
                free(*currentPost);
            }
            else
            {
                (*prevPost)->next = (*currentPost)->next;
                free(*currentPost); // we free the post here
            }

            printf("You have deleted the post successfully.\n");
            return 0;
        }
        else
        {
            *prevPost = *currentPost;
            (*currentPost) = (*currentPost)->next;
        }
        checkHead=1;
    }
    printf("The post doesn't exist.\n"); // an error will be given if the post doesn't exist
    return 1;
}