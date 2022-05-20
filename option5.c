#include <stdio.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>




void findDevice();
void getInfo();
void liveCapture();
void printPacketInfo();




int main(int argc, char **argv)
{
	findDevice();
	getInfo();
	liveCapture();
	return 0;
}




















findDevice()
{
	char *device; /* Name of device (e.g. eth0, wlan0) */
	char error_buffer[PCAP_ERRBUF_SIZE]; /* Size defined in pcap.h */
    	/* Find a device */
    	device = pcap_lookupdev(error_buffer);
    	if (device == NULL) 
    	{
        	printf("Error finding device: %s\n", error_buffer);
        	return 1;
    	}

    	printf("Network device found: %s\n", device);
}

getInfo()
{
	char *device;
	char ip[13];
	char subnet_mask[13];
	bpf_u_int32 ip_raw; /* IP address as integer */
	bpf_u_int32 subnet_mask_raw; /* Subnet mask as integer */
	int lookup_return_code;
	char error_buffer[PCAP_ERRBUF_SIZE]; /* Size defined in pcap.h */
	
	struct in_addr address; /* Used for both ip & subnet */

	/* Find a device */
	device = pcap_lookupdev(error_buffer);
	if (device == NULL)
	{
		printf("%s\n", error_buffer);
		return 1;
	}
    
	/* Get device info */
	lookup_return_code = pcap_lookupnet
	(
		device,
		&ip_raw,
		&subnet_mask_raw,
		error_buffer
	);

	if (lookup_return_code == -1)
	{
		printf("%s\n", error_buffer);
		return 1;
	}
	
	/* Get ip in human readable form */
	address.s_addr = ip_raw;
	strcpy(ip, inet_ntoa(address));
	if (ip == NULL)
	{
		perror("inet_ntoa"); /* print error */
		return 1;
	}
    
	/* Get subnet mask in human readable form */
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


liveCapture()
{
	char *device;
	char error_buffer[PCAP_ERRBUF_SIZE];
	pcap_t *handle;
	const u_char *packet;
	struct pcap_pkthdr packet_header;
	int packet_count_limit = 1;
	int timeout_limit = 10000; /* In milliseconds */

	device = pcap_lookupdev(error_buffer);
	if (device == NULL)
	{
		printf("Error finding device: %s\n", error_buffer);
		return 1;
	}

	/* Open device for live capture */
	handle = pcap_open_live
	(
		device,
		BUFSIZ,
		packet_count_limit,
		timeout_limit,
		error_buffer
	);

	/* Attempt to capture one packet. If there is no network traffic
	and the timeout is reached, it will return NULL */
	packet = pcap_next(handle, &packet_header);
	if (packet == NULL)
	{
		printf("No packet found.\n");
		return 2;
	}

	/* Our function to output some info */
	printPacketInfo(packet, packet_header);

	return 0;
}



void printPacketInfo(const u_char *packet, struct pcap_pkthdr packet_header)
{
	printf("Packet capture length: %d\n", packet_header.caplen);
	printf("Packet total length %d\n", packet_header.len);
}














