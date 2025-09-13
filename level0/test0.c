#include <stdio.h>
#include <string.h>
#define N 10
int main(){
    char str[N];
    printf("please input a word:\n");
        gets(str);
    if(strcmp(str,"Dian")==0)
        printf("2002");
    else if(strcmp(str,"Quit")==0)
        return 0;
    else
       printf("Error");
return 0;
}