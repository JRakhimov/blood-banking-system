#ifndef USER_ENTITY_H
#define USER_ENTITY_H

struct User {
  int id;
  char phoneNumber[512];
  char password[512];
  char name[512];
  char date[512];
  char bloodType[512];
  char validStatus[512];
};

#endif


