#ifndef POST
#define POST

typedef struct post Post;
typedef struct account Account;

struct post 
{
    char *UserName;
    int postID;
    int like;
    int LikedUser; //this is a number which when every user likes a post the accout ID of the user will be multiplead by this number so we can check in like function that weather the user has liked the post before or not
    char *text;
    Post *next;
};

struct account
{
    int NumberForID;
    char *UserName;
    char *pass;
    int PostNum;
    int AcntID; //it is a prime number
    struct post *headPost;
    struct account *next;
};
#endif
