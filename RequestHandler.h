/* 
 * File:   RequestHandler.h
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 5:30 PM
 */
#ifndef REQUESTHANDLER_H
#define	REQUESTHANDLER_H

#include <string>
#include <list>
#include <map>
#include "ClientProxy.h"

using namespace std;

class RequestHandler {
public:
    virtual ~RequestHandler();
    virtual bool canHandle(string request);
    virtual bool handleRequest(string request, ClientProxy* client);
    
    static RequestHandler* getRequestHandler(string request);
protected:
    virtual string getRequestPrefix() = 0;
    virtual string getName() = 0;
    virtual bool doHandleRequest(string request, ClientProxy* client) = 0;
    bool sendErrorResponse(string error, ClientProxy* client);
    bool sendOKResponse(ClientProxy* client);
    
private:
    typedef map<string, RequestHandler*> HandlerMap;
    static HandlerMap createHandlerMap();
    static HandlerMap handlerMap;
};

#endif	/* REQUESTHANDLER_H */

