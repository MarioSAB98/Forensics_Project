//you must install the following packages before using the program
//sudo apt-get install libpcap-dev
//sudo apt install gcc
//sudo apt install plocate
//






// run using:
// gcc forensics_project.c -o final.out -lpcap
// ./final.out




#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <stdbool.h>


void option1();
void option2();
void option5();
void option6();
void read();
void scan();
void inode();
void delete();
void updatedb();
void find();
void DeviceInfo();
void capture();
void PacketInfo();











void main()
{
	bool exit = false;
	while(!exit)
	{
		char input;
		printf("\n");
		printf("Welcome to this basic forensics tool\n");
		printf("To find the inode number of a file press 1\n");
		printf("To find the file belonging to a certain inode number press 2\n");
		printf("To make a packet capture from network device press 3\n");
		printf("To search for a keyword in a disk image press 4\n");
		printf("To exit press 5\n");
		scanf(" %c", &input);
		switch(input)
		{
			case '1':
				option1();
				break;
			case '2':
				option2();
				break;
			case '3':
				option5();
				break;
			case '4':
				option6();
				break;
			case '5':
				exit = true;
				break;
			default:
				printf("Invalid choice!\n");
		}
	}

}









option1()
{
	char fileText [5000];
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
	char *device;
	char errbuf[PCAP_ERRBUF_SIZE];
	find(device, errbuf);
	DeviceInfo(device, errbuf);
	capture(device, errbuf);
	return 0;
}





option6()
{
	char path[5000];
	char keyword[5000];
	char terminal[]="grep ";
	
	printf("enter file path: ");
	scanf("%s", path);
	printf("enter search keyword: ");
	scanf("%s", keyword);
	
	strcat(keyword," ");
	printf("\n");
	strcat(keyword,path);
	printf("\n");
	strcat(terminal,keyword);
	printf("\n");
	system(terminal);
}





scan()
{
	char filename[5000];
	char *inode;
	printf("enter file name: ");
	scanf("%s", filename);
	char terminal[]="locate -r /";
	strcat(terminal,filename);
	strcat(terminal,"$ >> filepath.txt");
	system(terminal);
}

read(char FileTxt[])
{
	FILE *fileStream;
	fileStream = fopen("filepath.txt", "rw");
	fgets (FileTxt, 100, fileStream);
	

	
	
	if (fclose(fileStream) == 0) 
	{
        printf("The file is closed successfully.");
    	}
    	else 
    	{
        printf("The file is not closed.");
    	}
}

inode(char FileTxt[])
{
	char terminal[]="stat --format=\"%i\" ";
	strcat(terminal,FileTxt);
	system(terminal);
}

delete()
{
	int result = remove("filepath.txt");
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




find(char *device, char *error_buffer)
{
    	device = pcap_lookupdev(error_buffer);
    	if (device == NULL) 
    	{
        	printf("No devices found");
        	return 1;
    	}

    	printf("Device found: %s\n", device);
}

DeviceInfo(char *device, char *errbuf)
{
	char ip[13];
	char subnet_mask[13];
	bpf_u_int32 ip_raw;
	bpf_u_int32 subnet_mask_raw;
	int lookup_return_code;
	
	struct in_addr address;

	device = pcap_lookupdev(errbuf);
	if (device == NULL)
	{
		printf("%s\n", errbuf);
		return 1;
	}
    
	lookup_return_code = pcap_lookupnet
	(
		device,
		&ip_raw,
		&subnet_mask_raw,
		error_buffer
	);

	if (lookup_return_code == -1)
	{
		printf("%s\n", errbuf);
		return 1;
	}
	
	address.s_addr = ip_raw;
	strcpy(ip, inet_ntoa(address));
	if (ip == NULL)
	{
		perror("inet_ntoa");
		return 1;
	}
    
	address.s_addr = subnet_mask_raw;
	strcpy(subnet_mask, inet_ntoa(address));
	if (subnet_mask == NULL)
	{
		perror("inet_ntoa");
		return 1;
	}

	printf("Device: %s\n", device);
	printf("IP address: %s\n", ip);
	printf("Subnet mask: %s\n", subnet_mask);

	return 0;
}


capture(char *device, char *errbuf)
{
	pcap_t *handle;
	const u_char *packet;
	struct pcap_pkthdr packet_header;
	int packet_count_limit = 1;
	int timeout_limit = 10000;

	device = pcap_lookupdev(errbuf);
	if (device == NULL)
	{
		printf("Error finding device: %s\n", errbuf);
		return 1;
	}

	handle = pcap_open_live
	(
		device,
		BUFSIZ,
		packet_count_limit,
		timeout_limit,
		errbuf
	);


	packet = pcap_next(handle, &packet_header);
	if (packet == NULL)
	{
		printf("No packets found.\n");
		return 2;
	}


	PacketInfo(packet, packet_header);

	return 0;
}



void PacketInfo(const u_char *packet, struct pcap_pkthdr packet_header)
{
	printf("Packet capture length: %d\n", packet_header.caplen);
	printf("Packet total length %d\n", packet_header.len);
}





