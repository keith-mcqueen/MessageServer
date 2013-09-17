/* 
 * File:   RequestHandler.cpp
 * Author: kmcqueen
 * 
 * Created on September 16, 2013, 5:30 PM
 */

#include "RequestHandler.h"
#include "ErrorResponse.h"
#include "main.h"

RequestHandler::RequestHandler() {
}

RequestHandler::~RequestHandler() {
}

list<RequestHandler*> RequestHandler::getHandlers() {
    list<RequestHandler*> handlers;
    
    return handlers;
}

bool RequestHandler::canHandle(string request) {
    int found = request.find(this->getRequestPrefix());
    if (found == string::npos) {
        return false;
    }
    
    return 0 == found;
}

bool RequestHandler::handleRequest(string request, ClientProxy* client) {
    debug(this->getName() + " is handling request: " + request);
    if (not this->canHandle(request)) {
        ErrorResponse* response = new ErrorResponse("Unexpected request: " + request);
        
        bool success = client->sendResponse(response);
        delete response;
        
        return success;
    }
    
    return this->doHandleRequest(request, client);
}