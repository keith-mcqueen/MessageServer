/* 
 * File:   ClientProxy.h
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 5:01 PM
 */

#ifndef CLIENTPROXY_H
#define	CLIENTPROXY_H

#include <string>

using namespace std;

class ClientProxy {
public:
    ClientProxy(int clientId);
    virtual ~ClientProxy();
    string getRequestLine();
    string getRequestString(int length);

private:
    int clientId;
    string leftOvers;
};

#endif	/* CLIENTPROXY_H */

