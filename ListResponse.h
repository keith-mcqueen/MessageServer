/* 
 * File:   ListResponse.h
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 10:04 PM
 */

#ifndef LISTRESPONSE_H
#define	LISTRESPONSE_H

#include "Response.h"
#include <vector>

class ListResponse : public Response {
public:
    ListResponse();
    virtual ~ListResponse();
    void addSubject(string subject);

protected:
    virtual string getHeader();
    virtual string getBody();

private:
    vector<string> subjects;
};

#endif	/* LISTRESPONSE_H */

