#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>


void option1();
void option2();
void option5();
void option6();
void read();
void scan();
void inode();
void delete();
void updatedb();












void main()
{
	bool exit = false;
	while(!exit)
	{
		int input;
		printf("Welcome to this basic forensics tool\n");
		printf("To find the inode number of a file press 1\n");
		printf("To find the file belonging to a certain inode number press 2\n");
		printf("To make a packet capture from network device press 3\n");
		printf("To search for a keyword in a disk image press 4\n");
		printf("To exit press 5\n");
		scanf("%d", input);
		switch(input)
		{
			case 1:
				option1();
				break;
			case 2:
				option2();
				break;
			case 3:
				option5();
				break;
			case 4:
				option6();
				break;
			case 5:
				exit = true;
				break;
			default:
				printf("Invalid choice!");
				break;
		}
	}

}









option1()
{
	char fileText [1024];
	updatedb();
	scan();
	read(fileText);
	delete();
	inode(fileText);
}






option2()
{
	char inode[10];
	printf("enter file inode: ");
	scanf("%s", inode);
	char terminal[]="sudo find / -type f -inum \"";
	strcat(terminal,inode);
	strcat(terminal,"\"");
	system(terminal);
}



option5()
{
	findDevice();
	getInfo();
	liveCapture();
	return 0;
}





option6()
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





