/* 
 * File:   RequestHandler.cpp
 * Author: kmcqueen
 * 
 * Created on September 16, 2013, 5:30 PM
 */

#include "RequestHandler.h"

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

void RequestHandler::handleRequest(string request, ClientProxy* client) {
    
}