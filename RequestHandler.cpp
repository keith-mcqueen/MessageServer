/* 
 * File:   RequestHandler.cpp
 * Author: kmcqueen
 * 
 * Created on September 16, 2013, 5:30 PM
 */

#include "RequestHandler.h"
#include "ErrorResponse.h"
#include "main.h"
#include "PutHandler.h"
#include "ListHandler.h"
#include "GetHandler.h"
#include "ResetHandler.h"

RequestHandler::~RequestHandler() {
}

list<RequestHandler*> RequestHandler::getHandlers() {
    list<RequestHandler*> handlers;
    
    // add the "put" request handler
    handlers.push_back(PutHandler::instance());
    
    // add the "list" request handler
    handlers.push_back(ListHandler::instance());
    
    // add the "get" request handler
    handlers.push_back(GetHandler::instance());
    
    // add the "reset" request handler
    handlers.push_back(ResetHandler::instance());
    
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
        return this->sendErrorResponse("Unexpected request: " + request, client);
    }
    
    return this->doHandleRequest(request, client);
}

bool RequestHandler::sendErrorResponse(string error, ClientProxy* client) {
    ErrorResponse* response = new ErrorResponse(error);
    
    bool success = client->sendResponse(response);
    delete response;
    
    return success;
}

bool RequestHandler::sendOKResponse(ClientProxy* client) {
    Response* response = new Response("OK");
    
    bool success = client->sendResponse(response);
    delete response;
    
    return success;
}