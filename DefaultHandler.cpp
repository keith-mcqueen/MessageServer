/* 
 * File:   DefaultHandler.cpp
 * Author: kmcqueen
 * 
 * Created on September 17, 2013, 12:07 AM
 */

#include "DefaultHandler.h"
#include "ErrorResponse.h"

DefaultHandler::~DefaultHandler() {
}

DefaultHandler* DefaultHandler::instance() {
    static DefaultHandler* instance = new DefaultHandler();
    return instance;
}

bool DefaultHandler::canHandle(string request) {
    return true;
}

bool DefaultHandler::doHandleRequest(string request, ClientProxy* client) {
    ErrorResponse* response = new ErrorResponse("Unrecognized request: " + request);
    
    bool success = client->sendResponse(response);
    delete response;
    
    return success;
}

string DefaultHandler::getRequestPrefix() {
    return "default";
}

string DefaultHandler::getName() {
    return "DefaultHandler";
}