/* 
 * File:   PutHandler.h
 * Author: kmcqueen
 *
 * Created on September 17, 2013, 12:06 PM
 */

#ifndef PUTHANDLER_H
#define	PUTHANDLER_H

#include "RequestHandler.h"

class PutHandler : public RequestHandler {
public:
    virtual ~PutHandler();

    static PutHandler* instance();

protected:
    virtual string getRequestPrefix();
    virtual string getName();
    virtual bool doHandleRequest(string request, ClientProxy* client);

private:
};

#endif	/* PUTHANDLER_H */

