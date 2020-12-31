#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include <stdio.h>
#include <mysql/mysql.h>

#define DATABASE_HOST "localhost"
#define DATABASE_NAME "os"
#define DATABASE_URER "root"
#define DATABSE_PASSWORD "root"

MYSQL *connectDatabase();

void disconnectDatabase(MYSQL *connection);

MYSQL *connectDatabase() {
  MYSQL *connection = mysql_init(NULL);

  printf("Connecting to database:\n");

  // check if connection to data base was successfull
  if(!(mysql_real_connect(connection, DATABASE_HOST, DATABASE_URER, DATABSE_PASSWORD, DATABASE_NAME, 0, NULL, 0))){
      fprintf(stderr,"\nError:  %s [%d] \n", mysql_error(connection), mysql_errno(connection));
      exit(1);
  }

  printf("Connection established\n\n");

  return connection;
}

void disconnectDatabase(MYSQL *connection) {
  printf("Terminating connection...\n");
  mysql_close(connection);
}


#endif