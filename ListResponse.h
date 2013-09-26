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
    void setMessageCount(int count);
    void setMessageList(string messageList);

protected:
    virtual string getHeader();
    virtual string getBody();

private:
    int messageCount;
    string messageList;
};

#endif	/* LISTRESPONSE_H */

