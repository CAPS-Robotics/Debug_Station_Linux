#ifndef HEADERS_H
#define HEADERS_H

//ANSI-C standard headers
#include <string>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

//POSIX libraries
#include <pthread.h>

//OpenGL headers and extension libraries
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <IL/il.h>

//Project header files
#include "display.h"
#include "Socket.h"
#include "main.h"
#include "keys.h"
#include "parser.h" //Not a project header, but an XML parser made by Jacob Hegna

#endif
