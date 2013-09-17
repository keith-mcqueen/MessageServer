/* 
 * File:   Server.h
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 4:28 PM
 */

#ifndef SERVER_H
#define	SERVER_H

#include "ClientProxy.h"
#include "RequestHandler.h"

class Server {
public:
    virtual ~Server();
    void serve(int port);
    
    static Server* instance();

private:
    void service(ClientProxy* client);
    RequestHandler* getRequestHandler(string request);
};

#endif	/* SERVER_H */

