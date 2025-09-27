#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 15       	//命令行中最长单词的长度
#define NWEEK 7    	//每周天数
#define NFLOOR 10  	//最大楼层数
#define NROW 50		//每层最大排数
#define NCOLUMN 50	//每层每排最大列数

char line[81],str[N],id;
char seat[NWEEK][NFLOOR][NROW][NCOLUMN];
int nfloor,level[NFLOOR][2];//nfloor是实际楼层数,level[NFLOOR][2]是每层的实际排数和列数
int idx=0,spv=0;	//idx即index指向line的当前位置，spv即supervisor说明是否是管理员模式

void Output_command_list();//输出命令清单
void init();//初始化文件
int nextword();//从line的idx处起识别出一个单词返回1否则返回0
void display();//显示某天某层的座位预约信息
void reservation();//显示当前用户的所有座位预约信息
void reserve();//为当前用户预约某天某层某排某列的指定座位
int getweek();//从命令行中识别出代表“星期”的单词，并转化为整型作为数组下标
int getfloor();//从命令行中识别出代表“层数”的单词，并转化为整型作为数组下标
int getrow();//从命令行中识别出代表“排数”的单词，并转化为整型作为数组下标
int getcolumn();//从命令行中识别出代表“列数”的单词，并转化为整型作为数组下标
void getusername();//从命令行中识别出代表“ID”的单词
void putweek(int);//将整型转化为代表“星期”的单词输出
void clear();//清空所有预约信息，管态执行
void s_display();//显示某天某层的座位预约信息，管态执行
void s_reservation();//显示用户的所有座位预约信息，管态执行
void s_reserve();//为当前用户预约某天某层某排某列的指定座位，管态执行
void reset();//重新设置楼层数以及各层座位分布，管态执行
void cancel();//取消预约 ，管态执行 

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
				spv=0;          		
		   } 		   		
		   else if(strcmp(line,"Admin")==0) {
		   		printf("Admin Login.\n");
				spv=1; 
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
			if(spv!=1) {
				printf("Command can only be executed by management personnel.\n");
				printf("Command is incorrect.\n");		   		
		   	} 
			else clear();
		}
		else if(strcmp(str,"S_display")==0) {
			if(spv!=1) {
				printf("Command can only be executed by management personnel.\n");
				printf("Command is incorrect.\n");		   		
		   	} 
			else s_display();
		}
		else if(strcmp(str,"S_reservation")==0) {
			if(spv!=1) {
				printf("Command can only be executed by management personnel.\n");
				printf("Command is incorrect.\n");		   		
		   	} 
			else s_reservation();
		}
		else if(strcmp(str,"S_reserve")==0) {
			if(spv!=1) {
				printf("Command can only be executed by management personnel.\n");
				printf("Command is incorrect.\n");		   		
		   	} 
			else s_reserve();
		}
		else if(strcmp(str,"Reset")==0) {
			if(spv!=1) {
				printf("Command can only be executed by management personnel.\n");
				printf("Command is incorrect.\n");		   		
		   	} 
			else reset();
		}
		else if(strcmp(str,"Cancel")==0) {
			if(spv!=1) {
				printf("Command can only be executed by management personnel.\n");
				printf("Command is incorrect.\n");		   		
		   	} 
			else cancel();
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
	if(f<1||f>NFLOOR){
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
	if(r<1||r>NROW){
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
	if(c<1||c>NCOLUMN){
		printf("Command is incorrect.\n");
		return-1;	
	}
	return c-1;
}

void getusername(){
	if(nextword()==0){
		printf("Command is incorrect.\n");
		return ;	
	}
	//printf ("%s\n",str);
	if(str[0]<'A' || str[0]>'Z'||strlen(str)!=1){
		printf("Command is incorrect.\n");
		return ;	
	}
	id=str[0];
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
	FILE *fp1,*fp2;	
	fp1=fopen("seat.dat","r");
	fp2=fopen("config.dat","r");
	if(fp1==NULL||fp2==NULL){
		printf("File open failed.\n");
		return ;
	}	
	fscanf(fp2,"%4d",&nfloor);
	for(int i=0;i<nfloor;i++){
		fscanf(fp2,"%4d%4d",&level[i][0],&level[i][1]);
	}
	for (w=0; w< NWEEK; w++)
         for (f=0; f<nfloor; f++)
               for (r=0; r<level[f][0]; r++)
                     for (c= 0; c<level[f][1]; c++)
                        seat[w][f][r][c]=fgetc(fp1);	   
    fclose(fp1);
	fclose(fp2);
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
	for (r=0; r<level[f][0]; r++)
        for (c= 0; c<level[f][1]; c++){
			if (seat[w][f][r][c]==id)	printf("%c",'2');					
			else if (seat[w][f][r][c]!='0') printf("%c",'1');
			else printf("%c",'0');		
		printf("\n");
		}					   		
} 

void reservation( ){
	int w,f,r,c;
	FILE *fp1,*fp2;	
	fp1=fopen("seat.dat","r");
	fp2=fopen("config.dat","r");
	if(fp1==NULL||fp2==NULL){
		printf("File open failed.\n");
		return ;
	}	
	fscanf(fp2,"%4d",&nfloor);
	for(int i=0;i<nfloor;i++){
		fscanf(fp2,"%4d%4d",&level[i][0],&level[i][1]);
	}
	for (w=0; w< NWEEK; w++)
         for (f=0; f<nfloor; f++)
               for (r=0; r<level[f][0]; r++)
                     for (c= 0; c<level[f][1]; c++)
                        seat[w][f][r][c]=fgetc(fp1);	   
    fclose(fp1);
	fclose(fp2);
	printf(" Appointment information of  User %c :\n",id);
	for (w=0; w< NWEEK; w++)
        for (f=0; f<nfloor; f++)
            for (r=0; r<level[f][0]; r++)
                for (c= 0; c<level[f][1]; c++)
					if (seat[w][f][r][c]==id){				
						putweek(w);
						printf(" Floor %d Seat %d %d .\n",f+1,r+1,c+1);
					} 		
}

void reserve(){
	int found=0;
	int w,f,r,c;
	FILE *fp1,*fp2;	
	fp1=fopen("seat.dat","r");
	fp2=fopen("config.dat","r");
	if(fp1==NULL||fp2==NULL){
		printf("File open failed.\n");
		return ;
	}	
	fscanf(fp2,"%4d",&nfloor);
	for(int i=0;i<nfloor;i++){
		fscanf(fp2,"%4d%4d",&level[i][0],&level[i][1]);
	}
	for (w=0; w< NWEEK; w++)
         for (f=0; f<nfloor; f++)
               for (r=0; r<level[f][0]; r++)
                     for (c= 0; c<level[f][1]; c++)
                          seat[w][f][r][c]=fgetc(fp1);	   
    fclose(fp1);
	fclose(fp2);
	w=getweek();
	if(w==-1){
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
	for(int i=0;i<nfloor;i++)
		for(int j=0;j<level[i][0];j++)
		   for(int k=0;k<level[i][1];k++)
			  if (seat[w][i][j][k]==id){				
				printf("Cannot make duplicate appointments.\n");
				printf("Command is incorrect.\n");
				return ;
			  } 
	if ( seat[w][f][r][c]=='0'){
		found=1;
		seat[w][f][r][c]=id;
		//printf("%d Floor %d Seat %d %d is empty.\n",w+1,f+1,r+1,c+1);	
	}
	if(!found)printf("Command is incorrect.\n");	
	else {
		printf("OK!\n");
		fp1=fopen("seat.dat","w");
		if(fp1==NULL){
			printf("File open failed.\n");
			return ;
		}
		for (w=0; w< NWEEK; w++)
         	for (f=0; f<nfloor; f++)
               for (r=0; r<level[f][0]; r++)
                     for (c= 0; c<level[f][1]; c++)
                          fputc(seat[w][f][r][c], fp1);
        
    	fclose(fp1);
	}
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
	printf("  Display w Floor f\n");
	printf("  Reserve w Floor f Seat r c\n");
	printf("  Reservation\n");
	printf("  Clear\n");
	printf("  S_display w Floor f\n");	
	printf("  S_reservation id\n");
	printf("  S_reserve id w Floor f Seat r c\n");		
	printf("  Reset\n");	
	printf("  Cancel id w Floor f\n");	
	printf("  ********************************************\n");
}

void init(){
	int w,f,r,c;
	FILE *fp1,*fp2;	
	fp1=fopen("seat.dat","w");
	fp2=fopen("config.dat","w");
	if(fp1==NULL||fp2==NULL){
		printf("File open failed.\n");
		return ;
	}
	printf("Enter the number of floors.\n");
	scanf("%d",&nfloor);
	fprintf(fp2,"%4d",nfloor);
	for(int i=1;i<=nfloor;i++){
		printf("Enter the number of rows and columns for this layer.\n");
		scanf("%d %d",&level[i][0],&level[i][1]);
		fprintf(fp2,"%4d%4d",level[i][0],level[i][1]);
	}
	fflush(stdin);
	for (w=0; w< NWEEK; w++)
         for (f=0; f<nfloor; f++)
               for (r=0; r<level[f][0]; r++)
                     for (c= 0; c<level[f][1]; c++)
                          fputc('0', fp1);						      
    fclose(fp1);
	fclose(fp2);
}

void clear(){
	int w,f,r,c;	
	FILE *fp1,*fp2;	
	fp1=fopen("seat.dat","w");
	fp2=fopen("config.dat","r");
	if(fp1==NULL||fp2==NULL){
		printf("File open failed.\n");
		return ;
	}	
	fscanf(fp2,"%4d",&nfloor);
	for(int i=0;i<nfloor;i++){
		fscanf(fp2,"%4d%4d",&level[i][0],&level[i][1]);
	}
	for (w=0; w< NWEEK; w++)
         for (f=0; f<nfloor; f++)
               for (r=0; r<level[f][0]; r++)
                     for (c= 0; c<level[f][1]; c++)
                          fputc('0', fp1);	   
    fclose(fp1);
	fclose(fp2);
}

void s_display(){
	int w,f,r,c;
	FILE *fp1,*fp2;	
	fp1=fopen("seat.dat","r");
	fp2=fopen("config.dat","r");
	if(fp1==NULL||fp2==NULL){
		printf("File open failed.\n");
		return ;
	}	
	fscanf(fp2,"%4d",&nfloor);
	for(int i=0;i<nfloor;i++){
		fscanf(fp2,"%4d%4d",&level[i][0],&level[i][1]);
	}
	for (w=0; w< NWEEK; w++)
         for (f=0; f<nfloor; f++)
               for (r=0; r<level[f][0]; r++)
                     for (c= 0; c<level[f][1]; c++)
                          seat[w][f][r][c] = fgetc(fp1);     
    fclose(fp1);
	fclose(fp2);    
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
	for(r=0;r<level[f][0];r++){
		for(c=0;c<level[f][1];c++) 
			printf("%c",seat[w][f][r][c]);
		printf("\n");
	}				
}

void s_reservation(){
	int w,f,r,c;
	FILE *fp1,*fp2;	
	fp1=fopen("seat.dat","r");
	fp2=fopen("config.dat","r");
	if(fp1==NULL||fp2==NULL){
		printf("File open failed.\n");
		return ;
	}	
	fscanf(fp2,"%4d",&nfloor);
	for(int i=0;i<nfloor;i++){
		fscanf(fp2,"%4d%4d",&level[i][0],&level[i][1]);
	}
	for (w=0; w< NWEEK; w++)
         for (f=0; f<nfloor; f++)
               for (r=0; r<level[f][0]; r++)
                     for (c= 0; c<level[f][1]; c++)
                          seat[w][f][r][c] = fgetc(fp1);     
    fclose(fp1);
	fclose(fp2);	
	getusername();
	for (w=0; w< NWEEK; w++)
		for(f=0; f<nfloor; f++)
			for(r=0;r<level[f][0];r++)
				for(c=0;c<level[f][1];c++) 
					if (seat[w][f][r][c]==id){
						putweek(w);
						printf("Floor %d Seat %d %d .\n",f+1,r+1,c+1);
					}						
}

void s_reserve(){
	int found=0;
	int w,f,r,c;
	FILE *fp1,*fp2;	
	fp1=fopen("seat.dat","r");
	fp2=fopen("config.dat","r");
	if(fp1==NULL||fp2==NULL){
		printf("File open failed.\n");
		return ;
	}	
	fscanf(fp2,"%4d",&nfloor);
	for(int i=0;i<nfloor;i++){
		fscanf(fp2,"%4d%4d",&level[i][0],&level[i][1]);
	}
	for (w=0; w< NWEEK; w++)
         for (f=0; f<nfloor; f++)
               for (r=0; r<level[f][0]; r++)
                     for (c= 0; c<level[f][1]; c++)
                          seat[w][f][r][c]=fgetc(fp1);	   
    fclose(fp1);
	fclose(fp2);
	getusername();
	w=getweek();
	if(w==-1){
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
	for(int i=0;i<5;i++)
		for(int j=0;j<4;j++)
		   for(int k=0;k<4;k++)
			 if (seat[w][i][j][k]==id){				
				printf("Cannot make duplicate appointments.\n");
				printf("Command is incorrect.\n");
				return ;
			} 	
	if ( seat[w][f][r][c]=='0'){
		found=1;
		seat[w][f][r][c]=id;
		//printf("%d Floor %d Seat %d %d is empty.\n",w+1,f+1,r+1,c+1);	
	}
	if(!found)printf("Command is incorrect.\n");	
	else {
		printf("OK!\n");
		fp1=fopen("seat.dat","w");
		if(fp1==NULL){
			printf("File open failed.\n");
			return ;
		}
		for (w=0; w< NWEEK; w++)
         for (f=0; f<nfloor; f++)
               for (r=0; r<level[f][0]; r++)
                     for (c= 0; c<level[f][1]; c++)
                          fputc(seat[w][f][r][c], fp1);        
    	fclose(fp1);
	}
}

void cancel(){	
	int w,f,r,c;
	FILE *fp1,*fp2;	
	fp1=fopen("seat.dat","r");
	fp2=fopen("config.dat","r");
	if(fp1==NULL||fp2==NULL){
		printf("File open failed.\n");
		return ;
	}	
	fscanf(fp2,"%4d",&nfloor);
	for(int i=0;i<nfloor;i++){
		fscanf(fp2,"%4d%4d",&level[i][0],&level[i][1]);
	}
	for (w=0; w< NWEEK; w++)
         for (f=0; f<nfloor; f++)
               for (r=0; r<level[f][0]; r++)
                     for (c= 0; c<level[f][1]; c++)
                          seat[w][f][r][c]=fgetc(fp1);	   
    fclose(fp1);
	fclose(fp2);
	getusername();
	w=getweek();
	if(w==-1){
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
	for(int j=0;j<level[f][0];j++)
		for(int k=0;k<level[f][1];k++)
			 seat[w][f][j][k]='0'; 	
	fp1=fopen("seat.dat","w");
	if(fp1==NULL){
			printf("File open failed.\n");
			return ;
	}
	for (w=0; w< NWEEK; w++)
         for (f=0; f<nfloor; f++)
               for (r=0; r<level[f][0]; r++)
                     for (c= 0; c<level[f][1]; c++)
                          fputc(seat[w][f][r][c], fp1);        
    fclose(fp1);
}


void reset(){

}