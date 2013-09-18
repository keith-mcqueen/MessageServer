/* 
 * File:   ClearHandler.cpp
 * Author: kmcqueen
 * 
 * Created on September 17, 2013, 7:15 PM
 */

#include "ResetHandler.h"
#include "Server.h"

ResetHandler* ResetHandler::instance() {
    static ResetHandler* instance = new ResetHandler();
    return instance;
}

ResetHandler::~ResetHandler() {
}

bool ResetHandler::doHandleRequest(string request, ClientProxy* client) {
    Server::instance()->reset();
    
    return RequestHandler::sendOKResponse(client);
}

string ResetHandler::getRequestPrefix() {
    return "reset";
}

string ResetHandler::getName() {
    return "ClearHandler";
}

