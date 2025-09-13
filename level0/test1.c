#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 10  //����ֵ��ౣ��10����Ч�ַ�
int main(){
	FILE *fp;
	char line[81]="",k[N+1]="",v[N+1]="";
	int i,j,index,found;
	
	fp=fopen("data.txt","r");
	if(fp==NULL){
		printf("data.txt not found.\n");
		return 0;
	}
	
	printf("input a key\n");
    gets(k);//����Ҫ���ҵļ� 
    
	while (fgets(line, sizeof(line), fp)){  //����һ�з���line�� 
    	found=1;
    	for(i=0,j=0;found&&k[i]!='\0';i++,j++){
    		if(k[i]!=line[j]) found=0;
		}
		if(!found) continue;  //û�ҵ�ƥ��ļ�����������ѭ�� 
		if(line[j]!=':') continue;  //��һ���ַ�����ð�ţ�û�ҵ�ƥ��ļ�����������ѭ��
		//ÿ�ζ��Ǵ��ļ�ͷ���н���ƥ�䣬�ҵ��ĵ�һ�������������ַ�������������ļ���Ӧ��ֵ�������Ǻ�����У����Խ�����ظ���������
		//����ļ��ĵ�ǰ���ǿ��� ����Ϊ��Ӧλ���ַ������foundΪ0��������ѭ�� �����Կ���������Խ���� 
		for(i=j+1,index=0;line[i]!='\0';i++,index++)
			v[index]=line[i];
		v[index]='\0';
		printf("key:value=%s:%s\n",k,v);
		fclose(fp);
		return 0;
	}
	printf("key not found!\n");  
	fclose(fp);      
    return 0;
}
