/* 
 * File:   ErrorResponse.h
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 9:51 PM
 */

#ifndef ERRORRESPONSE_H
#define	ERRORRESPONSE_H

#include "Response.h"

class ErrorResponse : public Response {
public:
    ErrorResponse(string description);
    virtual ~ErrorResponse();

protected:
    virtual string getHeader();

private:
    string description;
};

#endif	/* ERRORRESPONSE_H */

