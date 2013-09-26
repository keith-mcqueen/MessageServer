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

void ListResponse::addMessages(vector<Message*> messages) {
    vector<Message*> copied(messages);
    this->messages = copied;
}

string ListResponse::getHeader() {
    stringstream ss;
    
    ss << Response::getHeader() << " " << this->messages.size();
    
    return ss.str();
}

string ListResponse::getBody() {
    stringstream ss;
    
    int size = this->messages.size();
    for (int i = 0; i < size; i++) {
        ss << i+1 << " " << this->messages.at(i)->getSubject() << endl;
}
    
    return ss.str();
}