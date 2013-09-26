/* 
 * File:   MessageStore.cpp
 * Author: keith
 * 
 * Created on September 23, 2013, 10:29 PM
 */

#include <sstream>

#include "MessageStore.h"

MessageStore::MessageStore() {
    sem_init(&this->lock_, 0, 1);
}

MessageStore::~MessageStore() {
}

void MessageStore::addMessage(string recipient, Message* message) {
    this->lock();
    
    // add the message to the recipient's messages
    vector<Message*> messages = this->messagesByRecipient[recipient];
    messages.push_back(message);
    this->messagesByRecipient[recipient] = messages;

    this->unlock();
}

vector<Message*> MessageStore::getMessages(string recipient) {
    this->lock();
    
    vector<Message*> messages = this->messagesByRecipient[recipient];
    
    this->unlock();
    
    return messages;
}

void MessageStore::clear() {
    this->lock();
    
    // clear out the messages
    for (map<string, vector<Message*> >::iterator it = this->messagesByRecipient.begin();
            it != this->messagesByRecipient.end();
            ++it) {
        vector<Message*> messages = (*it).second;
        for (vector<Message*>::iterator it2 = messages.begin(); it2 != messages.end(); ++it2) {
            Message* message = *it2;
            delete message;
        }
    }
    this->messagesByRecipient.clear();
    
    this->unlock();
}

void MessageStore::lock() {
    sem_wait(&this->lock_);
}

void MessageStore::unlock() {
    sem_post(&this->lock_);
}
