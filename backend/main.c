#include <stdio.h>
#include "utils/bootstrap/bootstrap.c"

int main() {
  setbuf(stdout, NULL);

  return startServer();
}

// gcc main.c $(mysql_config --libs) -o main $(mysql_config --cflags)
