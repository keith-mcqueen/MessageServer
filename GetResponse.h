/* 
 * File:   GetResponse.h
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 10:48 PM
 */

#ifndef GETRESPONSE_H
#define	GETRESPONSE_H

#include "Response.h"

class GetResponse : public Response {
public:
    GetResponse(string subject, string message);
    virtual ~GetResponse();

protected:
    virtual string getHeader();
    virtual string getBody();

private:
    string subject;
    string message;
};

#endif	/* GETRESPONSE_H */

