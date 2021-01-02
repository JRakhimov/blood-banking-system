#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include <stdio.h>
#include <mysql/mysql.h>

#define DATABASE_HOST "localhost"
#define DATABASE_NAME "os"
#define DATABASE_URER "root"
#define DATABSE_PASSWORD "root"

// Functions declarations

MYSQL *connectDatabase();

void closeConnection(MYSQL *connection);

void makeQuery(MYSQL *connection, char *query);

// Functions implementations

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

void closeConnection(MYSQL *connection) {
  printf("Terminating connection...\n");
  mysql_close(connection);
}

void makeQuery(MYSQL *connection, char *query) {
  // prepare prepared statement for transmisson and execution
  MYSQL_STMT *stmt= mysql_stmt_init(connection);
  mysql_stmt_prepare(stmt, query,strlen(query));
  mysql_stmt_execute(stmt);
  mysql_stmt_close(stmt);
}

#endif