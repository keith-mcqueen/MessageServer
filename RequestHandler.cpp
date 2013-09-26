/* 
 * File:   RequestHandler.cpp
 * Author: kmcqueen
 * 
 * Created on September 16, 2013, 5:30 PM
 */

#include <map>

#include "RequestHandler.h"
#include "ErrorResponse.h"
#include "main.h"
#include "PutHandler.h"
#include "ListHandler.h"
#include "GetHandler.h"
#include "ResetHandler.h"
#include "DefaultHandler.h"

RequestHandler::~RequestHandler() {
}

RequestHandler* RequestHandler::getRequestHandler(string request) {
    int space = request.find(" ");
    
    // if the space was not found, see if there is a handler for the whole 
    //  string (like the "reset" handler)
    string prefix;
    if (string::npos == space) {
        prefix = request;
    } else {
        prefix = request.substr(0, space + 1);
    }
    
    map<string, RequestHandler*>::iterator found = 
            RequestHandler::handlerMap.find(prefix);
    if (found == RequestHandler::handlerMap.end()) {
        return DefaultHandler::instance();
    }
    
    return (*found).second;
}

RequestHandler::HandlerMap RequestHandler::createHandlerMap() {
    HandlerMap handlers;
    
    // put handler
    RequestHandler* handler = PutHandler::instance();
    handlers[handler->getRequestPrefix()] = handler;
    
    // list handler
    handler = ListHandler::instance();
    handlers[handler->getRequestPrefix()] = handler;
    
    // get handler
    handler = GetHandler::instance();
    handlers[handler->getRequestPrefix()] = handler;

    // reset handler
    handler = ResetHandler::instance();
    handlers[handler->getRequestPrefix()] = handler;
        
    return handlers;
}

RequestHandler::HandlerMap RequestHandler::handlerMap(RequestHandler::createHandlerMap());

bool RequestHandler::canHandle(string request) {
    int found = request.find(this->getRequestPrefix());
    if (found == string::npos) {
        return false;
    }
    
    return 0 == found;
}

bool RequestHandler::handleRequest(string request, ClientProxy* client) {
    debug(this->getName() + " is handling request: " + request);
    
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