#ifndef REQUEST_H
#define REQUEST_H

struct Route
{
  char module[1024];
  char method[1024];
};

struct Request
{
  struct Route route;
};

#endif
