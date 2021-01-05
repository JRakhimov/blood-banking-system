#ifndef ADMIN_QUERIES_H
#define ADMIN_QUERIES_H

#include "../connector.h"
#include "../../../shared/entities/record.h"
#include "../../shared/entities/user.h"

// Get only can be taken blood
// SELECT * FROM os.record WHERE taker_id IS NULL AND action = "donor" AND status = "approved" LIMIT 1;

// Get history of bloods for user by phone
// SELECT * FROM os.record WHERE donor_id = (SELECT id FROM os.dr_user WHERE phone_number = "+998935555556") OR taker_id = (SELECT id FROM os.dr_user WHERE phone_number = "+998935555556");

// Get bloods to analyze
// SELECT * FROM os.record WHERE action = "analysis" AND status = "pending" AND taker_id IS NULL;

// Take analyses
// INSERT INTO os.record (donor_id, action, status, date) VALUES((SELECT id from os.dr_user where phone_number = "+998935555556"), "analysis", "pending", NOW());

// Donate blood
// INSERT INTO os.record (donor_id, blood_type, action, status, date) VALUES(7, "A+", "donor", "approved", NOW());

// Take blood (set taker)
// UPDATE os.record SET taker_id = 5 WHERE id = 2;

// Set analyze result
// UPDATE os.record SET blood_type = "B+", status = "approved" WHERE id = 2;

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