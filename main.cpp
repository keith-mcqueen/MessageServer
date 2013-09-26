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
    int clients = 100;
    int threads = 10;
    
    // process command line options using getopt()
    // see "man 3 getopt"
    while ((option = getopt(argc,argv,"p:c:t:d")) != -1) {
        switch (option) {
            case 'p':
                port = atoi(optarg);
                break;
            
            case 'd':
                DEBUG = true;
                break;
                
            case 'c':
                clients = atoi(optarg);
                break;
                
            case 't':
                threads = atoi(optarg);
                break;
            
            default:
                cout << "msgd [-p port] [-c num_clients] [-t num_threads] [-d]" << endl;
                exit(EXIT_FAILURE);
        }
    }
    
    Server* server = Server::instance();
    server->serve(port, clients, threads);

    return 0;
}

