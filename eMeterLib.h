/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   eMeterLib.h
 * Author: Margarita E. Della Sera
 *
 * Created on April 5, 2016, 11:28 PM
 */

#ifndef EMETERLIB_H
#define EMETERLIB_H

#include "ReadStreamPopulateDB.h"
#include <stdio.h>
/*
 * Definition of the electrical parameters.
 */
typedef struct {
    
 std::string averagePower    = "";
 std::string iRms            = "";
 std::string vRms            = "";
 std::string apparentPower   = "";
 std::string temperatureC    = "";
 std::string iPeak           = "";
 std::string vPeak           = "";
 std::string trigReacPower   = "";
 std::string powerFactor     = "";
 std::string harmonicPower   = "";
 std::string fundActivePower = "";
 std::string fundReactPower  = "";
 std::string avgReactPower   = "";  
}electricParams;

/**
 * This class inherates from ReadStreamPopulateDB. It defines the data that is to
 * be read from the the given stream and write to the given database.
 */

class eMeterLib : public ReadStreamPopulateDB {
public:
    eMeterLib();
    eMeterLib(const eMeterLib& orig);
    virtual ~eMeterLib();
    
    virtual void prepareInsertStatement();
    virtual void writeDB(ReadStreamPopulateDB* b); 
    
protected:
 virtual void readStream(std::istream& input, ReadStreamPopulateDB& b);   
 
 
private:
    electricParams _electricParams;

};

extern "C" ReadStreamPopulateDB* create(){
    return new eMeterLib();
}

extern "C" void destroy(ReadStreamPopulateDB* p){
    delete p;
}

#endif /* EMETERLIB_H */

