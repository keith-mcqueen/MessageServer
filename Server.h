/* 
 * File:   Server.h
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 4:28 PM
 */

#ifndef SERVER_H
#define	SERVER_H

#include <vector>
#include <pthread.h>
#include "ClientProxy.h"
#include "RequestHandler.h"
#include "Message.h"
#include "MessageStore.h"

using namespace std;

class Server {
public:
    virtual ~Server();
    void serve(int port, int maxClients, int numThreads);
    void addMessage(string recipient, Message* message);
    vector<Message*> getMessages(string recipient);
    void reset();
    
    static Server* instance();

private:
    int initSocket(int port);
    void service(ClientProxy* client);
    RequestHandler* getRequestHandler(string request);
    static void* run(void* context);
    
    MessageStore store;
    list<RequestHandler*> handlers;
};

#endif	/* SERVER_H */

