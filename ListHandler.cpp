/* 
 * File:   ListHandler.cpp
 * Author: kmcqueen
 * 
 * Created on September 17, 2013, 12:51 PM
 */
#include "ListHandler.h"

#include <vector>
#include "Server.h"
#include "Message.h"
#include "ListResponse.h"
#include "main.h"

ListHandler* ListHandler::instance() {
    static ListHandler* instance = new ListHandler();
    return instance;
}

ListHandler::~ListHandler() {
}

bool ListHandler::doHandleRequest(string request, ClientProxy* client) {
    // extract the recipient from the request
    int start = this->getRequestPrefix().length();
    string recipient = request.substr(start);
    if (recipient.empty()) {
        return this->sendErrorResponse("Message recipient not found in request: " + request, client);
    }
    debug("\trecipient is: " + recipient);
    
    // get the message(s) for the recipient
    vector<Message*> messages = Server::instance()->getMessages(recipient);
    
    // prepare the response message
    ListResponse* response = new ListResponse();
    response->addMessages(messages);
    
    // send the response
    bool success = client->sendResponse(response);
    delete response;
    
    return success;
}

string ListHandler::getRequestPrefix() {
    return "list ";
}

string ListHandler::getName() {
    return "ListHandler";
}
