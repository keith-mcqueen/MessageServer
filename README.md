MessageServer
=============

BYU CS 360 MessageServer

# Information for Lab 2

Synchronization is encapsulated in classes that matter:

* ClientManager(.h/.cpp) - the pushClient() and popClient() methods use
  private semaphores as follows:
  * lock - to lock down access to the queue of ClientProxy objects
  * open_slot - to wait/notify on an open slot for a client
  * client_added - to wait/notify for the addition of a client to the queue

* MessageStore(.h/.cpp) - all public methods (addMessage(), getMessages(),
  and clear()) invoke the private lock() and unlock() methods at the 
  beginning and end respectively to synchronize access to the underlying data.

The Server(.h/.cpp) class makes use of the above classes as well as the
ThreadPool(.h/.cpp) class to implement multi-threading and to be able to support
multiple clients simultaneously.  The main() function (main.cpp) allows for
the number of supported clients (size of the client queue) and the number of 
threads servicing those clients to be configured at startup (with defaults of
100 and 10 respectively).