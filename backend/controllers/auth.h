#ifndef AUTH_CONTROLLERS_H
#define AUTH_CONTROLLERS_H

#include "../../shared/entities/system/response.h"
#include "../../shared/entities/system/request.h"
#include "../../shared/entities/user.h"
#include "../database/queries/user.h"

// Declarations
struct Response userLogin(struct Client *client, struct Request request);

// Implementations
struct Response userLogin(struct Client *client, struct Request request) {
  struct Response response;

  if (validUser(request.phoneNumber, request.password) == 1) {
    struct User user = selectUserByPhoneNumber(request.phoneNumber);

    response.status = 1;
    response.data.user = user;
  }

  return response;
}

#endif