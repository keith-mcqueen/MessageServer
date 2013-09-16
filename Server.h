/* 
 * File:   Server.h
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 4:28 PM
 */

#ifndef SERVER_H
#define	SERVER_H

class Server {
public:
    Server(int port);
    Server(const Server& orig);
    virtual ~Server();

private:
    void init(int port);
    void serve();
    
    int serverId;
};

#endif	/* SERVER_H */

