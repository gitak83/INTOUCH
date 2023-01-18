#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "scan.h"
#define TRUE 1
#define ONE 1
#define ZERO 0
int main()
{
    int successAct = 0;
    int *ptrAct;
    ptrAct = &successAct;
    int test;
    printf("Welcome to INTOUCH!!!\n");  //in this part the orders of using the program is specified for the user
    printf("you can quit the program anytime by pressing 'X'\n\n");
    printf("There are some orders to use INTOUCH\n");
    printf("SignUp: Enter your Username and password in front of the word 'signup' & seperate theme with a space\n");
    printf("LogIn: Enter your Username and password in front of the word 'login' & seperate theme with a space\n");
    printf("Post: Enter the text you want to post , in front of the word 'post', & seperate the text from post with a space\n");
    printf("Like: Enter the Username and the ID of the post you want to like in front of the word 'like' & seperate them with a space\n");
    printf("LogOut: Enter 'logout'\n");
    printf("Delete: Enter the postID in front of the word 'delete' & seperat them with a space\n");
    printf("Info: Enter the word 'info'\n");
    printf("Find a User: Enter the Username in front of 'find_user'\n");
    while (TRUE)
    {
        // the whole program is an infinite loop until the user wants to quit it. everything the user enters will be checked with scan function and the program will be countinued based on what has been entered
        test = scan(&successAct);
        switch (test)
        {
        case 0:
        {
            break;
        }
        case 1:
        {
            return 0;
        }
        }
    }
}