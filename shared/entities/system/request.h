#ifndef REQUEST_ENTITY_H
#define REQUEST_ENTITY_H

#include "route.h"

struct Request {
  struct Route route;

  char phoneNumber[256];
  char password[256];
};

#endif