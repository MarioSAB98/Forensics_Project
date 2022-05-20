//C library statement
#include <stdlib.h>
#include <stdio.h>

//Driver program
int main(void)
{    
	char path[1024];
	char keyword[1024];
	char terminal[]="grep ";
	
	printf("enter file path: ");
	scanf("%s", path);
	printf("enter search keyword: ");
	scanf("%s", keyword);
	
	strcat(keyword," ");
	printf("this is keyword: %s", keyword);
	printf("\n");
	strcat(keyword,path);
	printf("this is keyword: %s", keyword);
	printf("\n");
	strcat(terminal,keyword);
	printf("this is terminal: %s", terminal);
	printf("\n");
	system(terminal);
}




//cd path

//grep phoenix sample2
