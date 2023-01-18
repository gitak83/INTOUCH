#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "post.h"
#define ONE 1
#define TEXT_START 5
#define TRUE 1
int Posting(char *UserName, char *TypedChar, Post **currentPost, Post **prevPost, Post **headPost, int counter, Account **LoggedInAcnt)
{
    Post *cur;
    cur = (Post *)malloc(ONE * sizeof(Post));
    int i;
    char *PostText;
    PostText = (char *)malloc((counter+1) * sizeof(char)); //the text of the post will be seperated here
    for (i = 0; i < counter; i++)
    {
        PostText[i] = TypedChar[i + 5];
    }
    PostText[i] = '\0';
    // with codes below the information will be added to the new post
    cur->like = 0;
    cur->next = NULL;
    cur->postID = (*LoggedInAcnt)->NumberForID + 1;
    cur->text = PostText;
    cur->UserName = UserName;
    cur->LikedUser = 1;
    *currentPost = cur;
    switch ((*LoggedInAcnt)->PostNum+1) //in this part we add the post the list of the posts
    {
    case 1:
    {
        *headPost = *currentPost;
        (*LoggedInAcnt)->headPost=*headPost;
        *prevPost = *currentPost;
        break;
    }
    case 2:
    {
        (*headPost)->next = *currentPost;
        (*prevPost)->next = *currentPost;
        break;
    }
    default:
    {
        (*prevPost)->next = *currentPost;
        break;
    }
    }
    (*LoggedInAcnt)->PostNum++;
    (*LoggedInAcnt)->NumberForID++;
    *prevPost = *currentPost;
    return 0;
}