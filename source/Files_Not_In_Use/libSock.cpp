/*
 *  libSock.cpp
 *  
 *	This is the companion file for the Socket Shortcuts library. Written in C++.
 *
 *  Created by Eric Osburn on 7/13/11.
 *  Copyright 2011 DweebsUnited. All rights reserved.
 *
 */

#include "headers/libSock.h"

Sock::Sock()
{

}

Sock::~Sock()
{

}

int Sock::init(char *ipstr){
	ipstr[INET6_ADDRSTRLEN];
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
}

int Sock::getaddress(char *address, char *port){
	int status;
	if ((status = getaddrinfo(address, port, &hints, &list)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }
	
	servinfo = list;
	
	if (servinfo != NULL){
		
		if (servinfo->ai_family == AF_INET){
			
			printf("IPV4: ");
			
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)servinfo->ai_addr;
			
            addr = &(ipv4->sin_addr);
			
		} else {
			printf("IPV6: ");
			
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)servinfo->ai_addr;
            
			addr = &(ipv6->sin6_addr);
		}
	}
}

int Sock::recFrom()
{

}

int Sock::sendall(char* buf, int len){
	int total = 0;        // how many bytes we've sent
	int bytesleft = len; // how many we have left to send
	int n = 0;
	
	while(total < len) {
		n = send(sockfd, buf+total, bytesleft, 0);
		if (n == -1) { break; }
		total += n;
		bytesleft -= n;
	}
	
	len = total; // return number actually sent here
	
	std::cout << "sent " << total << " bytes\n\n";
	
	return n==-1?-1:0; // return -1 on failure, 0 on success
}
