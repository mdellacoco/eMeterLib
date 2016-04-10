/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReadStreamPopulateDB.h
 * Author: Margarita E. Della Sera
 *
 * Created on April 5, 2016, 11:31 PM
 */

#ifndef READSTREAMPOPULATEDB_H
#define READSTREAMPOPULATEDB_H

#include <string>
#include <iostream>
#include <stdio.h>

#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"

/**
 Clients parameters relates to the remote clients credentials:
 * the client name
 * the application the client is using to send data
 * the application number, or pid .
 */

typedef struct {
    std::string clientName = "";
    std::string appName = "";
    std::string appNo = "";
}clientParams;

/**
 * The date time structure used.
 */

typedef struct {
    std::string date = "";  //2016-04-07
    std::string time = "";  // 15:49:00
    std::string dateTime = ""; //2016 04 07 15:49:00
}dateTime;

/**
 * Common database variables found in this type of applications.
 */

typedef struct{
   int          index = 0;
   std::string  tableName = "";
   clientParams _clientParms;
   dateTime     _dateTime;
}dBCommonVar;

/**
 * This is the base class used to read data from a file and write the read data 
 * to a database.
 * The reading a stream and writing to database are done by overriding the
 *  >> and << operators.
 * The reading stream is performed by calling the virtual functions readStream.
 * The writing the read data to the database is done by calling the writeDB method.
 */

class ReadStreamPopulateDB {
public:
    ReadStreamPopulateDB();
    ReadStreamPopulateDB(const ReadStreamPopulateDB& orig);
    virtual ~ReadStreamPopulateDB();
    
    void setIndex(int index){m_dbCommonVar.index = index;}
    int getIndex(){return m_dbCommonVar.index;}
    void setTableName(std::string tableName){m_dbCommonVar.tableName = tableName;}
    std::string getDateTime() {return m_dbCommonVar._dateTime.dateTime;}
    void setDateTime(std::string dateTime){m_dbCommonVar._dateTime.dateTime = dateTime;}
    
    void setDBConnection(sql::Connection* pCon){m_pCon = pCon;}
    void setDBPreparedStatement(sql::PreparedStatement* pPStmt){m_pPStmt = pPStmt;}
    
    friend std::istream& operator>> (std::istream& in, ReadStreamPopulateDB& b) {  //done like this because friend class cannot be virtual
        b.readStream(in, b);
        return in;
    } 
    friend std::ostream& operator<< (std::ostream& out, ReadStreamPopulateDB* b) {
      return out;
    }
    virtual void prepareInsertStatement() {};//= 0; 
    virtual void writeDB(ReadStreamPopulateDB* b) {};
    
protected:
     virtual void readStream(std::istream& input, ReadStreamPopulateDB& b){}
    
public:
    
    sql::PreparedStatement*     m_pPStmt;
    dBCommonVar                 m_dbCommonVar;
    
protected:
    
    sql::Connection*            m_pCon;

};
/*The type of the class factory*/
typedef ReadStreamPopulateDB* create_t();
typedef void destroy_t(ReadStreamPopulateDB*);


#endif /* READSTREAMPOPULATEDB_H */

