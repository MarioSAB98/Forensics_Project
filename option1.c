//C library statement
#include <stdlib.h>

//Driver program
int main(void)
{    
	char filename[50];
	char *inode;
	printf("enter file name: ");
	scanf("%s", filename);
	printf(filename);
	printf("\n");
	char terminal[]="locate -r /";
	strcat(terminal,filename);
	strcat(terminal,"$");
	system(terminal);
	scanf(system(terminal), inode);
	printf("Inode is: %s",inode);
	printf("\n");

}




//find / -type f -name ""

//locate -r /node$

//stat ""
