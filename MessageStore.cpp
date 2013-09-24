/* 
 * File:   MessageStore.cpp
 * Author: keith
 * 
 * Created on September 23, 2013, 10:29 PM
 */

#include "MessageStore.h"

MessageStore::MessageStore() {
    sem_init(&this->lock_, 0, 1);
}

MessageStore::~MessageStore() {
}

void MessageStore::addMessage(string recipient, Message* message) {
    this->lock();
    
    this->messagesByRecipient.insert(pair<string, Message*>(recipient, message));
    
    this->unlock();
}

vector<Message*> MessageStore::getMessages(string recipient) {
    this->lock();
    
    vector<Message*> messages;
    
    pair<multimap<string, Message*>::iterator, multimap<string, Message*>::iterator> range;
    range = this->messagesByRecipient.equal_range(recipient);
    for (multimap<string, Message*>::iterator it = range.first; it != range.second; ++it) {
        messages.push_back(it->second);
    }
    
    this->unlock();
    
    return messages;
}

void MessageStore::clear() {
    this->lock();
    
    for (multimap<string, Message*>::iterator it = this->messagesByRecipient.begin(); 
            it != this->messagesByRecipient.end(); 
            ++it) {
        Message* message = it->second;
        delete message;
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
