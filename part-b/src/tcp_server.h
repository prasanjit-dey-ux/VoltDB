#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <iostream>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include "storage_engine.h"
#include "resp_parser.h"

#define MAX_EVENTS 10

class TCPServer {
public:
    explicit TCPServer(int port);
    void start();
private:
    int server_fd, epoll_fd;
    void handle_client(int client_socket);
    BlinkDB db;
};

#endif
