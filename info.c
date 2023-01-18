#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "info.h"
int Info(Account *LoggedInAcnt)
{
    //the informations will be printed one by one here
    printf("\noooooooooooooooooooooo\n");
    Post *current=LoggedInAcnt->headPost;
    printf("Your Username is: %s\n", LoggedInAcnt->UserName);
    printf("Your password is: %s\n", LoggedInAcnt->pass);
    printf("oooooooooooooooooooooo\n\n");
    while(current!=NULL)
    {
        printf("Post ID: %d\n", current->postID);
        printf("Post text: %s", current->text);
        printf("Likes: %d\n", current->like);
        printf("--------------------\n\n");
        current=current->next;
    }
    return 0;
}