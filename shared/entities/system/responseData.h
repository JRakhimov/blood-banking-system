#ifndef RESPONSE_DATA_ENTITY_H
#define RESPONSE_DATA_ENTITY_H

#include "../user.h"

struct ResponseData {
  union {
    struct User user;
  };
};

#endif