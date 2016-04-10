/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   eMeterLib.cpp
 * Author: Margarita E. Della Sera
 * 
 * Created on April 5, 2016, 11:28 PM
 */

#include "eMeterLib.h"
/**
 * Constructor
 */
eMeterLib::eMeterLib(){    
}

/**
 * Copy constructor
 */

eMeterLib::eMeterLib(const eMeterLib& orig) {
}

/**
 * Destructor
 */

eMeterLib::~eMeterLib() {
}

/**
 * This is an overriden function. It prepares the statement with the required 
 * table parameters prior to population of the database.
 */

void eMeterLib::prepareInsertStatement(){
     
    sql::SQLString insertStatement = "INSERT INTO " + m_dbCommonVar.tableName + 
               "(id, date, client, app_name, average_power, irms, vrms, "
               "apparent_power, temperature_c, i_peak, v_peak, trig_reac_power,"
               " power_factor, harmonic_power, fund_active_power,"
               " fund_react_power, avg_react_power)"
               "  VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    
    m_pPStmt = m_pCon->prepareStatement(insertStatement);
    
}

/**
 * This function reads line of data from the given string and stores the data
 * in local variables.
 */

void eMeterLib::readStream(std::istream& input, ReadStreamPopulateDB& b) {
     
  eMeterLib* p = (eMeterLib*)&b;
    
  std::string date, time, dateTime;

  //Clients parameters
  std::getline(input, b.m_dbCommonVar._clientParms.clientName, ' ');
  std::getline(input, b.m_dbCommonVar._clientParms.appName, ' ');
  std::getline(input, b.m_dbCommonVar._clientParms.appNo, ' ');
  
  //Date and time
  std::getline(input, m_dbCommonVar._dateTime.date, ' ');
  std::getline(input, m_dbCommonVar._dateTime.time, 'T');
  
  // Electrical Parameters
  std::getline(input, p->_electricParams.averagePower, ' ');
  std::getline(input, p->_electricParams.iRms, ' ');
  std::getline(input, p->_electricParams.vRms, ' ');
  std::getline(input, p->_electricParams.apparentPower, ' ');
  std::getline(input, p->_electricParams.temperatureC, ' ');
  std::getline(input, p->_electricParams.iPeak, ' ');
  std::getline(input, p->_electricParams.vPeak, ' ');
  std::getline(input, p->_electricParams.trigReacPower, ' ');
  std::getline(input, p->_electricParams.powerFactor, ' ');
  std::getline(input, p->_electricParams.harmonicPower, ' ');
  std::getline(input, p->_electricParams.fundActivePower, ' ');
  std::getline(input, p->_electricParams.fundReactPower, ' ');
  std::getline(input, p->_electricParams.avgReactPower, '\n');
  
  m_dbCommonVar._dateTime.dateTime = m_dbCommonVar._dateTime.date + " " +
                                     m_dbCommonVar._dateTime.time;
       
}

/**
 * This function writes data stored in local variables into the given table on
 * the give database.
 *  
 */

void eMeterLib::writeDB(ReadStreamPopulateDB* b){   
  
  eMeterLib* p = dynamic_cast<eMeterLib*>(b);
 
  b->m_pPStmt->setInt(1, b->m_dbCommonVar.index);
  b->m_pPStmt->setString(2, m_dbCommonVar._dateTime.dateTime);
  b->m_pPStmt->setString(3, b->m_dbCommonVar._clientParms.clientName);
  b->m_pPStmt->setString(4, b->m_dbCommonVar._clientParms.appName);
 // b->m_pPStmt->setString(4, b->m_dbCommonVar._clientParms.appNo);
  b->m_pPStmt->setString(5, p->_electricParams.averagePower);
  b->m_pPStmt->setString(6, p->_electricParams.iRms);
  b->m_pPStmt->setString(7, p->_electricParams.vRms);
  b->m_pPStmt->setString(8, p->_electricParams.apparentPower);
  b->m_pPStmt->setString(9, p->_electricParams.temperatureC);
  b->m_pPStmt->setString(10, p->_electricParams.iPeak);
  b->m_pPStmt->setString(11, p->_electricParams.vPeak);
  b->m_pPStmt->setString(12, p->_electricParams.trigReacPower);
  b->m_pPStmt->setString(13, p->_electricParams.powerFactor);
  b->m_pPStmt->setString(14, p->_electricParams.harmonicPower);
  b->m_pPStmt->setString(15, p->_electricParams.fundActivePower);
  b->m_pPStmt->setString(16, p->_electricParams.fundReactPower);
  b->m_pPStmt->setString(17, p->_electricParams.avgReactPower);

  b->m_pPStmt->executeUpdate();

}



