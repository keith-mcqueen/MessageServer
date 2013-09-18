/* 
 * File:   Message.cpp
 * Author: kmcqueen
 * 
 * Created on September 17, 2013, 11:39 AM
 */
#include "Message.h"

Message::Message(string subject, string body) {
    this->subject = subject;
    this->body = body;
}

Message::~Message() {
}

string Message::getSubject() {
    return this->subject;
}

string Message::getBody() {
    return this->body;
}