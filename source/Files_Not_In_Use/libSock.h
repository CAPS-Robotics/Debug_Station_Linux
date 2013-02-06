/*
 *  libSock.h
 *  
 *	This is the header for the overall Socket Shortcuts library. Written in C++
 *
 *  Created by Eric Osburn on 7/13/11.
 *  Copyright 2011 DweebsUnited. All rights reserved.
 *
 *  Modified by Jacob Hegna
 *
 */

#ifndef LIBSOCK
#define LIBSOCK

#include "stdio.h"
#include "string.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netdb.h"
#include "arpa/inet.h"
#include <iostream>

class Sock {

	private:
		int sockfd;	//socket descriptor
		int sockType;	//tcp, raw, udp... used in initSock
		void *addr;		//needed for returning data
	
		struct addrinfo hints;	//hints for lookup
		struct addrinfo *servinfo;	//will hold first server returned
		struct addrinfo *list;	//list returned from dns lookup

	public:
		Sock();
		~Sock();
	
		int sendall(char* buf, int len);	//will keep sending in case packet breaks
		int recFrom();
		int init(char *ipstr);
		int getaddress(char *address, char *port);
	
};

#endif
