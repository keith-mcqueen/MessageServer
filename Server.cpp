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

Server::~Server() {
}

Server* Server::instance() {
    static Server* instance = new Server();
    return instance;
}

void Server::serve(int port) {
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
    if (bind(serverId,(const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(-1);
    }

      // convert the socket to listen for incoming connections
    if (listen(serverId, SOMAXCONN) < 0) {
        perror("listen");
        exit(-1);       
    }
    
    // setup client
    int clientId;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

      // accept clients
    while ((clientId = accept(serverId, (struct sockaddr *)&client_addr, &clientlen)) > 0) {
        service(new ClientProxy(clientId));
        close(clientId);
    }
    
    close(serverId);
}

void Server::service(ClientProxy* client) {
    debug("Server::handle -- servicing client");
    
    string request;
    while (!(request = client->getRequestLine()).empty()) {
        // get the request handler for the request
        
        // handle the request
        
        // send the response to the client
    }
}

RequestHandler* Server::getRequestHandler(string request) {
    debug("Server::getRequestHandler -- getting request handler for request: " + request);
    
    list<RequestHandler*> handlers = RequestHandler::getHandlers();
    for (list<RequestHandler*>::iterator it = handlers.begin();
            it != handlers.end();
            ++it) {
        RequestHandler* handler = *it;
        if (handler->canHandle(request)) {
            return handler;
        }
    }
    
    debug("Server::getRequestHandler -- no request handler found, returning default handler");
    return DefaultHandler::instance();
}