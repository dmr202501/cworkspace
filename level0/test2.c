#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 10  
int check(char*);   
int check(char* str){
	int i=0;
	char c;
	if(strlen(str)==0||strlen(str)>10)  return 0;  
	while((c=str[i])!='\0'){		
		if(!isalpha(c)&&c!='_') return 0;
		i++;		
	}
	return 1;		
}
int main(){
	FILE *fp;
	char line[81],k[N+1],v[N+1];
	int i,j,index,found;	
	fp=fopen("data.txt","r");
	if(fp==NULL){
		printf("data.txt not found.\n");
		return 0;
	}	
	do{
		printf("Enter a string containing only letters and underscores as a key and search for matching value in the file.\n");
    	gets(k);
    	if(strcmp(k,"Quit")==0) {
			fclose(fp);      
	    	return 0;
		} 
		if(check(k)) break;	
		printf("Incorrect input,please re-enter .\n");
	}while(1); 	
	while (fgets(line, sizeof(line), fp)){ 
    	found=1;
    	for(i=0,j=0;found&&k[i]!='\0';i++,j++){
    		if(k[i]!=line[j]) found=0;
		}		
		if(!found) continue;   
		if(line[j]!=':') continue;
		for(i=j+1,index=0; line[i]!='\n' ;i++,index++)		
			v[index]=line[i];			
		v[index]='\0';		
		if(!check(v)) continue;
		printf("Find the value  that matches the key .\n");
		printf("  key : value = %s : %s\n",k,v);
		fclose(fp);
		return 0;
	}
	printf("Error!No value found that matches the key .\n");  
	fclose(fp);      
    return 0;
}

