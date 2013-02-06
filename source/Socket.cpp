#include "headers/headers.h"

Socket::Socket()
{

}

Socket::Socket(const char *portParam, bool s, const char *ip)
{
	init(portParam, s, ip);
}

Socket::~Socket()
{

}

int Socket::init(const char *portParam, bool s, const char *ip)
{
	port = portParam;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_DGRAM; // UDP socket
	hints.ai_flags = AI_PASSIVE;

	if(!s)
	{
		if((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0)
		{
			printf("Error in function 'getaddrinfo'\n");
			loadFine = false;
			return -1;
		}
	}
	else 
	{
		if((rv = getaddrinfo(ip, port, &hints, &servinfo)) != 0)
		{
			printf("Error in function 'getaddrinfo'\n");
			loadFine = false;
			return -1;
		}
	}

	if((sockfd = socket(servinfo->ai_family, 
						servinfo->ai_socktype,
						servinfo->ai_protocol)) == -1)
	{
		printf("Error in function 'socket'.  Error code %i\n", sockfd);
		loadFine = false;
		return -2;
	}	
	if(!s)
	{
		if(bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
		{
			printf("Error in function 'bind'\n");
			loadFine = false;
			return -3;
		}
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
			printf("Waiting to recvfrom on port %s...\n", port);

			if((rv = recvfrom(sockfd, data.fb, sizeof(data), 0, (struct sockaddr *)&their_addr, &addr_len)) != -1)
			{
				printf("Recieved %i bytes!\n", rv);
				printf("value: %f\nslct: %i\n", data.value, data.slct);
			}
			else
			{
				printf("Error in function 'recvfrom' while recieving bytes!\n");
			}
			
			values[data.slct] = data.value;
		}
	}
	else
	{
		printf("Errors in socket initialization, stopping...\n");
	}
}

int Socket::send(int paramSelect, float paramValue)
{
	int bytesSent;
	data.value = paramValue;
	data.slct = paramSelect;
 
	if(loadFine)
	{
		bytesSent = sendto(sockfd, data.fb, 8, 0, servinfo->ai_addr, servinfo->ai_addrlen);
		printf("Sent %i packets!\n", bytesSent);
	}
	else
	{
		printf("Errors in socket initialization, stopping...\n");
	}
}