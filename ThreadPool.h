/* 
 * File:   ThreadPool.h
 * Author: keith
 *
 * Created on September 23, 2013, 8:42 PM
 */

#ifndef THREADPOOL_H
#define	THREADPOOL_H

#include <pthread.h>

using namespace std;

class ThreadPool {
public:
    ThreadPool(int numThreads);
    virtual ~ThreadPool();
    void run(void *(*func) (void *), void* context);
    void join();
    void cancel();

private:
    int numThreads;
    vector<pthread_t> threads;
};

#endif	/* THREADPOOL_H */

