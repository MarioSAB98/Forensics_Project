//C library statement
#include <stdlib.h>

//Driver program
int main(void)
{    
	char path[1024];
	char filename[50];
	char keyword[50];
	char terminal[]="cd ";
	printf("enter file path: ");
	scanf("%s", path);
	strcat(terminal,path);
	system(terminal);
	printf("enter filename: ");
	scanf("%s", filename);
	printf("enter search keyword: ");
	scanf("%s", keyword);
	char search[]="grep ";
	printf(search);
	strcat(search,keyword);
	strcat(search,filename);
	printf("here\n");
	printf(search);
	printf("\nhere\n");
	system(search);
}




//cd path

//grep phoenix sample2
