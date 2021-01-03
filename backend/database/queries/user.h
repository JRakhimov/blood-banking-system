#ifndef SPECIALIST_QUERIES_H
#define SPECIALIST_QUERIES_H

#include "../connector.h"
#include "../../entities/user.h"

void insertNewUser(int id,char *phone_number, char *password,char *name, char *date, char *bloodType, char *validStatus, char *userStatus){
    
    MYSQL connection = connectDatabase();

    char query[300];

    sprintf(query, "INSERT INTO %s.dr_user (id,phone_number,password,name,dateofbirth,bloodtype,validstatus,userstatus) VALUES(%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\");",
    DATABASE_NAME, id,phone_number,password,name,date,bloodType,validStatus,userStatus);
   
    printf("%s\n",query);
    
    makeQuery(connection, query);

    printf("Insertion was successful\n");
    closeConnection(connection);
}

User selectUserByPhoneNumber(char *phone){

    MYSQL connection = connectDatabase();

    struct User user;

    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[100];

    sprintf(query, "SELECT * FROM %s.dr_user where phone_number = \"%s\";", DATABASE_NAME, phone);

    mysql_query(connection,query);

    res = mysql_store_result(connection);
    while(row  = mysql_fetch_row(res)){
        user.id = atoi(row[0]);
        user.phone_number = row[1];
        user.password = row[2];
        user.name = row[3];
        user.date = row[4];
        user.bloodType= row[5];
        user.validStatus=row[6];
        user.UserStatus=row[7];
    }
    mysql_free_result(res);
    closeConnection(connection);
    return user;
}

void deleteUserByPhoneNumber(char *phone){

    MYSQL connection = connectDatabase();

    char query[100];

    sprintf(query, "DELETE from %s.dr_user where phone_number = \"%s\";", DATABASE_NAME, phone); 
    makeQuery(connection, query);

    printf("Deletion was successful\n");
    closeConnection(connection);
}

void updateUser(char *phone_number, char *password,char *name, char *date, char *bloodType, char *validStatus, char *userStatus){

    MYSQL connection = connectDatabase();

    char query[300];

    sprintf(query, "UPDATE %s.dr_user SET password = \"%s\", name = \"%s\",dateofbirth= \"%s\", bloodtype = \"%s\",validstatus = \"%s\",userstatus=\"%s\" where phone_number = \"%s\";",
    DATABASE_NAME, password, name, date, bloodType, validStatus, userStatus, phone_number);

    makeQuery(connection, query);

    printf("Update was successful\n");
    closeConnection(connection);
}

void updateUserBloodType(char *phone_number,char *bloodType){

    MYSQL connection = connectDatabase();

    char query[100];

    sprintf(query, "UPDATE %s.dr_user SET bloodtype = \"%s\" where phone_number = \"%s\";", DATABASE_NAME, bloodType,phone_number);

    makeQuery(connection, query);

    printf("Update was successful\n");
    closeConnection(connection);

}

void updateUserValidStatus(char *phone_number,char *status){

    MYSQL connection = connectDatabase();
    char query[100];

    if((IsEqual(status,"Approved") ||(IsEqual(status,"Not Approved")))){
        sprintf(query, "UPDATE %s.dr_user SET validstatus = \"%s\" where phone_number = \"%s\";", DATABASE_NAME, status, phone_number);
 
        makeQuery(connection, query);

        printf("Update was successful\n");
    }
    else{
        printf("Invalid valid status parameter, try again\n");
    }
    
    closeConnection(connection);

}

void updateUserUserStatus(char *phone_number,char *status){

    MYSQL connection = connectDatabase();

    char query[100];

    if((IsEqual(status,"Donor") || (IsEqual(status,"Recipient")))){
        sprintf(query, "UPDATE %s.dr_user SET userstatus = \"%s\" where phone_number = \"%s\";", DATABASE_NAME, status, phone_number);

        makeQuery(connection, query);

        printf("Update was successful\n");
    }
    else{
        printf("Invalid user status parameter, try again\n");
    }
    
    closeConnection(connection);

}

int validUser( char *phone_number, char *password){

    MYSQL connection = connectDatabase();

    //variable definnition
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query1[100];
    char *DBphone_number;
    char *DBpassword; // in future will be used for password


    char *phoneNum = phone_number;
    char *userPassword = password;

    int phoneNumberStatus = 0;
    int passwordStatus = 0;
    int status = 0; // return 1 if true, 0 if false


    //Extracting name email(password) and validate with input
    sprintf(query, "SELECT phone_number,password FROM %s.dr_user", DATABASE_NAME);

    mysql_query(connection,query);

    res = mysql_store_result(connection);

    while(row  = mysql_fetch_row(res)){
        DBphone_number = row[0];
        DBpassword= row[1];

        if(IsEqual(DBphone_number,phoneNum)){
            phoneNumberStatus=1;
            if(IsEqual(DBpassword, userPassword)){
                passwordStatus=1;
                break;
            }
            else{
                passwordStatus=0;
            }
        }
        else{
            phoneNumberStatus=0;
        }
    }

    mysql_free_result(res);

    if(phoneNumberStatus == 0 || passwordStatus == 0){ 
        status = 0;
    }
    else{
        if (phoneNumberStatus == 1  && passwordStatus == 1 ){ 
            status = 1;
        }
    }
  
    closeConnection(connection);
    return status;
}

User* getAllUsers(){

    MYSQL connection = connectDatabase();

    struct User users[4096];
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *query = "SELECT * FROM %s.dr_user;", DATABASE_NAME);
    
    int i=0;

    mysql_query(connection, query);

    res = mysql_store_result(connection);
    while(row  = mysql_fetch_row(res)){
        users[i].id = atoi(row[0]);
        users[i].phoneNumber = row[1];
        users[i].password = row[2];
        users[i].name = row[3];
        users[i].date = row[4];
        users[i].bloodType = row[5];
        users[i].validStatus = row[6];
        users[i].userStatus = row[7];
        i++;
    }
    i = 0;
    mysql_free_result(res); // free result set
    closeConnection(connection); // close connection

    return users; //returning array of all users
}

/* 
DR_user* ShowAllUsers(DR_user people[]){

    for(int i=0;i<sizeof(users)/sizeof(DR_user);i++ ){
        users[i].id = 0;
    }

    GetAllDRUsers();

    for(int i=0;i<sizeof(users)/sizeof(DR_user);i++ ){
        people[i]=users[i];
    }
    return people;
}
*/


#endif