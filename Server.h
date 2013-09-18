/* 
 * File:   Server.h
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 4:28 PM
 */

#ifndef SERVER_H
#define	SERVER_H

#include <vector>
#include <map>
#include "ClientProxy.h"
#include "RequestHandler.h"
#include "Message.h"

using namespace std;

class Server {
public:
    virtual ~Server();
    void serve(int port);
    void addMessage(string recipient, Message* message);
    vector<Message*> getMessages(string recipient);
    void reset();
    
    static Server* instance();

private:
    void service(ClientProxy* client);
    RequestHandler* getRequestHandler(string request);
    multimap<string, Message*> messagesByRecipient;
};

#endif	/* SERVER_H */

