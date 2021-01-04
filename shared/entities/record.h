#ifndef RECORD_ENTITY_H
#define RECORD_ENTITY_H

struct Record {
  int id;
  char phone_number[512];
  char date[512];
  char action[512];
};

#endif
