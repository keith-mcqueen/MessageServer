/* 
 * File:   MessageStore.h
 * Author: keith
 *
 * Created on September 23, 2013, 10:29 PM
 */

#ifndef MESSAGESTORE_H
#define	MESSAGESTORE_H

#include <string>
#include <semaphore.h>
#include <map>
#include <vector>
#include "Message.h"

class MessageStore {
public:
    MessageStore();
    virtual ~MessageStore();
    void addMessage(string recipient, Message* message);
    vector<Message*> getMessages(string recipient);
    void clear();

private:
    void lock();
    void unlock();
    
    multimap<string, Message*> messagesByRecipient;
    sem_t lock_;
};

#endif	/* MESSAGESTORE_H */

