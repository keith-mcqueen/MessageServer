/* 
 * File:   ClientManager.cpp
 * Author: keith
 * 
 * Created on September 23, 2013, 9:20 PM
 */

#include "ClientManager.h"

ClientManager::ClientManager(int maxClients) {
    sem_init(&this->lock, 0, 1);
    sem_init(&this->open_slot, 0, maxClients);
    sem_init(&this->client_added, 0, 0);
}

ClientManager::~ClientManager() {
}

void ClientManager::pushClient(ClientProxy* client) {
    // wait for an open slot
    sem_wait(&this->open_slot);
    
    ///// CRITICAL SECTION /////
    // lock -> add the client -> unlock
    sem_wait(&this->lock);    
    this->clients.push(client);  
    sem_post(&this->lock);
    
    // signal that a client was added
    sem_post(&this->client_added);
}

ClientProxy* ClientManager::popClient() {
    // wait for an added client
    sem_wait(&this->client_added);
    
    ///// CRITICAL SECTION /////
    // lock -> get and remove a client -> unlock
    sem_wait(&this->lock);
    ClientProxy* client = this->clients.front();
    this->clients.pop();
    sem_post(&this->lock);
    
    // signal an open slot
    sem_post(&this->open_slot);
    
    return client;
}
