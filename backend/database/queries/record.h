#ifndef ADMIN_QUERIES_H
#define ADMIN_QUERIES_H

#include "../connector.h"
#include "../../../shared/entities/record.h"
#include "../../shared/entities/user.h"

void getUserHistory(int userId) {
    MYSQL *connection = connectDatabase();
    char query[300];

    sprintf(query, "SELECT * FROM %s.record WHERE donor_id = %d OR taker_id = %d;", DATABASE_NAME, userId);

    closeConnection(connection);
}

void getCanBeTakenBloodByType(char *type) {
    MYSQL *connection = connectDatabase();
    char query[300];

    sprintf(query, "SELECT * FROM %s.record WHERE blood_type = \"%s\" taker_id IS NULL AND action = \"donor\" AND status = \"approved\" LIMIT 1;", DATABASE_NAME, type);

    closeConnection(connection);
}

void getBloodsToAnalyze() {
    MYSQL *connection = connectDatabase();
    char query[300];

    sprintf(query, "SELECT * FROM %s.record WHERE action = \"analysis\" AND status = \"pending\" AND taker_id IS NULL;", DATABASE_NAME);

    closeConnection(connection);
}

void takeAnalysis(int userId) {
    MYSQL *connection = connectDatabase();
    char query[300];

    sprintf(query, "INSERT INTO %s.record (donor_id, action, status, date) VALUES(%d, \"analysis\", \"pending\", NOW());", DATABASE_NAME, userId);

    closeConnection(connection);
}

void donateBlood(int userId, char *type) {
    MYSQL *connection = connectDatabase();
    char query[300];

    sprintf(query, "INSERT INTO %s.record (donor_id, blood_type, action, status, date) VALUES(%d, \"%s\", \"donor\", \"approved\", NOW());", DATABASE_NAME, userId, type);

    closeConnection(connection);
}

void takeBlood(int recordId, int takerId) {
    MYSQL *connection = connectDatabase();
    char query[300];

    sprintf(query, "UPDATE %s.record SET taker_id = %d WHERE id = %d;", DATABASE_NAME, takerId, recordId);

    closeConnection(connection);
}

void setAnalisysResult(int recordId, char *status, char *type) {
    MYSQL *connection = connectDatabase();
    char query[300];
    
    sprintf(query, "UPDATE %s.record SET blood_type = \"%s\", status = \"%s\" WHERE id = %d;", DATABASE_NAME, type, status, recordId);

    closeConnection(connection);
}

void insertNewHistoryRecord(int id, char *phone_number, char *typeOfAction) {
    MYSQL *connection = connectDatabase();
    char query[300];

    if((isEqual(typeOfAction,"Donor") ||(isEqual(typeOfAction,"Recipient")))){
        sprintf(query, "INSERT INTO %s.history (id,phone_number,dateofaction,typeofaction) VALUES(%d,\"%s\",NOW(),\"%s\");", DATABASE_NAME,id,phone_number,typeOfAction);
        makeQuery(connection, query);
        printf("Insertion was successful\n");
    } else {
        printf("Invalid insertion parameters");
    }
    
    closeConnection(connection);
}

void deleteHistoryRecord( char *phone_number){
    MYSQL *connection = connectDatabase();
    char query[300];

        sprintf(query, "delete from %s.history where phone_number= \"%s\";", DATABASE_NAME, phone_number);
        makeQuery(connection, query);
        printf("Deletion was successful\n");
    
    closeConnection(connection);
}

Record* selectHistoryRecords(char *phone_number, Record array[]){
    MYSQL *connection = connectDatabase();
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

        sprintf(records[i].phone_number, "%s", row[1]);
        sprintf(records[i].date, "%s", row[2]);
        sprintf(records[i].action, "%s", row[3]);
        
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