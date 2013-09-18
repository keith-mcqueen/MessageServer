/* 
 * File:   GetHandler.h
 * Author: kmcqueen
 *
 * Created on September 17, 2013, 1:04 PM
 */

#ifndef GETHANDLER_H
#define	GETHANDLER_H

#include "RequestHandler.h"

class GetHandler : public RequestHandler {
public:
    virtual ~GetHandler();
    
    static GetHandler* instance();
    
protected:
    virtual string getRequestPrefix();
    virtual string getName();
    virtual bool doHandleRequest(string request, ClientProxy* client);
    
private:

};

#endif	/* GETHANDLER_H */

