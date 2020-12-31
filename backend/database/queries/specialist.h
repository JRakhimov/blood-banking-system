#ifndef SPECIALIST_QUERIES_H
#define SPECIALIST_QUERIES_H

#include "../connector.h"
#include "../../entities/specialist.h"

void insertNewSpecialist(int id, char *name, char *password)
{
    connectDatabase();
    char query[100];
    sprintf(query, "INSERT INTO %s.specialist (id, name, password) VALUES(%d,\"%s\",\"%s\");", DATABASE_NAME, id, name, password);
    printf("%s\n", query);

    MakeQuery(query);
    printf("Insertion was successful\n");
    close_connection();
}

S_user SelectSpecialistByName(char *name)
{

    struct S_user Specialist;

    connectDatabase();
    char query[100];
    sprintf(query, "SELECT * FROM test.specialist where name = \"%s\";", name);

    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_query(conn, query);

    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        Specialist.id = atoi(row[0]);
        Specialist.name = row[1];
        Specialist.password = row[2];
    }
    mysql_free_result(res);
    close_connection();
    return Specialist;
}

void DeleteSpecialistByName(char *name)
{
    connect_db();
    char query[100];
    sprintf(query, "DELETE from test.specialist where name = \"%s\";", name);
    //prepare prepared statement for transmisson and execution
    MakeQuery(query);

    printf("Deletion was successful\n");
    close_connection();
}

void UpdateSpecialistPassword(char *name, char *password)
{

    connect_db();
    char query[100];
    sprintf(query, "UPDATE test.specialist SET password = \"%s\" where name = \"%s\";", password, name);

    MakeQuery(query);

    printf("Update was successful\n");
    close_connection();
}

int ValidSpecialist(char *name, char *password)
{

    connect_db();

    //variable definnition
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query1[100];
    char *DBname;
    char *DBpassword; // in future will be used for password

    char *UserName = name;
    char *UserPassword = password;

    int NameStatus = 0;
    int PasswordStatus = 0;
    int TotalStatus = 0; // return 1 if true, 0 if false

    //#####

    //Extracting name email(password) and validate with input
    sprintf(query1, "SELECT name,password FROM test.specialist");

    mysql_query(conn, query1);

    res = mysql_store_result(conn);

    while (row = mysql_fetch_row(res))
    {
        DBname = row[0];
        DBpassword = row[1];

        if (IsEqual(DBname, UserName))
        {
            NameStatus = 1;
            if (IsEqual(DBpassword, UserPassword))
            {
                PasswordStatus = 1;
                break;
            }
            else
            {
                PasswordStatus = 0;
            }
        }
        else
        {
            NameStatus = 0;
        }
    }

    mysql_free_result(res);

    if (NameStatus == 0 || PasswordStatus == 0)
    {
        TotalStatus = 0;
    }
    else
    {
        if (NameStatus == 1 && PasswordStatus == 1)
        {
            TotalStatus = 1;
        }
    }
    //#####
    close_connection();
    return TotalStatus;
}

#endif