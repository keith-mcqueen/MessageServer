/* 
 * File:   ListHandler.h
 * Author: kmcqueen
 *
 * Created on September 17, 2013, 12:51 PM
 */

#ifndef LISTHANDLER_H
#define	LISTHANDLER_H

#include "RequestHandler.h"

class ListHandler : public RequestHandler {
public:
    virtual ~ListHandler();
    
    static ListHandler* instance();
    
protected:
    virtual string getRequestPrefix();
    virtual string getName();
    virtual bool doHandleRequest(string request, ClientProxy* client);
    
private:

};

#endif	/* LISTHANDLER_H */

