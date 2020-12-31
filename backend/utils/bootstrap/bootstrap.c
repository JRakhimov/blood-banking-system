#include "bootstrap_injection.h"
#include "../clients_injection.h"

int startServer();

int initMasterSocket();

int initAddress();

int handleConnections();

int handleNewConnection();

fd_set readFds;

struct sockaddr_in address;

int masterSocket;
int addressLength;
int activity;

int startServer() {
  if (initMasterSocket()) {
    fprintf(stderr, "Master socket init error");
    return EXIT_FAILURE;
  }

  if (initAddress()) {
    fprintf(stderr, "Address init error");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int initMasterSocket() {
  int opt = 1;

  for (int i = 0; i < MAX_ALLOWED_CLIENTS; i++) {
    // init socket for clients
  }

  // Creating master socket
  masterSocket = socket(AF_INET, SOCK_STREAM, 0);

  if (masterSocket == 0) {
    perror("Error: creating master socket");
    return EXIT_FAILURE;
  }

  // Allow multiple connections logic
  if (setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, (char*) &opt, sizeof(opt)) < 0) {
    perror("Error: setsockopt");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int initAddress() {
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  addressLength = sizeof(address);

  if (bind(masterSocket, (struct sockaddr *) &address, addressLength) < 0) {
    perror("Error: binding socket to port");
    return EXIT_FAILURE;
  }

  if (listen(masterSocket, 3) < 0) {
    perror("Error: set listener");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
