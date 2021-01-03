#ifndef ADMIN_QUERIES_H
#define ADMIN_QUERIES_H

#include "../connector.h"
#include "../../entities/record.h"
#include "../../entities/user.h"

void insertNewHistoryRecord(int id, char *phone_number, char *typeOfAction)
{
    MYSQL connection = connectDatabase();
    char query[300];

    if((isEqual(typeOfAction,"Donor") ||(isEqual(typeOfAction,"Recipient")))){
        sprintf(query, "INSERT INTO %s.history (id,phone_number,dateofaction,typeofaction) VALUES(%d,\"%s\",NOW(),\"%s\");", DATABASE_NAME,id,phone_number,typeOfAction);
        makeQuery(connection, query);
        printf("Insertion was successful\n");
    }
    else{
        printf("Invalid insertion parameters");
    }
    closeConnection(connection);
}

void deleteHistoryRecord( char *phone_number){
    
    MYSQL connection = connectDatabase();
    char query[300];

        sprintf(query, "delete from %s.history where phone_number= \"%s\";", DATABASE_NAME, phone_number);
        makeQuery(connection, query);
        printf("Deletion was successful\n");
    
    closeConnection(connection);
}

Record* selectHistoryRecords(char *phone_number, Record array[]){
    
    MYSQL connection = connectDatabase();
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[100];
    Record records[4096];
    int i=0;

    sprintf(query, "SELECT * FROM %s.history where phone_number = %s;", DATABASE_NAME, phone_number);

    mysql_query(connection, query);

    res = mysql_store_result(connection);

    for(int i=0; i < sizeof(records)/sizeof(Record); i++ ) {
        records[i].id = 0;
    }

    while(row = mysql_fetch_row(res)) {
        records[i].id = atoi(row[0]);
        records[i].phone_number = row[1];
        records[i].date = row[2];
        records[i].action = row[3];
        
        i++;
    }
    i=0;
    mysql_free_result(res); // free result set
    closeConnection(connection); // close connection

    for(int i=0; i < sizeof(records)/sizeof(User); i++) {
        array[i]=records[i];
    }

    return array;
}


#endif