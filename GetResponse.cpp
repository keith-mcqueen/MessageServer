/* 
 * File:   GetResponse.cpp
 * Author: kmcqueen
 * 
 * Created on September 16, 2013, 10:48 PM
 */
#include "GetResponse.h"

#include <sstream>

GetResponse::GetResponse(string subject, string message) : Response("message") {
    this->subject = subject;
    this->message = message;
}

GetResponse::~GetResponse() {
}

string GetResponse::getHeader() {
    stringstream ss;
    
    ss << Response::getHeader() << " " << this->subject << " " << this->message.length() << endl;
    
    return ss.str();
}

string GetResponse::getBody() {
    return this->message;
}