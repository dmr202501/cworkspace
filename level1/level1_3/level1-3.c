#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#define N 15

char line[81],str[N],id;
char seat[7][5][4][4];
int idx=0;

void Output_command_list();
void init();
int nextword();
void display();
void reservation();
void reserve();
int getweek();
int getfloor();
int getrow();
int getcolumn();
void putweek(int);

int main(){
    init(); 
	Output_command_list();   
    while(1){
    	printf("Please enter a command.\n");		
    	gets(line);    	
		idx=0;
		if(nextword()==0){
			printf("Command is incorrect.\n");
			continue;
		}
    	if(strcmp(str,"Quit")==0) return 0;
    	else if(strcmp(str,"Exit")==0) {
			continue;
			id='\0';
		}
    	else if(strcmp(str,"Login")==0){
           printf("Please enter your username.\n");
           gets(line);
           if(strlen(line)==1&&line[0]>='A'&&line[0]<='Z') {
           		printf("User Login.\n");
				id=line[0];     		
		   } 		   		
		   else if(strcmp(line,"Admin")==0) {
		   		printf("Admin Login.\n");
				id='*';	
		   } 		   
		   else                                                    
		   		printf("Username is incorrect.\n");		 
    	}
    	else if(strcmp(str,"Display")==0) {
			if(id=='\0') {
					printf("You first need to log in.\n");
					printf("Command is incorrect.\n");		   		
		   		} 
			 else display();
		}
		else if(strcmp(str,"Reserve")==0) {
		   	if(id=='\0') {
				printf("You first need to log in.\n");
				printf("Command is incorrect.\n");		   		
		   	} 			
			else reserve();
		} 
		else if(strcmp(str,"Reservation")==0) {
			if(id=='\0') {
				printf("You first need to log in.\n");
				printf("Command is incorrect.\n");		   		
		   	} 
			else reservation();
		}
		else if(strcmp(str,"Clear")==0) {
			if(id!='*') {
				printf("Command can only be executed by management personnel.\n");
				printf("Command is incorrect.\n");		   		
		   	} 
			else init();
		}
		else 
        	printf("Command is incorrect.\n");        
	}	
    return 0;
}

int getweek(){
	int w;
	if(nextword()==0){
		printf("Command is incorrect.\n");
		return -1;	
	}
	if(strcmp(str,"Monday")==0) w=0;
	else if(strcmp(str,"Tuesday")==0) w=1;
	else if(strcmp(str,"Wednesday")==0) w=2;
	else if(strcmp(str,"Thursday")==0) w=3;
	else if(strcmp(str,"Friday")==0) w=4;
	else if(strcmp(str,"Saturday")==0) w=5;
	else if(strcmp(str,"Sunday")==0) w=6;
	else {
		printf("Command is incorrect.\n");
		return -1;	
	}
	return w;
}

int getfloor(){
	int f;
	if(nextword()==0){
		printf("Command is incorrect.\n");
		return -1;	
	}	
	if(strlen(str)!=1){
		printf("Command is incorrect.\n");
		return -1;	
	}
	f=str[0]-'0';
	if(f<1||f>5){
		printf("Command is incorrect.\n");
		return -1;	
	}
	return f-1;
}

int getrow(){
	int r;
	if(nextword()==0){
		printf("Command is incorrect.\n");
		return -1;	
	}
	if(strlen(str)!=1){
		printf("Command is incorrect.\n");
		return -1;	
	}
	r=str[0]-'0';
	if(r<1||r>5){
		printf("Command is incorrect.\n");
		return-1;	
	}
	return r-1;
}
int getcolumn(){
	int c;
	if(nextword()==0){
		printf("Command is incorrect.\n");
		return -1;	
	}
	if(strlen(str)!=1){
		printf("Command is incorrect.\n");
		return -1;	
	}
	c=str[0]-'0';
	if(c<1||c>5){
		printf("Command is incorrect.\n");
		return-1;	
	}
	return c-1;
}

void putweek(int w){
	if(w==0) printf(" Monday ");
	else if(w==1) printf(" Tuesday ");
	else if(w==2) printf(" Wednesday ");
	else if(w==3) printf(" Thursday ");
	else if(w==4) printf(" Friday ");
	else if(w==5) printf(" Saturday ");
	else if(w==6) printf(" Sunday ");
}

void display(){
	int w,f,r,c;
	FILE *fp;
    fp = fopen("seat.dat", "r");
    if (fp == NULL) {
       printf("File open failed.\n");      
       return;
    }
    for (w=0; w< 6; w++)
         for (f=0; f<5; f++)
               for (r=0; r<4; r++)
                     for (c= 0; c< 4; c++)
                         seat[w][f][r][c] = fgetc(fp);
    fclose(fp);
	w=getweek();
	//printf("week=%d\n",week);
	if(w==-1) return;
	if(nextword()==0){
		printf("Command is incorrect.\n");
		return ;	
	}
	//printf ("%s\n",str);
	if(strcmp(str,"Floor")!=0){
		printf("Command is incorrect.\n");
		return ;	
	}
	f=getfloor();
	//printf("floor=%d\n",floor);
	if(f==-1) return;
	for(r=0;r<4;r++){
		for(c=0;c<4;c++){
			if (seat[w][f][r][c]==id)	printf("%c",'2');					
			else if (seat[w][f][r][c]!='0') printf("%c",'1');
			else printf("%c",'0');
		}
		printf("\n");
	}					   		
} 

void reservation( ){
	int w,f,r,c;
	FILE *fp;
    fp = fopen("seat.dat", "r");
    if (fp == NULL) {
       printf("File open failed.\n");      
       return;
    }
    for (w=0; w< 6; w++)
         for (f=0; f<5; f++)
               for (r=0; r<4; r++)
                     for (c= 0; c< 4; c++)
                         seat[w][f][r][c] = fgetc(fp);
    fclose(fp);
	printf(" Appointment information of  User %c :\n",id);
	for (w=0;w<6;w++)
		for(f=0;f<5;f++)
			for(r=0;r<4;r++)
				for(c=0;c<4;c++)
					if (seat[w][f][r][c]==id){				
						putweek(w);
						printf(" Floor %d Seat %d %d .\n",f+1,r+1,c+1);
					} 		
}

void reserve(){
	int found=0;
	int w,f,r,c;
	FILE *fp;
    fp = fopen("seat.dat", "r");
    if (fp == NULL) {
       printf("File open failed.\n");      
       return;
    }
    for (w=0; w< 6; w++)
         for (f=0; f<5; f++)
               for (r=0; r<4; r++)
                     for (c= 0; c< 4; c++)
                         seat[w][f][r][c] = fgetc(fp);
    fclose(fp);
	w=getweek();
	if(w==-1){
		printf("Command is incorrect.\n");
		return ;	
	}
	for(int i=0;i<5;i++)
		for(int j=0;j<4;j++)
		   for(int k=0;k<4;k++)
			 if (seat[w][i][j][k]==id){				
				printf("Cannot make duplicate appointments.\n");
				printf("Command is incorrect.\n");
				return ;
			} 
	if(nextword()==0){
		printf("Command is incorrect.\n");
		return ;	
	}
	if(strcmp(str,"Floor")!=0){
		printf("Command is incorrect.\n");
		return ;	
	}
	f=getfloor();
	if(f==-1){
		printf("Command is incorrect.\n");
		return ;	
	}
	if(nextword()==0){
		printf("Command is incorrect.\n");
		return ;	
	}
	if(strcmp(str,"Seat")!=0){
		printf("Command is incorrect.\n");
		return ;	
	}
	r=getrow();
	if(r==-1){
		printf("Command is incorrect.\n");
		return ;	
	};
	c=getcolumn();
	if(c==-1){
		printf("Command is incorrect.\n");
		return ;	
	}		
	if ( seat[w][f][r][c]=='0'){
		found=1;
		seat[w][f][r][c]=id;
		//printf("%d Floor %d Seat %d %d is empty.\n",w+1,f+1,r+1,c+1);	
	}
	if(!found){
		printf("Command is incorrect.\n");
		return;
	}
	
	/*
	if(!found){
		for(f=0;f<5;f++)	
			for(r=0;r<4;r++)
				for(c=0;c<4;c++)
					if ( !found && seat[w][f][r][c]=='0'){
						found=1;					
						seat[w][f][r][c]=id;
						printf("%d Floor %d Seat %d %d is empty.\n",w+1,f+1,r+1,c+1);	
					}
		if(found==0) {
				printf("No seat available.\n");
				printf("Command is incorrect.\n");
				return;		   		
		} 	
	}	
	*/	
	printf("OK!\n");
	fp=fopen("seat.dat","w");
	if(fp==NULL){
			printf("File open failed.\n");
			return ;
	}
	for (w=0; w< 6; w++)
        for (f=0; f<5; f++)
            for (r=0; r<4; r++)
                    for (c= 0; c< 4; c++)
                        fputc(seat[w][f][r][c], fp);
        
    fclose(fp);	
}

int nextword( ){       
	int i=0;
	while(line[idx]==' ' ) 
		idx++;	
	while(line[idx]!=' '&& line[idx]!='\n'&&line[idx]!='\0') {
		str[i]=line[idx];		
		i++;
		idx++;
	}
	str[i]='\0';
	if(i==0) return 0;
	else return 1;	
}

void Output_command_list(){
	printf("  ****************Command List****************\n");
	printf("  Login\n");
	printf("  Exit\n");
	printf("  Quit\n");
	printf("  Display week Floor floor\n");
	printf("  Reserve week Floor floor Seat row column\n");
	printf("  Reservation\n");
	printf("  Clear\n");	
	printf("  ********************************************\n");
}

void init(){
	int w,f,r,c;
	FILE *fp;
	fp=fopen("seat.dat","w");
	if(fp==NULL){
		printf("File open failed.\n");
		exit(1);
	}
	for (w=0; w< 6; w++)
         for (f=0; f<5; f++)
               for (r=0; r<4; r++)
                     for (c= 0; c< 4; c++)
                          fputc('0', fp);
        
    fclose(fp);
}