/* 
 * File:   GetHandler.cpp
 * Author: kmcqueen
 * 
 * Created on September 17, 2013, 1:04 PM
 */
#include "GetHandler.h"

#include <stdlib.h>
#include "Server.h"
#include "GetResponse.h"
#include "main.h"

GetHandler* GetHandler::instance() {
    static GetHandler* instance = new GetHandler();
    return instance;
}

GetHandler::~GetHandler() {
}

bool GetHandler::doHandleRequest(string request, ClientProxy* client) {
    // extract the recipient
    int start = this->getRequestPrefix().length();
    int space = request.find(" ", start);
    if (string::npos == space) {
        return this->sendErrorResponse("Message recipient not found in request: " + request, client);
    }
    string recipient = request.substr(start, space - start);
    debug("\trecipient is: " + recipient);
    
    // extract the message number
    string msgNum = request.substr(space + 1);
    if (msgNum.empty()) {
        return this->sendErrorResponse("Message length not found in request: " + msgNum, client);
    }
    debug("\tmessage number is: " + msgNum);
    
    int idx = atoi(msgNum.c_str());
    
    // get the message from the server
    vector<Message*> messages = Server::instance()->getMessages(recipient);
    Message* msg = messages.at(idx - 1);
    
    // prepare the response
    GetResponse* response = new GetResponse(msg->getSubject(), msg->getBody());
    
    // send the response
    bool success = client->sendResponse(response);
    delete response;
    
    return success;
}

string GetHandler::getRequestPrefix() {
    return "get ";
}

string GetHandler::getName() {
    return "GetHandler";
}
