#ifndef CLIENTS_INJECTION_H
#define CLIENTS_INJECTION_H

#include "../entities/client.h"

#define MAX_ALLOWED_CLIENTS 10

static struct Client clients[MAX_ALLOWED_CLIENTS];

struct Client getClientByPhone(char *phone);

struct Client getClientByPhone(char *phone) {
  for (int i = 0; i < MAX_ALLOWED_CLIENTS; i++) {
    if (strcmp(clients[i])) {
      return clients[i];
    }
  }
}

#endif