/* 
 * File:   ClearHandler.h
 * Author: kmcqueen
 *
 * Created on September 17, 2013, 7:15 PM
 */

#ifndef CLEARHANDLER_H
#define	CLEARHANDLER_H

#include "RequestHandler.h"

class ResetHandler : public RequestHandler {
public:
    virtual ~ResetHandler();
    
    static ResetHandler* instance();
    
protected:
    virtual string getRequestPrefix();
    virtual string getName();
    virtual bool doHandleRequest(string request, ClientProxy* client);
    
private:

};

#endif	/* CLEARHANDLER_H */

