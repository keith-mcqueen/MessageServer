/* 
 * File:   ClientManager.h
 * Author: keith
 *
 * Created on September 23, 2013, 9:20 PM
 */

#ifndef CLIENTMANAGER_H
#define	CLIENTMANAGER_H

#include <queue>
#include <semaphore.h>
#include "ClientProxy.h"

using namespace std;

class ClientManager {
public:
    ClientManager(int maxClients);
    virtual ~ClientManager();
    void pushClient(ClientProxy* client);
    ClientProxy* popClient();

private:
    int maxClients;
    queue<ClientProxy*> clients;
    
    sem_t lock;
    sem_t open_slot;
    sem_t client_added;
};

#endif	/* CLIENTMANAGER_H */

