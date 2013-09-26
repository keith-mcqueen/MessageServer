/* 
 * File:   ListResponse.h
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 10:04 PM
 */

#ifndef LISTRESPONSE_H
#define	LISTRESPONSE_H

#include "Response.h"
#include "Message.h"
#include <vector>

class ListResponse : public Response {
public:
    ListResponse();
    virtual ~ListResponse();
    void addMessages(vector<Message*> messages);

protected:
    virtual string getHeader();
    virtual string getBody();

private:
    vector<Message*> messages;
};

#endif	/* LISTRESPONSE_H */

