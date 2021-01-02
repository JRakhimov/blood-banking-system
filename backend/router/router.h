#ifndef ROUTER_H
#define ROUTER_H

#include "../entities/system/client.h"
#include "../entities/system/request.h"
#include "../entities/system/response.h"

/** Function Declarations */
int handleRequest(struct Client *client, struct Request *request);

int sendResponse(int sd, struct Response response);

/** Function Implementations */
int handleRequest(struct Client *client, struct Request *request) {
  struct Response response;
  struct Route route = request->route;

  return EXIT_SUCCESS;
}

int sendResponse(int sd, struct Response response) {
    int size = sizeof(response);
    if (sendall(sd, &response, size, 0))
        return EXIT_SUCCESS;

    fprintf(stderr, "Failed to send response");
    return EXIT_FAILURE;
}

#endif