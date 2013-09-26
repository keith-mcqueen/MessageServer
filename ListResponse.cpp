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

void ListResponse::setMessageCount(int count) {
    this->messageCount = count;
}

void ListResponse::setMessageList(string messageList) {
    this->messageList = messageList;
}

string ListResponse::getHeader() {
    stringstream ss;
    
    ss << Response::getHeader() << " " << this->messageCount;
    
    return ss.str();
}

string ListResponse::getBody() {
    return this->messageList;
}