/* 
 * File:   main.cpp
 * Author: kmcqueen
 *
 * Created on September 16, 2013, 4:19 PM
 */
#include "main.h"
#include "Server.h"

#include <cstdlib>
#include <iostream>
#include <unistd.h>

using namespace std;

bool DEBUG = false;

void debug(string info) {
    if (DEBUG) {
        cout << "[DEBUG] " << info << endl;
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    int option;
    
    int port = 3000;
    
    // process command line options using getopt()
    // see "man 3 getopt"
    while ((option = getopt(argc,argv,"p:d")) != -1) {
        switch (option) {
            case 'p':
                port = atoi(optarg);
                break;
            
            case 'd':
                DEBUG = true;
                break;
            
            default:
                cout << "msgd [-p port] [-d]" << endl;
                exit(EXIT_FAILURE);
        }
    }
    
    Server* server = Server::instance();
    server->serve(port);

    return 0;
}

