#include "headers/headers.h"

Socket::Socket()
{

}

Socket::Socket(const char *portParam)
{
	init(portParam);
}

Socket::~Socket()
{

}

int Socket::init(const char *portParam)
{
	port = portParam;

	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_DGRAM; // UDP socket
	hints.ai_flags = AI_PASSIVE;

	if((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0)
	{
		printf("Error in function 'getaddrinfo'\n");
		loadFine = false;
		return -1;
	}

	if((sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		printf("Error in function 'socket'\n");
		loadFine = false;
		return -2;
	}	

	if(bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		printf("Error in function 'bind'\n");
		loadFine = false;
		return -3;
	}

	freeaddrinfo(servinfo);
	addr_len = sizeof(their_addr);

	loadFine = true;
	return 0;
}

int Socket::listen()
{
	if(loadFine)
	{
		while(true)
		{
			printf("Waiting to recvfrom...\n");

			if((rv = recvfrom(sockfd, data.fb, sizeof(data), 0, (struct sockaddr *)&their_addr, &addr_len)) != -1)
			{
				printf("Recieved %i bytes!\n");
				printf("value: %f\nslct: %i\n", data.value, data.slct);
			}
			else
			{
				printf("Error in function 'recvfrom'\n");
			}
			
			values[data.slct] = data.value;
		}
	}
	else
	{
		printf("Errors in socket initialization, stopping...\n");
	}
}
