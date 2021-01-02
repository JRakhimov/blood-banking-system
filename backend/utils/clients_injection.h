#ifndef CLIENTS_INJECTION_H
#define CLIENTS_INJECTION_H

#include "../entities/system/client.h"

#define MAX_ALLOWED_CLIENTS 10

static struct Client clients[MAX_ALLOWED_CLIENTS];

struct Client getClientByPhone(char *phone);

struct Client getClientByUsername(char *username);

struct Client getClientByUsername(char *username) {
  for (int i = 0; i < MAX_ALLOWED_CLIENTS; i++) {
    if (clients[i].type == 0 && strcmp(clients[i].admin.username, username) == 0) {
      return clients[i];
    } else if (clients[i].type == 1 && strcmp(clients[i].specialist.username, username) == 0) {
      return clients[i];
    }
  }
}

struct Client getClientByPhone(char *phone) {
  for (int i = 0; i < MAX_ALLOWED_CLIENTS; i++) {
    if (strcmp(clients[i].user.phoneNumber, phone) == 0) {
      return clients[i];
    }
  }
}

#endif