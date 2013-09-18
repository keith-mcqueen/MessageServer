/* 
 * File:   PutHandler.cpp
 * Author: kmcqueen
 * 
 * Created on September 17, 2013, 12:06 PM
 */
#include "PutHandler.h"

#include <stdlib.h>
#include "Server.h"
#include "main.h"

PutHandler* PutHandler::instance() {
    static PutHandler* instance = new PutHandler();
    return instance;
}

PutHandler::~PutHandler() {
}

bool PutHandler::doHandleRequest(string request, ClientProxy* client) {
    // extract the recipient from the request
    int start = this->getRequestPrefix().length();
    int space = request.find(" ", start);
    if (string::npos == space) {
        return this->sendErrorResponse("Message recipient not found in request: " + request, client);
    }
    string recipient = request.substr(start, space - start);
    debug("\trecipient is: " + recipient);
    
    // extract the subject from the request
    start = space + 1;
    space = request.find(" ", start);
    if (string::npos == space) {
        return this->sendErrorResponse("Message subject not found in request: " + request, client);
    }
    string subject = request.substr(start, space - start);
    debug("\tsubject is: " + subject);
            
    // extract the message size from the request
    string length = request.substr(space + 1);
    if (length.empty()) {
        return this->sendErrorResponse("Message length not found in request: " + length, client);
    }
    debug("\tlength is: " + length);
    
    int len = atoi(length.c_str());
    
    // get the rest of the message (the message body) from the client
    string body = client->getRequestString(len);
    
    // create and store the message object
    Message* message = new Message(subject, body);
    Server::instance()->addMessage(recipient, message);
    
    // send the (OK) response
    return this->sendOKResponse(client);
}

string PutHandler::getRequestPrefix() {
    return "put ";
}

string PutHandler::getName() {
    return "PutHandler";
}
