/* 
 * File:   ClientProxy.cpp
 * Author: kmcqueen
 * 
 * Created on September 16, 2013, 5:01 PM
 */
#include "ClientProxy.h"

#include <errno.h>
#include <arpa/inet.h>
#include "main.h"

ClientProxy::ClientProxy(int clientId) {
    this->clientId = clientId;
}

ClientProxy::~ClientProxy() {
}

string ClientProxy::getRequestLine() {
    debug("ClientProxy::getRequestLine() -- getting a request line from the client");
    
    // start out with the leftovers from the last call
    string request = this->leftOvers;
    
    // the temporary buffer to store the server's response
    char* buf;
    
    int newline;
    while ((newline = request.find("\n")) == string::npos) {
        int numCharsRecvd = recv(this->clientId, buf, 1024, 0);
        if (numCharsRecvd < 0) {
            if (errno == EINTR) {
                // the socket call was interrupted, just try again
                continue;
            } else {
                // something bad happened
                //perror("read");
                return "";
            }
        } else if (numCharsRecvd == 0) {
            // the socket is closed
            return "";
        }
        
        // append the received characters (bytes) to the response
        request.append(buf, numCharsRecvd);
    }
    
    // save everything after the newline for later
    this->leftOvers = request.substr(newline + 1);
    
    // return the portion of the response that precedes the newline
    return request.substr(0, newline + 1);
}

string ClientProxy::getRequestString(int length) {
    debug("ClientProxy::getRequestString -- getting a request string from the client");
    
    // start out with the leftovers from the last call
    string request = this->leftOvers;
    
    // the temporary buffer to store the server's response
    char* buf;
    
    while (request.length() < length) {
        int numCharsRecvd = recv(this->clientId, buf, 1024, 0);
        if (numCharsRecvd < 0) {
            if (errno == EINTR) {
                // the socket call was interrupted, just try again
                continue;
            } else {
                // something bad happened
                //perror("read");
                return "";
            }
        } else if (numCharsRecvd == 0) {
            // the socket is closed
            return "";
        }
        
        // append the received characters (bytes) to the response
        request.append(buf, numCharsRecvd);
    }
    
    // save everything after the newline for later
    this->leftOvers = request.substr(length);
    
    // return the portion of the response that precedes the newline
    return request.substr(0, length);
}