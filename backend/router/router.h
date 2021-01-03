#ifndef ROUTER_H
#define ROUTER_H

#include <stdio.h>

#include "../entities/system/client.h"
#include "../entities/system/request.h"
#include "../entities/system/response.h"

/** Function Declarations */
int handleRequest(struct Client *client, struct Request *request);

int sendResponse(int sd, struct Response response);

int sendAll(int fd, void *buf, int n, int flags);

/** Function Implementations */
int handleRequest(struct Client *client, struct Request *request) {
  struct Response response;
  struct Route route = request->route;

  return EXIT_SUCCESS;
}

int sendAll(int fd, void *buf, int n, int flags) {
  int temp, total = 0;

  while (total < n) {
    temp = send(fd, buf + total, n - total, flags);

    if (temp == -1) {
      break;
    }

    total += temp;
  }

  return temp == -1 ? -1 : total;
}

int sendResponse(int sd, struct Response response) {
    int size = sizeof(response);
    if (sendAll(sd, &response, size, 0))
        return EXIT_SUCCESS;

    fprintf(stderr, "Failed to send response");
    return EXIT_FAILURE;
}

#endif