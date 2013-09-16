/* 
 * File:   Server.cpp
 * Author: kmcqueen
 * 
 * Created on September 16, 2013, 4:28 PM
 */
#include "Server.h"

#include <arpa/inet.h>

Server::Server(int port) {
    this->init(port);
    this->serve();
}

Server::Server(const Server& orig) {
}

Server::~Server() {
}

void Server::init(int port) {
    struct sockaddr_in server_addr;

    // set up socket address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // create socket
    this->serverId = socket(PF_INET,SOCK_STREAM,0);
    if (!this->serverId) {
        perror("socket");
        exit(-1);
    }

    // set socket to immediately reuse port when the application closes
    int reuse = 1;
    if (setsockopt(this->serverId, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt");
        exit(-1);
    }

    // call bind to associate the socket with our local address and
    // port
    if (bind(this->serverId,(const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(-1);
    }

      // convert the socket to listen for incoming connections
    if (listen(this->serverId, SOMAXCONN) < 0) {
        perror("listen");
        exit(-1);       
    }
}

void Server::serve() {
    // setup client
    int clientId;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

      // accept clients
    while ((clientId = accept(this->serverId, (struct sockaddr *)&client_addr, &clientlen)) > 0) {
        handle(clientId);
        close(clientId);
    }
    
    close(this->serverId);
}