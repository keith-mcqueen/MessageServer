/* 
 * File:   Response.h
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 8:44 PM
 */

#ifndef RESPONSE_H
#define	RESPONSE_H

#include <string>

using namespace std;

class Response {
public:
    Response(string type);
    virtual ~Response();
    string toString();
    
protected:
    virtual string getHeader();
    virtual string getBody();
    
private:
    string type;
};

#endif	/* RESPONSE_H */

