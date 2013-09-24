/* 
 * File:   ThreadPool.cpp
 * Author: keith
 * 
 * Created on September 23, 2013, 8:42 PM
 */

#include <vector>
#include <errno.h>
#include <stdio.h>
#include "main.h"

#include "ThreadPool.h"

ThreadPool::ThreadPool(int numThreads) {
    this->numThreads = numThreads;
}

ThreadPool::~ThreadPool() {
}

void ThreadPool::run(void *(*func)(void *), void* context) {
    pthread_t thread;
    for (int i = 0; i < this->numThreads; i++) {
        int retval = pthread_create(&thread, NULL, func, context);
        if (0 == retval) {
            this->threads.push_back(thread);
        } else {
            perror("pthread_create");
        }
    }
}

void ThreadPool::join() {
    for (vector<pthread_t>::iterator it = this->threads.begin(); 
            it != this->threads.end(); 
            ++it) {
        pthread_join(*it, NULL);
    }
}

void ThreadPool::cancel() {
    for (vector<pthread_t>::iterator it = this->threads.begin(); 
            it != this->threads.end(); 
            ++it) {
        pthread_cancel(*it);
    }
}
