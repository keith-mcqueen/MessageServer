/* 
 * File:   ClientProxy.h
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 5:01 PM
 */

#ifndef CLIENTPROXY_H
#define	CLIENTPROXY_H

#include <string>
#include "Response.h"

using namespace std;

class ClientProxy {
public:
    ClientProxy(int clientId);
    virtual ~ClientProxy();
    string getRequestLine();
    string getRequestString(int length);
    bool sendResponse(Response* response);

private:
    int clientId;
    string leftOvers;
    char* buf;
    int buflen;
};

#endif	/* CLIENTPROXY_H */

