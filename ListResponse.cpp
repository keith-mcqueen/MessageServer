/* 
 * File:   ListResponse.cpp
 * Author: kmcqueen
 * 
 * Created on September 16, 2013, 10:04 PM
 */
#include "ListResponse.h"

#include <sstream>

ListResponse::ListResponse() : Response("list") {
}

ListResponse::~ListResponse() {
}

void ListResponse::addSubject(string subject) {
    this->subjects.push_back(subject);
}

string ListResponse::getHeader() {
    stringstream ss;
    
    ss << Response::getHeader() << " " << this->subjects.size() << endl;
    
    return ss.str();
}

string ListResponse::getBody() {
    stringstream ss;
    
    for (int i = 0; i < this->subjects.size(); i++) {
        ss << i+1 << " " << this->subjects.at(i) << endl;
    }
    
    return ss.str();
}