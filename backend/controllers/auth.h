#ifndef AUTH_CONTROLLERS_H
#define AUTH_CONTROLLERS_H

#include "../../shared/entities/system/response.h"
#include "../../shared/entities/system/request.h"
#include "../../shared/entities/user.h"

#include "../database/queries/specialist.h"
#include "../database/queries/admin.h"
#include "../database/queries/user.h"

// Declarations
struct Response userLogin(struct Client *client, struct Request request);

struct Response userRegistration(struct Client *client, struct Request request);

struct Response adminLogin(struct Client *client, struct Request request);

// Implementations
struct Response userLogin(struct Client *client, struct Request request) {
  struct Response response;

  if (validUser(request.phoneNumber, request.password) == 1) {
    struct User user = selectUserByPhoneNumber(request.phoneNumber);

    response.status = 1;
    response.data.user = user;
  } else {
    response.status = 0;
    sprintf(response.message, "Wrong phone or password");
  }

  return response;
}

struct Response userRegistration(struct Client *client, struct Request request) {
  struct Response response;

  if (validUser(request.phoneNumber, request.password) == 0) {
    insertNewUser(request.phoneNumber, request.password, request.name, request.date, request.bloodType, request.validStatus);

    struct User user = selectUserByPhoneNumber(request.phoneNumber);

    response.status = 1;
    response.data.user = user;
  } else {
    response.status = 0;
    sprintf(response.message, "User exists");
  }

  return response;
}

struct Response adminLogin(struct Client *client, struct Request request) {
  struct Response response;

  // if it is admin
  if (strcmp(request.username, "admin") == 0) {
    if (validAdmin(request.username, request.password) == 1) {
      struct Admin admin = selectAdminByName(request.username);

      response.status = 1;
      response.data.admin = admin;
    } else {
      response.status = 0;
      sprintf(response.message, "Wrong username or password");
    }
  } else {
    if (validSpecialist(request.username, request.password) == 1) {
      struct Specialist specialist = selectSpecialistByUsername(request.username);

      response.status = 1;
      response.data.specialist = specialist;
    } else {
      response.status = 0;
      sprintf(response.message, "Wrong username or password");
    }
  }

  return response;
}

#endif