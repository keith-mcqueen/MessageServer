/* 
 * File:   Server.h
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 4:28 PM
 */

#ifndef SERVER_H
#define	SERVER_H

#include "ClientProxy.h"

class Server {
public:
    Server(int port);
    virtual ~Server();

private:
    void init(int port);
    void serve();
    void service(ClientProxy* client);
    
    int serverId;
};

#endif	/* SERVER_H */

