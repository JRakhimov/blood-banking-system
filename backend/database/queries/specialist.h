#ifndef SPECIALIST_QUERIES_H
#define SPECIALIST_QUERIES_H

#include "../connector.h"
#include "../../entities/specialist.h"

void insertNewSpecialist(int id, char *name, char *password)
{
    MYSQL connection = connectDatabase();
    char query[100];
    sprintf(query, "INSERT INTO %s.specialist (id, name, password) VALUES(%d,\"%s\",\"%s\");", DATABASE_NAME, id, name, password);
    printf("%s\n", query);

    makeQuery(connection, query);
    printf("Insertion was successful\n");

    closeConnection(connection);
}

Specialist SelectSpecialistByName(char *name)
{
    struct Specialist specialist;

    MYSQL connection = connectDatabase();
    char query[100];
    sprintf(query, "SELECT * FROM %s.specialist where name = \"%s\";", DATABASE_NAME, name);

    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_query(connection, query);

    res = mysql_store_result(connection);
    while (row = mysql_fetch_row(res))
    {
        specialist.id = atoi(row[0]);
        specialist.name = row[1];
        specialist.password = row[2];
    }

    mysql_free_result(res);
    closeConnection(connection);

    return specialist;
}

void DeleteSpecialistByName(char *name)
{
    MYSQL connection = connectDatabase();

    char query[100];
    sprintf(query, "DELETE from test.specialist where name = \"%s\";", name);
    //prepare prepared statement for transmisson and execution
    makeQuery(connection, query);

    printf("Deletion was successful\n");
    closeConnection(connection);
}

void UpdateSpecialistPassword(char *name, char *password)
{
    MYSQL connection = connectDatabase();

    char query[100];
    sprintf(query, "UPDATE test.specialist SET password = \"%s\" where name = \"%s\";", password, name);

    makeQuery(connection, query);

    printf("Update was successful\n");
    closeConnection(connection);
}

int validSpecialist(char *name, char *password)
{

    MYSQL connection = connectDatabase();

    //variable definnition
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query1[100];
    char *DBname;
    char *DBpassword; // in future will be used for password

    char *userName = name;
    char *userPassword = password;

    int nameStatus = 0;
    int passwordStatus = 0;
    int totalStatus = 0; // return 1 if true, 0 if false

    //#####

    //Extracting name email(password) and validate with input
    sprintf(query1, "SELECT name,password FROM test.specialist");

    mysql_query(connection, query1);

    res = mysql_store_result(connection);

    while (row = mysql_fetch_row(res))
    {
        DBname = row[0];
        DBpassword = row[1];

        if (IsEqual(DBname, userName))
        {
            nameStatus = 1;
            if (IsEqual(DBpassword, userPassword))
            {
                passwordStatus = 1;
                break;
            }
            else
            {
                passwordStatus = 0;
            }
        }
        else
        {
            nameStatus = 0;
        }
    }

    mysql_free_result(res);

    if (nameStatus == 0 || passwordStatus == 0)
    {
        totalStatus = 0;
    }
    else
    {
        if (nameStatus == 1 && passwordStatus == 1)
        {
            totalStatus = 1;
        }
    }
    //#####
    closeConnection(connection);
    return totalStatus;
}

#endif