#ifndef SOCKET_DEPENDENCIES_H
#define SOCKET_DEPENDENCIES_H

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

static int socketClientId;

void closeSocketConnection() {
  close(socketClientId);
}

#endif