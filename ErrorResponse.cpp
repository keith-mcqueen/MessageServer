/* 
 * File:   ErrorResponse.cpp
 * Author: kmcqueen
 * 
 * Created on September 16, 2013, 9:51 PM
 */
#include "ErrorResponse.h"

#include <sstream>

ErrorResponse::ErrorResponse(string description) : Response("error") {
    this->description = description;
}

ErrorResponse::~ErrorResponse() {
}

string ErrorResponse::getHeader() {
    stringstream ss;
    
    ss << Response::getHeader() << " " << this->description << endl;
    
    return ss.str();
}