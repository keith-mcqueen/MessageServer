/* 
 * File:   Server.cpp
 * Author: kmcqueen
 * 
 * Created on September 16, 2013, 4:28 PM
 */
#include "Server.h"

#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "RequestHandler.h"
#include "DefaultHandler.h"
#include "ThreadPool.h"
#include "ClientManager.h"
#include "MessageStore.h"

Server::~Server() {
}

Server* Server::instance() {
    static Server* instance = new Server();
    return instance;
}

void Server::serve(int port, int maxClients, int numThreads) {
    // set up the server socket
    debug("Server::serve -- initializing listening socket");
    int serverId = this->initSocket(port);
    
    // set up the client manager
    debug("Server::serve -- setting up client manager");
    ClientManager* mgr = new ClientManager(maxClients);
    
    // set up the thread pool
    debug("Server::serve -- setting up thread pool");
    ThreadPool* pool = new ThreadPool(numThreads);
    pool->run(&run, mgr);
    
    // set up client
    int clientId;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

      // accept clients
    debug("Server::serve -- waiting for client");
    while ((clientId = accept(serverId, (struct sockaddr *)&client_addr, &clientlen)) > 0) {
        ClientProxy* client = new ClientProxy(clientId);
        debug("Server::serve -- adding client to queue");
        mgr->pushClient(client);
    }
    
    // close the server socket
    debug("Server::serve -- closing server socket");
    close(serverId);

    // clean up some memory (even though this will likely not ever be reached)
    delete mgr;
    delete pool;
}

int Server::initSocket(int port) {
    // set up listening socket
    struct sockaddr_in server_addr;

    // set up socket address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // create socket
    int serverId = socket(PF_INET,SOCK_STREAM,0);
    if (!serverId) {
        perror("socket");
        exit(-1);
    }

    // set socket to immediately reuse port when the application closes
    int reuse = 1;
    if (setsockopt(serverId, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt");
        exit(-1);
    }

    // call bind to associate the socket with our local address and
    // port
    if (bind(serverId, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(-1);
    }

      // convert the socket to listen for incoming connections
    if (listen(serverId, SOMAXCONN) < 0) {
        perror("listen");
        exit(-1);       
    }
    
    return serverId;
}

void Server::service(ClientProxy* client) {
    while (true) {
        debug("Server::service -- waiting for a request from the client");
        string request = client->getRequestLine();
        if (request.empty()) {
            break;
        }
        
        // get the request handler for the request
        RequestHandler* handler = this->getRequestHandler(request);
        
        // handle the request
        if (not handler->handleRequest(request, client)) {
            break;
        }
    }
    
    // clean up the client
    debug("Server::service -- terminating client connection");
    client->terminate();
    delete client;
}

RequestHandler* Server::getRequestHandler(string request) {
    return RequestHandler::getRequestHandler(request);
}

void Server::addMessage(string recipient, Message* message) {
    debug("Server::addMessage -- adding a message to the store");
    this->store.addMessage(recipient, message);
}

vector<Message*> Server::getMessages(string recipient) {
    debug("Server::getMessages -- getting messages from the store");
    return this->store.getMessages(recipient);
}

void Server::reset() {
    debug("Server::reset -- clearing the message store");
    this->store.clear();
}

void* Server::run(void* context) {
    ClientManager* mgr = (ClientManager*) context;
    
    while (true) {
        // get a client to be serviced from the server
        debug("Server::run -- getting a client from the queue");
        ClientProxy* client = mgr->popClient();

        // service the client
        debug("Server::run -- servicing the client");
        Server::instance()->service(client);
    }
}
