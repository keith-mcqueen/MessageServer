/* 
 * File:   Response.cpp
 * Author: kmcqueen
 * 
 * Created on September 16, 2013, 8:44 PM
 */
#include "Response.h"

#include <sstream>

Response::Response(string type) {
    this->type = type;
}

Response::~Response() {
}

string Response::toString() {
    stringstream ss;
    
    ss << this->getHeader() << endl;
    ss << this->getBody();
    
    return ss.str();
}

string Response::getHeader() {
    return this->type;
}

string Response::getBody() {
    return "";
}