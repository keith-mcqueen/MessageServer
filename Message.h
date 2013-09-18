/* 
 * File:   Message.h
 * Author: kmcqueen
 *
 * Created on September 17, 2013, 11:39 AM
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

#include <string>

using namespace std;

class Message {
public:
    Message(string subject, string body);
    virtual ~Message();
    string getSubject();
    string getBody();

private:
    string subject;
    string body;
};

#endif	/* MESSAGE_H */

