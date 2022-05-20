//C library statement
#include <stdlib.h>
#include <stdio.h>


void read();
void scan();
void inode();
void delete();
void updatedb();

//Driver program
int main(void)
{    

	
	char fileText [1024];
	updatedb();
	scan();
	read(fileText);
	delete();
	inode(fileText);


}

scan()
{
	char filename[50];
	char *inode;
	printf("enter file name: ");
	scanf("%s", filename);
	printf(filename);
	printf("\n");
	char terminal[]="locate -r /";
	strcat(terminal,filename);
	strcat(terminal,"$ >> SomeFile.txt");
	system(terminal);
}

read(char FileTxt[])
{
	FILE *fileStream;
	fileStream = fopen("SomeFile.txt", "rw");
	fgets (FileTxt, 100, fileStream);
	

	
	
	if (fclose(fileStream) == 0) 
	{
        printf("The file is closed successfully.");
    	}
    	else 
    	{
        printf("The file is not closed.");
    	}
    	
    	printf(FileTxt);
}

inode(char FileTxt[])
{
	char terminal[]="stat ";
	strcat(terminal,FileTxt);
	system(terminal);
}

delete()
{
	int result = remove("SomeFile.txt");
	if (result == 0) 
	{
        printf("The file is deleted successfully.");
    	}
    	else 
    	{
        printf("The file is not deleted.");
    	}
}

updatedb()
{
	system("sudo updatedb");
}


//find / -type f -name ""

//locate -r /node$

//stat ""
