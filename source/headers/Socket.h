#pragma once

#include "headers.h"

union {
	struct {
		int		slct;
		float	value;
	};
	char fb[8];
} data;

class Socket
{
	private:
		const char *port;

		bool loadFine;

		struct addrinfo hints;
		struct addrinfo *servinfo;
		struct sockaddr_storage their_addr, blank;
		socklen_t addr_len;

		int rv;
		int sockfd;

		char buf[12];

	public:
		Socket();
		Socket(const char *portParam, bool s, const char *ip);
		~Socket();

		int init(const char *portParam, bool s, const char *ip);

		int listen();
		int send(int paramSelect, float paramValue);
};
