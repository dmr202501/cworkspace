#include<stdio.h>
#include <string.h>
#define N 10
int main(){
    char str[N];
    char username[N];
    printf("please input an operation\n");
    gets(str);
    while(strcmp(str,"Quit")!=0){
       if(strcmp(str,"Login")==0){
           printf("Please input your username\n");
           gets(username);
           if(strcmp(username,"Admin")==0)             printf("Admin Login.\n");
           else if(username[0]>='A'&&username[0]<='Z')      printf("User Login.\n");
           else                                   printf("Username is incorrect.\n"); 
           printf("please input an operation\n");
           gets(str);          
       }
       else if(strcmp(str,"Exit")==0){
           printf("please input an operation\n");
           gets(str);
       }
       else {
           printf("Error operation\n");
           printf("please input an operation\n");
           gets(str);
       }
    }
    return 0;
}