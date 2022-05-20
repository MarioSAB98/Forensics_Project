//C library statement
#include <stdlib.h>

//Driver program
int main(void)
{    
	char inode[10];
	printf("enter file inode: ");
	scanf("%s", inode);
	char terminal[]="sudo find / -type f -inum \"";
	strcat(terminal,inode);
	strcat(terminal,"\"");
	system(terminal);
}




//sudo find / -type f -inum "14888"

