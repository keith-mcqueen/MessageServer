/* 
 * File:   DefaultHandler.h
 * Author: kmcqueen
 *
 * Created on September 17, 2013, 12:07 AM
 */

#ifndef DEFAULTHANDLER_H
#define	DEFAULTHANDLER_H

#include "RequestHandler.h"

class DefaultHandler : public RequestHandler {
public:
    virtual ~DefaultHandler();
    virtual bool canHandle(string request);

    static DefaultHandler* instance();

protected:
    virtual string getRequestPrefix();
    virtual string getName();
    virtual bool doHandleRequest(string request, ClientProxy* client);

private:

};

#endif	/* DEFAULTHANDLER_H */

