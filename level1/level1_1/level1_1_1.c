#include<stdio.h>
#include <string.h>
#define N 10
int main(){
    char str[N];
    while(1){
    	printf("Please enter a command.\n");
    	gets(str);
    	//puts(str);
    	if(strcmp(str,"Quit")==0) return 0;
    	else if(strcmp(str,"Exit")==0) continue;
    	else if(strcmp(str,"Login")==0){
           printf("Please enter your username.\n");
           gets(str);
           //puts(str);
           if(strlen(str)==1&&str[0]>='A'&&str[0]<='Z')  
		   		printf("User Login.\n");
		   else if(strcmp(str,"Admin")==0)        
		   		printf("Admin Login.\n");
		   else                                                    
		   		printf("Username is incorrect.\n");           
    	}
    	else
        	printf("Command is incorrect.\n");        
	}	
    return 0;
}
